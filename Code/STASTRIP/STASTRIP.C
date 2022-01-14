/*
 * STASTRIP.C
 * StatStrip Version 1.00
 *
 * Window procedure and other functions that are frequently used in
 * the life of a StatStrip.
 *
 * Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <windows.h>
#include "statint.h"


/*
 * StatStripWndProc
 *
 * Purpose:
 *  Window procedure for the StatStrip control.
 */

LRESULT APIENTRY StatStripWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PSTATSTRIP      pST;
    int             cyFont;
    HDC             hDC;
    LRESULT         lRet;

    pST=(PSTATSTRIP)GetWindowLong(hWnd, STATWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pST=(PSTATSTRIP)(void *)LocalAlloc(LPTR, CBSTATSTRIP);

            if (NULL==pST)
                return -1L;

            //Calc size of 0 point font, which we'll use as default.
            hDC=GetDC(NULL);
            cyFont=-MulDiv(10, GetDeviceCaps(hDC, LOGPIXELSY), 72);
            ReleaseDC(NULL, hDC);

            pST->hFont=CreateFont(cyFont, 0, 0, 0, FW_NORMAL, FALSE
                , FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS
                , CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY
                , VARIABLE_PITCH | FF_SWISS, TEXT("MS Sans Serif"));

            /*
             * If we could create the font, remember that we own it.
             * If font creation failed, then we'll just do with the
             * system font.
             */
            pST->fMyFont=(NULL!=pST->hFont);

            SetWindowLong(hWnd, STATWL_STRUCTURE, (LONG)pST);
            return DefWindowProc(hWnd, iMsg, wParam, lParam);


        case WM_DESTROY:
            StatStripClean(pST, TRUE);
            LocalFree((HLOCAL)(UINT)(LONG)pST);
            break;


        case WM_ERASEBKGND:
            /*
             * Eat this message to avoid erasing portions that we are
             * going to repaint in WM_PAINT.  Part of a change-state-
             * and-repaint strategy is to rely on WM_PAINT to do
             * anything visual, which includes erasing invalid
             * portions.  Letting WM_ERASEBKGND erase the background
             * is redundant.
             */
            return TRUE;


        case WM_PAINT:
            StatStripPaint(hWnd, pST);
            break;


        case WM_SETFONT:
            if (!IsWindowEnabled(hWnd))
                break;

            /*
             * wParam has the new font.  Always repaint immediately.
             * First, delete the old font only if we own it.
             */
            if (NULL!=pST->hFont && pST->fMyFont)
                DeleteObject(pST->hFont);

            //Save the new font but mark that we don't own it.
            pST->hFont=(HFONT)wParam;
            pST->fMyFont=FALSE;

            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;


        case WM_GETFONT:
            return (LRESULT)(UINT)pST->hFont;


        case WM_SETTEXT:
            if (!IsWindowEnabled(hWnd))
                break;

            //This saves the text for us, so we only have to repaint.
            lRet=DefWindowProc(hWnd, iMsg, wParam, lParam);

            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;


        case WM_ENABLE:
            //Repaint on enabling or disabling either way.
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;


        //Control-specific messages
        case STATM_MESSAGEMAP:
            //lParam is an LPSTATMESSAGEMAPINIT
            if (0L!=lParam)
                {
                LPSTATMESSAGEMAPINIT  pMI=(LPSTATMESSAGEMAPINIT)lParam;

                return (LRESULT)StatStripMessageMap(hWnd
                    , pMI->hWndOwner, pMI->hInst, pMI->uIDRMap
                    , pMI->idsMin, pMI->idsMax, pMI->cchMax
                    , pMI->uIDPopupMin, pMI->uIDPopupMax
                    , pMI->uIDStatic, pMI->uIDBlank
                    , pMI->uIDSysMenu);
                }
            break;


        case STATM_MENUSELECT:
            //wParam and lParam from caller's WM_MENUSELECT message
            StatStripMenuSelect(hWnd, wParam, lParam);
            break;


        case STATM_MESSAGEDISPLAY:
            //wParam is ID to display
            StatStripMessageDisplay(hWnd, (USHORT)wParam);
            break;


        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }







