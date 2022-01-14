
#include "rpcproxy.h"
#include "ianimal.h"


extern const MIDL_FORMAT_STRING __MIDLFormatString;

extern const MIDL_FORMAT_STRING __MIDLProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT __stdcall IAnimal_Eat_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [in] */ LPTSTR pszFoodRecommended,
    /* [out][in] */ LPTSTR pszFoodEaten,
    /* [in] */ short cchEaten)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
            
            
            
            
            _StubMsg.BufferLength = 12U + 14U + 4U;
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pszFoodRecommended,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[0] );
            
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pszFoodEaten,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[0] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pszFoodRecommended,
                                (PFORMAT_STRING) &__MIDLFormatString.Format[0] );
            
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pszFoodEaten,
                                (PFORMAT_STRING) &__MIDLFormatString.Format[0] );
            
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = cchEaten;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[0] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pszFoodEaten,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[0],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(1)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[0],
                         ( void __RPC_FAR * )pszFoodEaten);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAnimal_Eat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short cchEaten;
    LPTSTR pszFoodEaten;
    LPTSTR pszFoodRecommended;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    pszFoodRecommended = 0;
    pszFoodEaten = 0;
    RpcTryFinally
        {
        NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[0] );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&pszFoodRecommended,
                              (PFORMAT_STRING) &__MIDLFormatString.Format[0],
                              (unsigned char)0 );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&pszFoodEaten,
                              (PFORMAT_STRING) &__MIDLFormatString.Format[0],
                              (unsigned char)0 );
        
        cchEaten = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAnimal *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Eat(
       (IAnimal *) ((CStdStubBuffer *)This)->pvServerObject,
       pszFoodRecommended,
       pszFoodEaten,
       cchEaten);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 12U + 10U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)pszFoodEaten,
                              (PFORMAT_STRING) &__MIDLFormatString.Format[0] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)pszFoodEaten,
                            (PFORMAT_STRING) &__MIDLFormatString.Format[0] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IAnimal_Sleep_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [out][in] */ short __RPC_FAR *pcMinutes)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
            
            
            
            
            _StubMsg.BufferLength = 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = *pcMinutes;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[12] );
            
            *pcMinutes = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer += 2;
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(1)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[4],
                         ( void __RPC_FAR * )pcMinutes);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAnimal_Sleep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short __RPC_FAR *pcMinutes;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    pcMinutes = 0;
    RpcTryFinally
        {
        NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[12] );
        
        pcMinutes = ( short __RPC_FAR * )_StubMsg.Buffer;
        _StubMsg.Buffer += sizeof( short  );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAnimal *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Sleep((IAnimal *) ((CStdStubBuffer *)This)->pvServerObject,pcMinutes);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 2U + 6U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( short __RPC_FAR * )_StubMsg.Buffer)++ = *pcMinutes;
        
        _StubMsg.Buffer += 2;
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IAnimal_Procreate_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [out] */ short __RPC_FAR *pcOffspring)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
            
            
            
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[18] );
            
            *pcOffspring = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer += 2;
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(1)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[8],
                         ( void __RPC_FAR * )pcOffspring);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAnimal_Procreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    short _M4;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short __RPC_FAR *pcOffspring;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    pcOffspring = 0;
    RpcTryFinally
        {
        pcOffspring = &_M4;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAnimal *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Procreate((IAnimal *) ((CStdStubBuffer *)This)->pvServerObject,pcOffspring);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 2U + 6U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( short __RPC_FAR * )_StubMsg.Buffer)++ = *pcOffspring;
        
        _StubMsg.Buffer += 2;
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IAnimal_WhatKindOfAnimal_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [out] */ IID __RPC_FAR *pIID)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    memset(
          pIID,
          0,
          sizeof( IID  ));
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
            
            
            
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[24] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pIID,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[12],
                                  (unsigned char)0 );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(1)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[12],
                         ( void __RPC_FAR * )pIID);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAnimal_WhatKindOfAnimal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IID _pIIDM;
    IID __RPC_FAR *pIID;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    pIID = 0;
    RpcTryFinally
        {
        pIID = &_pIIDM;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAnimal *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> WhatKindOfAnimal((IAnimal *) ((CStdStubBuffer *)This)->pvServerObject,pIID);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)pIID,
                              (PFORMAT_STRING) &__MIDLFormatString.Format[12] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)pIID,
                            (PFORMAT_STRING) &__MIDLFormatString.Format[12] );
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pIID,
                        &__MIDLFormatString.Format[12] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDLFormatString.Format,
    0, /* -error bounds_check flag */
    0x10001, /* Ndr library version */
    0, /* Reserved */
    0, /* Reserved */
    0  /* Reserved */
    };


