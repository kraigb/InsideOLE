/*
 * BEEPER.CPP
 * Beeper Automation Object #4 Chapter 14
 *
 * Implementation of the CBeeper class demonstrating the use of
 * dual interface.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "beeper.h"

extern HINSTANCE g_hInst;

#ifdef WIN32
extern DWORD     g_dwTLS;
#endif


/*
 * CBeeper::CBeeper
 * CBeeper::~CBeeper
 *
 * Parameters (Constructor):
 *  pUnkOuter       LPUNKNOWN of a controlling unknown.
 *  pfnDestroy      PFNDESTROYED to call when an object
 *                  is destroyed.
 */

CBeeper::CBeeper(LPUNKNOWN pUnkOuter, PFNDESTROYED pfnDestroy)
    {
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pfnDestroy=pfnDestroy;

    m_lSound=0;

    //These are created as needed in GetTypeInfo
    m_pITINeutral=NULL;
    m_pITIGerman=NULL;
    return;
    }


CBeeper::~CBeeper(void)
    {
    ReleaseInterface(m_pITIGerman);
    ReleaseInterface(m_pITINeutral);
    return;
    }



/*
 * CBeeper::Init
 *
 * Purpose:
 *  Performs any intiailization of a CBeeper that's prone to failure
 *  that we also use internally before exposing the object outside.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CBeeper::Init(void)
    {
    LPUNKNOWN       pIUnknown=this;

    if (NULL!=m_pUnkOuter)
        pIUnknown=m_pUnkOuter;

    return TRUE;
    }



/*
 * CBeeper::QueryInterface
 * CBeeper::AddRef
 * CBeeper::Release
 */

STDMETHODIMP CBeeper::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    /*
     * IUnknown, IBeeper, and IDispatch are all
     * part of CBeeper now.
     */
    if (IID_IUnknown==riid || IID_IBeeper==riid
        || IID_IDispatch==riid)
        *ppv=this;

    //Indicate that we support error information
    if (IID_ISupportErrorInfo==riid)
        *ppv=m_pImpISuppErr;

    //AddRef any interface we'll return.
    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CBeeper::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CBeeper::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0L;
    }



//IDispatch functions, now part of CBeeper

/*
 * CBeeper::GetTypeInfoCount
 *
 * Purpose:
 *  Returns the number of type information (ITypeInfo) interfaces
 *  that the object provides (0 or 1).
 *
 * Parameters:
 *  pctInfo         UINT * to the location to receive
 *                  the count of interfaces.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */

STDMETHODIMP CBeeper::GetTypeInfoCount(UINT *pctInfo)
    {
    //We implement GetTypeInfo so return 1
    *pctInfo=1;
    return NOERROR;
    }




/*
 * CBeeper::GetTypeInfo
 *
 * Purpose:
 *  Retrieves type information for the automation interface.  This
 *  is used anywhere that the right ITypeInfo interface is needed
 *  for whatever LCID is applicable.  Specifically, this is used
 *  from within GetIDsOfNames and Invoke.
 *
 * Parameters:
 *  itInfo          UINT reserved.  Must be zero.
 *  lcid            LCID providing the locale for the type
 *                  information.  If the object does not support
 *                  localization, this is ignored.
 *  ppITypeInfo     ITypeInfo ** in which to store the ITypeInfo
 *                  interface for the object.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */

STDMETHODIMP CBeeper::GetTypeInfo(UINT itInfo, LCID lcid
    , ITypeInfo **ppITypeInfo)
    {
    HRESULT     hr;
    ITypeLib   *pITypeLib;
    ITypeInfo **ppITI=NULL;

    if (0!=itInfo)
        return ResultFromScode(TYPE_E_ELEMENTNOTFOUND);

    if (NULL==ppITypeInfo)
        return ResultFromScode(E_POINTER);

    *ppITypeInfo=NULL;

    /*
     * Since we returned one from GetTypeInfoCount, this function
     * can be called for a specific locale.  We support English,
     * German, and neutral (defaults to English) locales.  Anything
     * else is an error.
     *
     * After this switch statement, ppITI will either be NULL or
     * a valid pointer in it after.  If NULL, we know we need to
     * load type information, retrieve the ITypeInfo we want, and
     * then store it in *ppITI.
     */
    switch (PRIMARYLANGID(lcid))
        {
        case LANG_NEUTRAL:
        case LANG_ENGLISH:
            ppITI=&m_pITINeutral;
            break;

        case LANG_GERMAN:
            ppITI=&m_pITIGerman;
            break;

        default:
            return ResultFromScode(DISP_E_UNKNOWNLCID);
        }

    //Load a type lib if we don't have the information already.
    if (NULL==*ppITI)
        {
        /*
         * The type libraries are registered under 0 (neutral),
         * 7 (German), and 9 (English) with no specific sub-
         * language, which would make them 407 or 409 and such.
         * If you are sensitive to sub-languages, then use the
         * full LCID instead of just the LANGID as done here.
         */
        hr=LoadRegTypeLib(LIBID_BeeperTypeLibrary, 1, 0
            , PRIMARYLANGID(lcid), &pITypeLib);

        /*
         * If LoadRegTypeLib fails, try loading directly with
         * LoadTypeLib, which will register the library for us.
         * Note that there's no default case here because the
         * prior switch will have filtered lcid already.
         *
         * NOTE:  You should prepend your DIR registry key to the
         * .TLB name so you don't depend on it being it the PATH.
         * This sample will be updated later to reflect this.
         */
        if (FAILED(hr))
            {
            switch (PRIMARYLANGID(lcid))
                {
                case LANG_NEUTRAL:
                case LANG_ENGLISH:
                    hr=LoadTypeLib(OLETEXT("BEEP0000.TLB"), &pITypeLib);
                    break;

                case LANG_GERMAN:
                    hr=LoadTypeLib(OLETEXT("BEEP0007.TLB"), &pITypeLib);
                    break;
                }
            }

        if (FAILED(hr))
            return hr;

        //Got the type lib, get type info for the interface we want
        hr=pITypeLib->GetTypeInfoOfGuid(IID_IBeeper, ppITI);
        pITypeLib->Release();

        if (FAILED(hr))
            return hr;
        }

    /*
     * Note:  the type library is still loaded since we have
     * an ITypeInfo from it.
     */

    (*ppITI)->AddRef();
    *ppITypeInfo=*ppITI;
    return NOERROR;
    }





/*
 * CBeeper::GetIDsOfNames
 *
 * Purpose:
 *  Converts text names into DISPIDs to pass to Invoke
 *
 * Parameters:
 *  riid            REFIID reserved.  Must be IID_NULL.
 *  rgszNames       OLECHAR ** pointing to the array of names to be
 *                  mapped.
 *  cNames          UINT number of names to be mapped.
 *  lcid            LCID of the locale.
 *  rgDispID        DISPID * caller allocated array containing IDs
 *                  corresponging to those names in rgszNames.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */

STDMETHODIMP CBeeper::GetIDsOfNames(REFIID riid
    , OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispID)
    {
    HRESULT     hr;
    ITypeInfo  *pTI;

    if (IID_NULL!=riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    //Get the right ITypeInfo for lcid.
    hr=GetTypeInfo(0, lcid, &pTI);

    if (SUCCEEDED(hr))
        {
        hr=DispGetIDsOfNames(pTI, rgszNames, cNames, rgDispID);
        pTI->Release();
        }

    return hr;
    }



/*
 * CBeeper::Invoke
 *
 * Purpose:
 *  Calls a method in the dispatch interface or manipulates a
 *  property.
 *
 * Parameters:
 *  dispID          DISPID of the method or property of interest.
 *  riid            REFIID reserved, must be IID_NULL.
 *  lcid            LCID of the locale.
 *  wFlags          USHORT describing the context of the invocation.
 *  pDispParams     DISPPARAMS * to the array of arguments.
 *  pVarResult      VARIANT * in which to store the result.  Is
 *                  NULL if the caller is not interested.
 *  pExcepInfo      EXCEPINFO * to exception information.
 *  puArgErr        UINT * in which to store the index of an
 *                  invalid parameter if DISP_E_TYPEMISMATCH
 *                  is returned.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */

STDMETHODIMP CBeeper::Invoke(DISPID dispID, REFIID riid
    , LCID lcid, unsigned short wFlags, DISPPARAMS *pDispParams
    , VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
    {
    HRESULT     hr;
    ITypeInfo  *pTI;
    LANGID      langID=PRIMARYLANGID(lcid);

    //riid is supposed to be IID_NULL always
    if (IID_NULL!=riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    //Get the ITypeInfo for lcid
    hr=GetTypeInfo(0, lcid, &pTI);

    if (FAILED(hr))
        return hr;

   #ifdef WIN32
    //This saves the language ID for this thread
    TlsSetValue(g_dwTLS, &langID);
   #endif

    //Clear exceptions
    SetErrorInfo(0L, NULL);

    //This is exactly what DispInvoke does--so skip the overhead.
    hr=pTI->Invoke((IBeeper *)this, dispID, wFlags
        , pDispParams, pVarResult, pExcepInfo, puArgErr);

    //Exception handling is done within ITypeInfo::Invoke

    pTI->Release();
    return hr;
    }








//IBeeper interface functions

/*
 * CBeeper::get_Sound
 * CBeeper::put_Sound
 *
 * Purpose:
 *  Functions called from DispInvoke to handle the Sound property.
 *
 * Parameters (Set only):
 *  lSound          long, new sound to save after validation
 *
 * Out Parameters: (Get only):
 *  plSound         long *, the current sound.
 */

STDMETHODIMP CBeeper::get_Sound(long *plSound)
    {
    if (NULL==plSound)
        return ResultFromScode(E_POINTER);

    *plSound=m_lSound;
    return NOERROR;
    }


STDMETHODIMP CBeeper::put_Sound(long lSound)
    {
    if (MB_OK!=lSound && MB_ICONEXCLAMATION!=lSound
        && MB_ICONQUESTION!=lSound && MB_ICONHAND!=lSound
        && MB_ICONASTERISK!=lSound)
        {
        /*
         * Since we cannot return a value to ITypeInfo::Invoke to
         * indicate an exception condition, we'll use our Exception
         * function to raise them through the error info mechanism.
         */
        Exception(EXCEPTION_INVALIDSOUND);
        return ResultFromScode(DISP_E_EXCEPTION);
        }

    m_lSound=lSound;
    return NOERROR;
    }


/*
 * CBeeper::Beep
 *
 * Purpose:
 *  Function called from DispInvoke to invoke the Beep method.
 *
 * Out Parameter:
 *  plSoundPlayed   long *, the sound played.
 */

STDMETHODIMP CBeeper::Beep(long *plSoundPlayed)
    {
    if (NULL==plSoundPlayed)
        return ResultFromScode(E_POINTER);

    *plSoundPlayed=m_lSound;
    MessageBeep((UINT)m_lSound);
    return NOERROR;
    }



/*
 * CBeeper::Exception
 *
 * Purpose:
 *  Raises an exception for Invoke from within ITypeInfo::Invoke
 *  using the CreateErrorInfo API and the ICreateErrorInfo interface.
 *  This is part of CBeeper since CBeeper derives from IDispatch
 *  as well.
 *
 * Parameters:
 *  wException      WORD exception code.
 */

void CBeeper::Exception(WORD wException)
    {
    HRESULT             hr;
    ICreateErrorInfo   *pICreateErr;
    BOOL                fSuccess;
    LPTSTR              psz;
    LPOLESTR            pszHelp;
    UINT                idsSource;
    UINT                idsException;
    DWORD               dwHelpID;
    LANGID              langID=LANG_NEUTRAL;
   #ifdef WIN32
    LANGID             *pLangID;
   #endif

   #ifdef WIN32
    pLangID=(LANGID *)TlsGetValue(g_dwTLS);

    if (NULL!=pLangID)
        langID=*pLangID;
   #endif

    /*
     * Thread-safe exception handling means that we call
     * CreateErrorInfo which gives us an ICreateErrorInfo pointer
     * that we then use to set the error information (basically
     * to set the fields of an EXCEPINFO structure.  We then
     * call SetErrorInfo to attach this error to the current
     * thread.  ITypeInfo::Invoke will look for this when it
     * returns from whatever function was invokes by calling
     * GetErrorInfo.
     */

    //Not much we can do if this fails.
    if (FAILED(CreateErrorInfo(&pICreateErr)))
        return;

    psz=(LPTSTR)malloc(1024*sizeof(TCHAR));

    if (NULL==psz)
        {
        pICreateErr->Release();
        return;
        }

    fSuccess=FALSE;

    switch (wException)
        {
        case EXCEPTION_INVALIDSOUND:
            pICreateErr->SetGUID(IID_IBeeper);

            dwHelpID=HID_SOUND_PROPERTY_LIMITATIONS;

            pszHelp=OLETEXT("beep0000.hlp");
            idsSource=IDS_0_EXCEPTIONSOURCE;
            idsException=IDS_0_EXCEPTIONINVALIDSOUND;

            switch (langID)
                {
                case LANG_GERMAN:
                    idsSource=IDS_7_EXCEPTIONSOURCE;
                    idsException=IDS_7_EXCEPTIONINVALIDSOUND;
                    pszHelp=OLETEXT("beep0007.hlp");
                    break;

                case LANG_ENGLISH:
                case LANG_NEUTRAL:
                default:
                    break;
                }

            fSuccess=TRUE;
            break;

        default:
            break;
        }


    if (fSuccess)
        {
        IErrorInfo *pIErr;

        /*
         * If you have a help file, call the functions
         * ICreateErrorInfo::SetHelpFile and
         * ICreateErrorInfo::SetHelpContext as well.  If you
         * set the help file to NULL the context is ignored.
         */
        pICreateErr->SetHelpFile(pszHelp);
        pICreateErr->SetHelpContext(dwHelpID);

       #ifdef WIN32ANSI
        OLECHAR     szTemp[256];

        LoadString(g_hInst, idsSource, psz, 256);
        MultiByteToWideChar(CP_ACP, 0, psz, -1, szTemp, 256);
        pICreateErr->SetSource(szTemp);

        LoadString(g_hInst, idsException, psz, 256);
        MultiByteToWideChar(CP_ACP, 0, psz, -1, szTemp, 256);
        pICreateErr->SetDescription(szTemp);
       #else
        LoadString(g_hInst, idsSource, psz, 1024);
        pICreateErr->SetSource(psz);

        LoadString(g_hInst, idsException, psz, 1024);
        pICreateErr->SetDescription(psz);
       #endif

        hr=pICreateErr->QueryInterface(IID_IErrorInfo
            , (PPVOID)&pIErr);

        if (SUCCEEDED(hr))
            {
            SetErrorInfo(0L, pIErr);
            pIErr->Release();
            }
        }

    free(psz);

    //SetErrorInfo holds the object's IErrorInfo
    pICreateErr->Release();
    return;
    }






//ISupportErrorInfo interface implementation

/*
 * CImpISupportErrorInfo::CImpISupportErrorInfo
 * CImpISupportErrorInfo::~CImpISupportErrorInfo
 *
 * Parameters (Constructor):
 *  pObj            PCBeeper of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpISupportErrorInfo::CImpISupportErrorInfo(PCBeeper pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpISupportErrorInfo::~CImpISupportErrorInfo(void)
    {
    return;
    }



/*
 * CImpISupportErrorInfo::QueryInterface
 * CImpISupportErrorInfo::AddRef
 * CImpISupportErrorInfo::Release
 *
 * Purpose:
 *  IUnknown members for CImpISupportErrorInfo object.
 */

STDMETHODIMP CImpISupportErrorInfo::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpISupportErrorInfo::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpISupportErrorInfo::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpISupportErrorInfo::InterfaceSupportsErrorInfo
 *
 * Purpose:
 *  Informs a caller whether or not a specific interface
 *  supports exceptions through the Set/GetErrorInfo mechanism.
 *
 * Parameters:
 *  riid            REFIID of the interface in question.
 *
 * Return Value:
 *  HRESULT         NOERROR if a call to GetErrorInfo will succeed
 *                  for callers of riid.  S_FALSE if not.
 */

STDMETHODIMP CImpISupportErrorInfo::InterfaceSupportsErrorInfo
    (REFIID riid)
    {
    if (IID_IBeeper==riid)
        return NOERROR;

    return ResultFromScode(S_FALSE);
    }