/*
 * StatStripPaint
 * Internal
 *
 * Purpose:
 *  Provides drawing the StatStrip window with the 3-D effect and the
 *  current message and the current font.
 *
 * Parameters:
 *  hWnd            HWND of the window;
 *  pST             PSTATSTRIP containing control information.
 *
 * Return Value:
 *  None
 */

static void StatStripPaint(HWND hWnd, PSTATSTRIP pST)
    {
    int             y;
    HDC             hDC;
    RECT            rc;
    UINT            cch;
    TCHAR           szMsg[512];
    HPEN            hPenFrame, hPenHigh;
    HFONT           hFontT;
    HBRUSH          hBr;
    COLORREF        crHighlight;
    TEXTMETRIC      tm;
    PAINTSTRUCT     ps;

    hDC=BeginPaint(hWnd, &ps);
    GetClientRect(hWnd, &rc);

    //Draw the top line using the frame color
    hPenFrame=CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME));

    if (NULL!=hPenFrame)
        {
        SelectObject(hDC, hPenFrame);
        MoveToEx(hDC, rc.left, rc.top, NULL);
        LineTo(hDC, rc.right, rc.top);
        }

    //Draw the two highlight lines
    crHighlight=GetSysColor(COLOR_BTNHIGHLIGHT);

    hPenHigh=CreatePen(PS_SOLID, 1, crHighlight);

    if (NULL!=hPenHigh)
        {
        SelectObject(hDC, hPenHigh);
        MoveToEx(hDC, rc.left, rc.bottom, NULL);
        LineTo(hDC, rc.left, rc.top+1);
        LineTo(hDC, rc.right, rc.top+1);
        }


    //Draw the face color avoiding the frame and highlight
    rc.top +=2;
    rc.left+=1;

    hBr=CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
    FillRect(hDC, &rc, hBr);
    DeleteObject(hBr);


    //Now write the text, color sensitive to the enabled state
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, GetSysColor(IsWindowEnabled(hWnd)
        ? COLOR_BTNTEXT : COLOR_BTNSHADOW));

    //Center the font vertically, accounting for borders on the rect.
    hFontT=SelectObject(hDC, pST->hFont);

    GetTextMetrics(hDC, &tm);
    y=rc.top+(((rc.bottom-rc.top)-tm.tmHeight) >> 1);
    y=max(y, rc.top);

    cch=GetWindowText(hWnd, szMsg, sizeof(szMsg));
    TextOut(hDC, 4, y, szMsg, cch);
    SelectObject(hDC, hFontT);

    //Clean up
    EndPaint(hWnd, &ps);

    DeleteObject(hPenHigh);
    DeleteObject(hPenFrame);
    return;
    }







/*
 * StatStripMenuSelect
 * External
 *
 * Purpose:
 *  Displays the appropriate message for whatever is in the
 *  parameters of a WM_MENUSELECT message.  This can only be called
 *  if StatStripMessageMap has already been called and must be used
 *  with the same menu the owner window had at the time of that call.
 *
 *  Since we're unpacking an application's messages for it, the app
 *  and this DLL must match 16-16 and 32-32 bits.
 *
 * Parameters:
 *  hWnd            HWND of the StatStrip
 *  wParam          WPARAM of the WM_MENUSELECT message.
 *  lParam          LPARAM of the WM_MENUSELECT message.
 *
 * Return Value:
 *  None
 */

