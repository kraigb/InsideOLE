/*
 * INIT.C
 * StatStrip Version 1.00
 *
 * Initialization code for the StatStrip.
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
 * LibMain(32)
 *
 * Purpose:
 *  Entry point conditionally compiled for Windows NT and Windows
 *  3.1.  Provides the proper structure for each environment.
 */

#ifdef WIN32

BOOL __stdcall LibMain32(HINSTANCE hInstance, ULONG ulReason
    , PCONTEXT pContext)
    {
    UNREFERENCED_PARAMETER(pContext);

    if (DLL_PROCESS_DETACH==ulReason)
        return TRUE;
    else
        {
        if (DLL_PROCESS_ATTACH!=ulReason)
            return TRUE;
        }

    return FRegisterControl(hInstance);
    }

#else

int APIENTRY LibMain(HINSTANCE hInstance, WORD wDataSeg
    , WORD cbHeapSize, LPTSTR lpCmdLine)
    {
     //Perform global initialization.
    if (FRegisterControl(hInstance))
        {
        if (0!=cbHeapSize)
            UnlockData(0);
        }

    return (int)hInstance;
    }

#endif





/*
 * FRegisterControl
 *
 * Purpose:
 *  Registers the StatStrip control class, including CS_GLOBALCLASS
 *  to make the control available to all applications in the system.
 *
 * Parameters:
 *  hInst           HINSTANCE of the DLL that will own this class.
 *
 * Return Value:
 *  BOOL            TRUE if the class is registered, FALSE otherwise.
 */

static BOOL FRegisterControl(HINSTANCE hInst)
    {
    static BOOL     fRegistered=FALSE;
    WNDCLASS        wc;

    if (!fRegistered)
        {
        wc.lpfnWndProc   =StatStripWndProc;
        wc.cbClsExtra    =0;
        wc.cbWndExtra    =CBWINDOWEXTRA;
        wc.hInstance     =hInst;
        wc.hIcon         =NULL;
        wc.hCursor       =LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground =(HBRUSH)(COLOR_BTNFACE+1);
        wc.lpszMenuName  =NULL;
        wc.lpszClassName =CLASS_STATSTRIP;
        wc.style         =CS_DBLCLKS | CS_GLOBALCLASS
                          | CS_VREDRAW | CS_HREDRAW;

        fRegistered=RegisterClass(&wc);
        }

    return fRegistered;
    }








/*
 * StatStripMessageMap
 *
 * Purpose:
 *  Initializes the message mappings in the StatStrip for subsequent
 *  use with StatMessageMenuSelect.  If this function is called more
 *  than once then any previous initialization is cleaned up so
 *  previous message IDs will then be invalid.
 *
 *  The total number of messages is inferred by (idsMax-idsMin+1).
 *  The maximum number of popup menu items we'll hold is inferred by
 *  (uIDPopupMax-uIDPopupMin+1).
 *
 * Parameters:
 *  hWnd            HWND of the StatStrip control.
 *  hWndOwner       HWND of the window owning menus.
 *  hInst           HINSTANCE of the app from which to load resources
 *  uIDRMap         UINT identifying a resource mapping ID values
 *                  to string ID values.
 *  idsMin          UINT specifying the lowest string ID to load.
 *  idsMax          UINT specifying the hightest string ID to load.
 *  cchMax          UINT maximum string length.
 *  uIDPopupMin     USHORT lowest ID to assign to popup menus.
 *  uIDPopupMax     USHORT highest ID to assign to popup menus.
 *  uIDStatic       USHORT ID for the quiescent message.
 *  uIDBlank        USHORT ID for a blank message.
 *  uIDSysMenu      USHORT ID for the system menu.
 *
 * Return Value:
 *  BOOL            TRUE if the function was successful, FALSE
 *                  otherwise.
 */

