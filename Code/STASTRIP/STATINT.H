/*
 * STATINT.H
 * StatStrip Version 1.00
 *
 * Internal definitions and function prototypes for the StatStrip
 * control.
 *
 * Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <book1632.h>
#include "stastrip.h"


//For loading the RCDATA mapping menu item IDs to string IDs
typedef struct tagSTATMESSAGEMAP
    {
    USHORT      uID;
    USHORT      idsMsg;
    } STATMESSAGEMAP, *PSTATMESSAGEMAP;

//Array mapping menu handles to menu item IDs
typedef struct tagPOPUPMENUMAP
    {
    HMENU       hMenu;
    USHORT      uID;
    } POPUPMENUMAP, * PPOPUPMENUMAP;




typedef struct tagSTATSTRIP
    {
    HFONT               hFont;      //Current control font
    BOOL                fMyFont;

    BOOL                fMapped;    //StatStripMessageMap called?
    HWND                hWndOwner;

    USHORT              cMessages;  //Total number of messages
    UINT                idsMin;     //Starting string ID
    UINT                idsMax;

    USHORT              uIDStatic;  //Quiescent message ID
    USHORT              uIDBlank;   //Blank message ID
    USHORT              uIDSysMenu; //System menu message ID

    HGLOBAL             hMemSMM;    //Handle to STATMESSAGEMAP data
    PSTATMESSAGEMAP     pSMM;       //Memory holding STATMESSAGEMAP

    HGLOBAL             hMemSzStat; //Memory for Stat strings
    LPTSTR *            ppsz;       //Stat string pointers

    USHORT              cPopups;
    USHORT              uIDPopupMin;
    USHORT              uIDPopupMax;
    PPOPUPMENUMAP       pPMM;
    } STATSTRIP, *PSTATSTRIP;


#define CBSTATSTRIP             sizeof(STATSTRIP)

#define CBWINDOWEXTRA           sizeof(PSTATSTRIP)
#define STATWL_STRUCTURE        0


//STASTRIP.C
LRESULT APIENTRY StatStripWndProc(HWND, UINT, WPARAM, LPARAM);
static void      StatStripPaint(HWND, PSTATSTRIP);
static USHORT    IDFromHMenu(PSTATSTRIP, HMENU);
static UINT      IStringFromID(PSTATMESSAGEMAP, USHORT, USHORT);

//INIT.C
void             StatStripClean(PSTATSTRIP, BOOL);
static BOOL      FRegisterControl(HINSTANCE);
static HGLOBAL   HStringCache(HINSTANCE, UINT, UINT, UINT, LPTSTR *);
static void      HStringCacheFree(HGLOBAL);
static void      StatMessageMapSort(PSTATMESSAGEMAP, USHORT);