void WINAPI StatStripMenuSelect(HWND hWnd, WPARAM wParam
    , LPARAM lParam)
    {
    PSTATSTRIP      pST;
    USHORT          uID;

    MENUSELECTPARAMS(wItem, wMenuFlags, hMenu);

    if (!IsWindow(hWnd) || !IsWindowEnabled(hWnd))
        return;

    pST=(PSTATSTRIP)GetWindowLong(hWnd, STATWL_STRUCTURE);

    //Case 1:  Menu was cancelled, display static string
    if (0==wItem && 0xFFFF==wMenuFlags)
        uID=pST->uIDStatic;
    else
        //Case 2:  System menu selected by itself.
        if (MF_POPUP & wMenuFlags && MF_SYSMENU & wMenuFlags)
            uID=pST->uIDSysMenu;
        else
            /*
             * Case 3:  A popup menu was chosen:  Find the ID for
             * hMenu (in wItem)
             */
            if (MF_POPUP & wMenuFlags)
                uID=IDFromHMenu(pST, (HMENU)wItem);
            else
                //Case 4:  A menu item is selected
                if (0!=wItem)
                    uID=(UINT)wItem;
                else
                    //Case 5:  Nothing is selected (like a separator)
                    uID=pST->uIDBlank;


    /*
     * Go display the message.  Since all this function does extra
     * that we may not have to do here is a GetWindowLong, which
     * is quick, so by doing this we keep the code in one place and
     * only have to test this API to test the other.
     */
    StatStripMessageDisplay(hWnd, uID);
    return;
    }






/*
 * StatStripMessageDisplay
 * External
 *
 * Purpose:
 *  Displays the appropriate message for a given ID value.   This can
 *  only be called if StatStripMessageMap has already been called.
 *
 * Parameters:
 *  hWnd            HWND of the StatStrip
 *  uID             USHORT of the message to display.
 *
 * Return Value:
 *  None
 */

void WINAPI StatStripMessageDisplay(HWND hWnd, USHORT uID)
    {
    PSTATSTRIP      pST;
    UINT            idsMsg;

    if (!IsWindow(hWnd) || !IsWindowEnabled(hWnd))
        return;

    pST=(PSTATSTRIP)GetWindowLong(hWnd, STATWL_STRUCTURE);

    //Go look up the string ID to display.
    idsMsg=IStringFromID(pST->pSMM, pST->cMessages, uID);
    SetWindowText(hWnd, pST->ppsz[idsMsg-pST->idsMin]);
    return;
    }






/*
 * IDFromHMenu
 *
 * Purpose:
 *  Given a specific menu handle, searches through pST->pPMM for a
 *  match and returns the ID associated with that menu.
 *
 * Parameters:
 *  pST             PSTATSTRIP of the control
 *  hMenu           HMENU to search for
 *
 * Return Value:
 *  USHORT          ID associated with the menu handle.
 */

static USHORT IDFromHMenu(PSTATSTRIP pST, HMENU hMenu)
    {
    USHORT      uID=pST->uIDBlank;      //Default is empty
    UINT        i;

   #ifdef WIN32
    /*
     * Under Win32 the hMenu passed here from the WM_MENUSELECT
     * message will only be the index to the actual menu.  We
     * have to use GetSubMenu from the top-level menu using this
     * index to actually get the menu handle.
     */

    hMenu=GetSubMenu(GetMenu(pST->hWndOwner), (UINT)hMenu);
   #endif

    for (i=0; i < pST->cPopups; i++)
        {
        if (pST->pPMM[i].hMenu==hMenu)
            {
            uID=pST->pPMM[i].uID;
            break;
            }
        }

    return uID;
    }







/*
 * IStringFromID
 *
 * Purpose:
 *  Performs a binary search in a STATMESSAGEMAP array looking for
 *  a specific item ID returning the string ID for that item.
 *
 * Parameters:
 *  pSMM            PSTATMESSAGEMAP to search
 *  cItems          USHORT size of the map in elements
 *  uID             USHORT item ID to locate.
 *
 * Return Value:
 *  UINT            String ID associated with wItem.
 */

static UINT IStringFromID(PSTATMESSAGEMAP pSMM, USHORT cItems
    , USHORT uID)
    {
    UINT        iLow =0;
    UINT        iHigh=cItems-1;
    UINT        iMid;

    while (TRUE)
        {
        iMid=(iLow+iHigh) >> 1;

        if (uID < pSMM[iMid].uID)
            iHigh=iMid-1;
        else
            {
            if (uID > pSMM[iMid].uID)
                iLow=iMid+1;
            else
                break;    //Equality
            }

        if (iHigh < iLow)
            break;
        }

    return pSMM[iMid].idsMsg;
    }