BOOL WINAPI StatStripMessageMap(HWND hWnd, HWND hWndOwner
    , HINSTANCE hInst , UINT uIDRMap, UINT idsMin, UINT idsMax
    , UINT cchMax, USHORT uIDPopupMin, USHORT uIDPopupMax
    , USHORT uIDStatic, USHORT uIDBlank, USHORT uIDSysMenu)
    {
    PSTATSTRIP      pST;
    HMENU           hMenu;
    HRSRC           hRes;
    UINT            i;
    USHORT          uID;

   #ifdef WIN32
    DWORD           cbRes;
    DWORD           dwPrevProt;
   #endif

    if (!IsWindow(hWnd))
        return FALSE;

    pST=(PSTATSTRIP)GetWindowLong(hWnd, STATWL_STRUCTURE);

    if (NULL==pST)
        return FALSE;

    //Parameter validation
    if (NULL==hInst || idsMax < idsMin || uIDPopupMax < uIDPopupMin)
        return FALSE;

    //Clean ourselves out if we've already initialized.
    if (pST->fMapped)
        StatStripClean(pST, FALSE);

    pST->hWndOwner  =hWndOwner;

    pST->idsMin     =idsMin;
    pST->idsMax     =idsMax;
    pST->cMessages  =(USHORT)(idsMax-idsMin+1);

    pST->uIDPopupMin=uIDPopupMin;
    pST->uIDPopupMax=uIDPopupMax;
    pST->cPopups    =(USHORT)(uIDPopupMax-uIDPopupMin+1);

    pST->uIDStatic  =uIDStatic;
    pST->uIDBlank   =uIDBlank;
    pST->uIDSysMenu =uIDSysMenu;

    //Load the STATMESSAGEMAP array from our resources.
    hRes=FindResource(hInst, MAKEINTRESOURCE(uIDRMap), RT_RCDATA);

    if (NULL==hRes)
        return FALSE;


    pST->hMemSMM=LoadResource(hInst, hRes);

    if (NULL==pST->hMemSMM)
        return FALSE;

    pST->pSMM=(PSTATMESSAGEMAP)LockResource(pST->hMemSMM);

    if (NULL==pST->pSMM)
        {
        StatStripClean(pST, FALSE);
        return FALSE;
        }

   #ifdef WIN32
    /*
     * In Win32 resource pages are read-only when loaded.
     * Change to read-write for the purposes of sorting
     * initially.
     */
    cbRes=SizeofResource(hInst, hRes);
    VirtualProtect(pST->pSMM, cbRes, PAGE_READWRITE, &dwPrevProt);
   #endif

    //Sort these for binary search lookup.
    StatMessageMapSort(pST->pSMM, pST->cMessages);

   #ifdef WIN32
    VirtualProtect(pST->pSMM, cbRes, dwPrevProt, &dwPrevProt);
   #endif

    //Allocate space for string pointers
    pST->ppsz=(LPTSTR *)LocalAlloc(LPTR
        , sizeof(LPTSTR)*pST->cMessages);

    if (NULL==pST->ppsz)
        {
        StatStripClean(pST, FALSE);
        return FALSE;
        }

    //Load the stringtable for messages.
    pST->hMemSzStat=HStringCache(hInst, idsMin, idsMax, cchMax
        , pST->ppsz);

    if (NULL==pST->hMemSzStat)
        {
        StatStripClean(pST, FALSE);
        return FALSE;
        }

    //Allocate an array of POPUPMENUMAP structures
    pST->pPMM=(PPOPUPMENUMAP)(void *)LocalAlloc(LPTR
        , sizeof(POPUPMENUMAP)*pST->cPopups);

    if (NULL==pST->pPMM)
        {
        StatStripClean(pST, FALSE);
        return FALSE;
        }

    //Initialize the array mapping popup menus to specific IDs.
    uID=uIDPopupMin;
    hMenu=GetMenu(hWndOwner);

    for (i=0; i < pST->cPopups; i++)
        {
        pST->pPMM[i].hMenu=GetSubMenu(hMenu, i);
        pST->pPMM[i].uID  =uID++;
        }

    pST->fMapped=TRUE;
    return TRUE;
    }







/*
 * StatStripClean
 *
 * Purpose:
 *  Cleans out any allocations in a STATSTRIP.
 *
 * Parameters:
 *  pST             PSTATSTRIP to clean
 *  fIncludeFont    BOOL indicates if we're to also clean the font.
 *                  This is FALSE from StatMessageMap, TRUE from
 *                  WM_DESTROY.
 *
 * Return Value:
 *  None
 */

void StatStripClean(PSTATSTRIP pST, BOOL fIncludeFont)
    {
    //Free up anything from StatMessageMap
    if (NULL!=pST->pPMM)
        {
        LocalFree((HLOCAL)(UINT)(LONG)pST->pPMM);
        pST->pPMM=NULL;
        }

    if (NULL!=pST->ppsz)
        {
        LocalFree((HLOCAL)(UINT)(LONG)pST->ppsz);
        pST->ppsz=NULL;
        }

    if (NULL!=pST->hMemSzStat)
        {
        HStringCacheFree(pST->hMemSzStat);
        pST->hMemSzStat=NULL;
        }

    if (NULL!=pST->pSMM)
        {
       #ifndef WIN32
        UnlockResource(pST->hMemSMM);
       #endif
        pST->pSMM=NULL;
        }

    if (NULL!=pST->hMemSMM)
        {
        FreeResource(pST->hMemSMM);
        pST->hMemSMM=NULL;
        }

    //Delete the old font only if we own it.
    if (fIncludeFont)
        {
        if (NULL!=pST->hFont && pST->fMyFont)
            {
            DeleteObject(pST->hFont);
            pST->hFont=NULL;
            }
        }

    return;
    }





