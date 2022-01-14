
#include "rpcproxy.h"
#include "ikoala.h"


extern const MIDL_FORMAT_STRING __MIDLFormatString;

extern const MIDL_FORMAT_STRING __MIDLProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT __stdcall IKoala_ClimbEucalyptusTree_Proxy( 
    IKoala __RPC_FAR * This,
    /* [in] */ short iTree)
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
            
            
            
            
            _StubMsg.BufferLength = 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = iTree;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[0] );
            
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
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IKoala_ClimbEucalyptusTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short iTree;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[0] );
        
        iTree = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IKoala *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ClimbEucalyptusTree((IKoala *) ((CStdStubBuffer *)This)->pvServerObject,iTree);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


void __stdcall IKoala_PouchOpensDown_Proxy( 
    IKoala __RPC_FAR * This)
{

    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        
        _StubMsg.BufferLength = 0U;
        NdrProxyGetBuffer(This, &_StubMsg);
        NdrProxySendReceive(This, &_StubMsg);
        
        }
    RpcFinally
        {
        NdrProxyFreeBuffer(This, &_StubMsg);
        
        }
    RpcEndFinally
    
}

void __RPC_STUB IKoala_PouchOpensDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER_NO_HRESULT;
        (((IKoala *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> PouchOpensDown((IKoala *) ((CStdStubBuffer *)This)->pvServerObject);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IKoala_SleepAfterEating_Proxy( 
    IKoala __RPC_FAR * This,
    /* [in] */ short cMinutes)
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
            
            
            
            
            _StubMsg.BufferLength = 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = cMinutes;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[0] );
            
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
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IKoala_SleepAfterEating_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short cMinutes;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[0] );
        
        cMinutes = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IKoala *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SleepAfterEating((IKoala *) ((CStdStubBuffer *)This)->pvServerObject,cMinutes);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
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


const CInterfaceProxyVtbl _IKoalaProxyVtbl = 
{
    &IID_IKoala,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy,
    IKoala_ClimbEucalyptusTree_Proxy,
    IKoala_PouchOpensDown_Proxy,
    IKoala_SleepAfterEating_Proxy
};
static const PRPC_STUB_FUNCTION IKoala_table[] =
{
    0,
    0,
    0,
    IKoala_ClimbEucalyptusTree_Stub,
    IKoala_PouchOpensDown_Stub,
    IKoala_SleepAfterEating_Stub
};

const CInterfaceStubVtbl _IKoalaStubVtbl =
{
    &IID_IKoala,
    0,
    6,
    IKoala_table,
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
			0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/*  2 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  4 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const MIDL_FORMAT_STRING __MIDLFormatString =
    {
        0,
        {

			0x0
        }
    };

const CInterfaceProxyVtbl * _ikoala_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IKoalaProxyVtbl,
    0
};

const CInterfaceStubVtbl * _ikoala_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IKoalaStubVtbl,
    0
};

PCInterfaceName _ikoala_InterfaceNamesList[] = 
{
    "IKoala",
    0
};

const ExtendedProxyFileInfo ikoala_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ikoala_ProxyVtblList, 
    (PCInterfaceStubVtblList *) & _ikoala_StubVtblList, 
     (const PCInterfaceName * ) & _ikoala_InterfaceNamesList 
};