const CInterfaceProxyVtbl _IAnimalProxyVtbl = 
{
    &IID_IAnimal,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy,
    IAnimal_Eat_Proxy,
    IAnimal_Sleep_Proxy,
    IAnimal_Procreate_Proxy,
    IAnimal_WhatKindOfAnimal_Proxy
};
static const PRPC_STUB_FUNCTION IAnimal_table[] =
{
    0,
    0,
    0,
    IAnimal_Eat_Stub,
    IAnimal_Sleep_Stub,
    IAnimal_Procreate_Stub,
    IAnimal_WhatKindOfAnimal_Stub
};

const CInterfaceStubVtbl _IAnimalStubVtbl =
{
    &IID_IAnimal,
    0,
    7,
    IAnimal_table,
    CStdStubBuffer_QueryInterface,
    CStdStubBuffer_AddRef,
    CStdStubBuffer_Release,
    CStdStubBuffer_Connect,
    CStdStubBuffer_Disconnect,
    CStdStubBuffer_Invoke,
    CStdStubBuffer_IsIIDSupported,
    CStdStubBuffer_CountRefs,
    CStdStubBuffer_DebugServerQueryInterface,
    CStdStubBuffer_DebugServerRelease
};

static const MIDL_FORMAT_STRING __MIDLProcFormatString =
    {
        0,
        {
			
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* 1 */
/*  2 */	0x0, 0x0,	/* Type Offset=0 */
/*  4 */	
			0x50,		/* FC_IN_OUT_PARAM */
			0x1,		/* 1 */
/*  6 */	0x0, 0x0,	/* Type Offset=0 */
/*  8 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 10 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 12 */	
			0x50,		/* FC_IN_OUT_PARAM */
			0x1,		/* 1 */
/* 14 */	0x4, 0x0,	/* Type Offset=4 */
/* 16 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 18 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* 1 */
/* 20 */	0x8, 0x0,	/* Type Offset=8 */
/* 22 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 24 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* 1 */
/* 26 */	0xc, 0x0,	/* Type Offset=12 */
/* 28 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_FORMAT_STRING __MIDLFormatString =
    {
        0,
        {
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  2 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/*  4 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  6 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/*  8 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 10 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 12 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 14 */	0x8, 0x0,	/* Offset= 8 (22) */
/* 16 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 18 */	0x8, 0x0,	/* 8 */
/* 20 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 22 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 24 */	0x10, 0x0,	/* 16 */
/* 26 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 28 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 30 */	0x0,		/* 0 */
			0xf1, 0xff,	/* Offset= -15 (16) */
			0x5b,		/* FC_END */

			0x0
        }
    };

const CInterfaceProxyVtbl * _ianimal_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IAnimalProxyVtbl,
    0
};

const CInterfaceStubVtbl * _ianimal_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IAnimalStubVtbl,
    0
};

PCInterfaceName _ianimal_InterfaceNamesList[] = 
{
    "IAnimal",
    0
};

const ExtendedProxyFileInfo ianimal_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ianimal_ProxyVtblList, 
    (PCInterfaceStubVtblList *) & _ianimal_StubVtblList, 
     (const PCInterfaceName * ) & _ianimal_InterfaceNamesList 
};