/*
 * HStringCache
 *
 * Purpose:
 *  Allocates memory and reads a stringtable into that memory.
 *  Pointers to the strings in the memory are then stored at ppsz
 *  which is assumed to be (idsMax-idsMin+1) strings long.
 *
 * Parameters:
 *  hInst           HINSTANCE of the application
 *  idsMin          UINT string index to start loading
 *  idsMax          UINT maximum string index in this table.
 *  cchMax          UINT length of the longest string in TCHARs.
 *  ppsz            LPTSTR * to an array in which to store pointers.
 *
 * Return Value:
 *  HGLOBAL         Handle to the memory.  NULL if memory could
 *                  not be allocated.
 */

static HGLOBAL HStringCache(HINSTANCE hInst, UINT idsMin, UINT idsMax
    , UINT cchMax, LPTSTR *ppsz)
    {
    HANDLE      hMem;
    LPTSTR      pch;
    UINT        cchUsed=0;
    UINT        cch;
    UINT        i, cStrings;

    cStrings=idsMax-idsMin+1;
    hMem=GlobalAlloc(GHND, cStrings * cchMax * sizeof(TCHAR));

    if (NULL!=hMem)
        {
        pch=GlobalLock(hMem);

        /*
         * Load the strings into the memory and retain the specific
         * pointer to that string.
         */
        for (i=0; i < cStrings; i++)
            {
            cch=LoadString(hInst, i+idsMin, (LPTSTR)(pch+cchUsed)
                , cchMax-1);
            ppsz[i]=(LPTSTR)(pch+cchUsed);

            /*
             * Add one char to cch to include a NULL.  The memory
             * was ZEROINITed on allocation so by skipping a TCHAR
             * we get the NULL.
             */
            cchUsed+=cch+sizeof(TCHAR);
            }

        /*
         * Memory is locked for the duration of the app.  Don't
         * bother reallocating since we might have to recalc
         * all the pointers to the strings again.
         */
        }

    return hMem;
    }





/*
 * HStringCacheFree
 *
 * Purpose:
 *  Frees up any memory associated with the string cache from
 *  HStringCache.
 *
 * Parameters:
 *  hMem            HGLOBAL to the memory containing the cahce.
 *
 * Return Value:
 *  None
 */

static void HStringCacheFree(HGLOBAL hMem)
    {
    if (NULL!=hMem)
        {
        GlobalUnlock(hMem);
        GlobalFree(hMem);
        }
    return;
    }





/*
 * StatMessageMapSort
 *
 * Purpose:
 *  Performs a selection sort on the STATMESSAGEMAP array that we
 *  load from our resource.  Since we expect that the data is
 *  partially sorted (we tend to place things in resources in groups
 *  of seqential values), since the number of messages is usually
 *  < 200, and since we're in startup (which takes a long time
 *  anyway), selection sort is a better choice to implement over
 *  qsort saving much code.
 *
 * Parameters:
 *  pSMM            PSTATMESSAGEMAP to sort
 *  n               USHORT number of elements in the array.
 *
 * Return Value:
 *  None
 */

static void StatMessageMapSort(PSTATMESSAGEMAP pSMM, USHORT n)
    {
    USHORT          i, j, k;
    STATMESSAGEMAP  smm;

    for (j=0; j < (UINT)(n-1); j++)
        {
        k=j;
        smm.uID   =pSMM[j].uID;
        smm.idsMsg=pSMM[j].idsMsg;

        for (i=j+1; i < (UINT)n; i++)
            {
            if (pSMM[i].uID < smm.uID)
                {
                smm.uID   =pSMM[i].uID;
                smm.idsMsg=pSMM[i].idsMsg;
                k=i;
                }
            }

        smm.uID       =pSMM[j].uID;
        smm.idsMsg    =pSMM[j].idsMsg;
        pSMM[j].uID   =pSMM[k].uID;
        pSMM[j].idsMsg=pSMM[k].idsMsg;
        pSMM[k].uID   =smm.uID;
        pSMM[k].idsMsg=smm.idsMsg;
        }

    return;
    }
