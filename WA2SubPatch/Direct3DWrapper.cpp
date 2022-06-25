#include "Direct3DWrapper.h"
#include "GameHooks.h"

Direct3DDeviceWrapper::Direct3DDeviceWrapper(IDirect3DDevice9* orig)
{
	// member variables left uninitialized should be fine because this is a pass-through.
	// we'll see though :)
	this->orig = orig;
	initSub(orig);
}

Direct3DWrapper::Direct3DWrapper(IDirect3D9* orig)
{
	// member variables left uninitialized should be fine because this is a pass-through.
	// we'll see though :)
	this->orig = orig;
}

HRESULT Direct3DDeviceWrapper::EndScene(void)
{
	update();
	return orig->EndScene();
}

HRESULT Direct3DWrapper::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface)
{
	HRESULT hres = orig->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
	if (hres == D3D_OK)
	{
		*ppReturnedDeviceInterface = new Direct3DDeviceWrapper(*ppReturnedDeviceInterface);
		setGameHooks();
	}

	return hres;
}

ULONG Direct3DWrapper::Release(void)
{
	ULONG result = orig->Release();
	delete this;
	return result;
}

ULONG Direct3DDeviceWrapper::Release(void)
{
	ULONG result = orig->Release();
	delete this;
	return result;
}

/* auto-generated stuff */

HRESULT Direct3DDeviceWrapper::QueryInterface(REFIID riid, void** ppvObj)
{
	return orig->QueryInterface(riid, ppvObj);
}

ULONG Direct3DDeviceWrapper::AddRef(void)
{
	return orig->AddRef();
}

HRESULT Direct3DDeviceWrapper::TestCooperativeLevel(void)
{
	return orig->TestCooperativeLevel();
}

UINT Direct3DDeviceWrapper::GetAvailableTextureMem(void)
{
	return orig->GetAvailableTextureMem();
}

HRESULT Direct3DDeviceWrapper::EvictManagedResources(void)
{
	return orig->EvictManagedResources();
}

HRESULT Direct3DDeviceWrapper::GetDirect3D(IDirect3D9** ppD3D9)
{
	return orig->GetDirect3D(ppD3D9);
}

HRESULT Direct3DDeviceWrapper::GetDeviceCaps(D3DCAPS9* pCaps)
{
	return orig->GetDeviceCaps(pCaps);
}

HRESULT Direct3DDeviceWrapper::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	return orig->GetDisplayMode(iSwapChain, pMode);
}

HRESULT Direct3DDeviceWrapper::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters)
{
	return orig->GetCreationParameters(pParameters);
}

HRESULT Direct3DDeviceWrapper::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
	return orig->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void Direct3DDeviceWrapper::SetCursorPosition(int X, int Y, DWORD Flags)
{
	return orig->SetCursorPosition(X, Y, Flags);
}

BOOL Direct3DDeviceWrapper::ShowCursor(BOOL bShow)
{
	return orig->ShowCursor(bShow);
}

HRESULT Direct3DDeviceWrapper::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
	return orig->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT Direct3DDeviceWrapper::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
	return orig->GetSwapChain(iSwapChain, pSwapChain);
}

UINT Direct3DDeviceWrapper::GetNumberOfSwapChains(void)
{
	return orig->GetNumberOfSwapChains();
}

HRESULT Direct3DDeviceWrapper::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return orig->Reset(pPresentationParameters);
}

HRESULT Direct3DDeviceWrapper::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	return orig->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT Direct3DDeviceWrapper::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	return orig->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT Direct3DDeviceWrapper::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	return orig->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT Direct3DDeviceWrapper::SetDialogBoxMode(BOOL bEnableDialogs)
{
	return orig->SetDialogBoxMode(bEnableDialogs);
}

void Direct3DDeviceWrapper::SetGammaRamp(UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	return orig->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void Direct3DDeviceWrapper::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	return orig->GetGammaRamp(iSwapChain, pRamp);
}

HRESULT Direct3DDeviceWrapper::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	return orig->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

HRESULT Direct3DDeviceWrapper::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	return orig->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT Direct3DDeviceWrapper::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	return orig->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT Direct3DDeviceWrapper::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	return orig->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT Direct3DDeviceWrapper::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	return orig->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT Direct3DDeviceWrapper::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return orig->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT Direct3DDeviceWrapper::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return orig->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT Direct3DDeviceWrapper::UpdateSurface(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint)
{
	return orig->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT Direct3DDeviceWrapper::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
	return orig->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT Direct3DDeviceWrapper::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	return orig->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT Direct3DDeviceWrapper::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	return orig->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT Direct3DDeviceWrapper::StretchRect(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return orig->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT Direct3DDeviceWrapper::ColorFill(IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color)
{
	return orig->ColorFill(pSurface, pRect, color);
}

HRESULT Direct3DDeviceWrapper::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return orig->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT Direct3DDeviceWrapper::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	return orig->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT Direct3DDeviceWrapper::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	return orig->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT Direct3DDeviceWrapper::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	return orig->SetDepthStencilSurface(pNewZStencil);
}

HRESULT Direct3DDeviceWrapper::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	return orig->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT Direct3DDeviceWrapper::BeginScene(void)
{
	return orig->BeginScene();
}

HRESULT Direct3DDeviceWrapper::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return orig->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT Direct3DDeviceWrapper::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return orig->SetTransform(State, pMatrix);
}

HRESULT Direct3DDeviceWrapper::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	return orig->GetTransform(State, pMatrix);
}

HRESULT Direct3DDeviceWrapper::MultiplyTransform(D3DTRANSFORMSTATETYPE state, CONST D3DMATRIX* matrix)
{
	return orig->MultiplyTransform(state, matrix);
}

HRESULT Direct3DDeviceWrapper::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
	return orig->SetViewport(pViewport);
}

HRESULT Direct3DDeviceWrapper::GetViewport(D3DVIEWPORT9* pViewport)
{
	return orig->GetViewport(pViewport);
}

HRESULT Direct3DDeviceWrapper::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	return orig->SetMaterial(pMaterial);
}

HRESULT Direct3DDeviceWrapper::GetMaterial(D3DMATERIAL9* pMaterial)
{
	return orig->GetMaterial(pMaterial);
}

HRESULT Direct3DDeviceWrapper::SetLight(DWORD Index, CONST D3DLIGHT9* light)
{
	return orig->SetLight(Index, light);
}

HRESULT Direct3DDeviceWrapper::GetLight(DWORD Index, D3DLIGHT9* light)
{
	return orig->GetLight(Index, light);
}

HRESULT Direct3DDeviceWrapper::LightEnable(DWORD Index, BOOL Enable)
{
	return orig->LightEnable(Index, Enable);
}

HRESULT Direct3DDeviceWrapper::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return orig->GetLightEnable(Index, pEnable);
}

HRESULT Direct3DDeviceWrapper::SetClipPlane(DWORD Index, CONST float* pPlane)
{
	return orig->SetClipPlane(Index, pPlane);
}

HRESULT Direct3DDeviceWrapper::GetClipPlane(DWORD Index, float* pPlane)
{
	return orig->GetClipPlane(Index, pPlane);
}

HRESULT Direct3DDeviceWrapper::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return orig->SetRenderState(State, Value);
}

HRESULT Direct3DDeviceWrapper::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return orig->GetRenderState(State, pValue);
}

HRESULT Direct3DDeviceWrapper::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	return orig->CreateStateBlock(Type, ppSB);
}

HRESULT Direct3DDeviceWrapper::BeginStateBlock(void)
{
	return orig->BeginStateBlock();
}

HRESULT Direct3DDeviceWrapper::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	return orig->EndStateBlock(ppSB);
}

HRESULT Direct3DDeviceWrapper::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
	return orig->SetClipStatus(pClipStatus);
}

HRESULT Direct3DDeviceWrapper::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
	return orig->GetClipStatus(pClipStatus);
}

HRESULT Direct3DDeviceWrapper::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
	return orig->GetTexture(Stage, ppTexture);
}

HRESULT Direct3DDeviceWrapper::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	return orig->SetTexture(Stage, pTexture);
}

HRESULT Direct3DDeviceWrapper::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return orig->GetTextureStageState(Stage, Type, pValue);
}

HRESULT Direct3DDeviceWrapper::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return orig->SetTextureStageState(Stage, Type, Value);
}

HRESULT Direct3DDeviceWrapper::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	return orig->GetSamplerState(Sampler, Type, pValue);
}

HRESULT Direct3DDeviceWrapper::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return orig->SetSamplerState(Sampler, Type, Value);
}

HRESULT Direct3DDeviceWrapper::ValidateDevice(DWORD* pNumPasses)
{
	return orig->ValidateDevice(pNumPasses);
}

HRESULT Direct3DDeviceWrapper::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return orig->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT Direct3DDeviceWrapper::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return orig->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT Direct3DDeviceWrapper::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return orig->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT Direct3DDeviceWrapper::GetCurrentTexturePalette(UINT* PaletteNumber)
{
	return orig->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT Direct3DDeviceWrapper::SetScissorRect(CONST RECT* pRect)
{
	return orig->SetScissorRect(pRect);
}

HRESULT Direct3DDeviceWrapper::GetScissorRect(RECT* pRect)
{
	return orig->GetScissorRect(pRect);
}

HRESULT Direct3DDeviceWrapper::SetSoftwareVertexProcessing(BOOL bSoftware)
{
	return orig->SetSoftwareVertexProcessing(bSoftware);
}

BOOL Direct3DDeviceWrapper::GetSoftwareVertexProcessing(void)
{
	return orig->GetSoftwareVertexProcessing();
}

HRESULT Direct3DDeviceWrapper::SetNPatchMode(float nSegments)
{
	return orig->SetNPatchMode(nSegments);
}

float Direct3DDeviceWrapper::GetNPatchMode(void)
{
	return orig->GetNPatchMode();
}

HRESULT Direct3DDeviceWrapper::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return orig->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT Direct3DDeviceWrapper::DrawIndexedPrimitive(D3DPRIMITIVETYPE prim, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return orig->DrawIndexedPrimitive(prim, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT Direct3DDeviceWrapper::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return orig->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT Direct3DDeviceWrapper::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return orig->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT Direct3DDeviceWrapper::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	return orig->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT Direct3DDeviceWrapper::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	return orig->CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT Direct3DDeviceWrapper::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	return orig->SetVertexDeclaration(pDecl);
}

HRESULT Direct3DDeviceWrapper::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	return orig->GetVertexDeclaration(ppDecl);
}

HRESULT Direct3DDeviceWrapper::SetFVF(DWORD FVF)
{
	return orig->SetFVF(FVF);
}

HRESULT Direct3DDeviceWrapper::GetFVF(DWORD* pFVF)
{
	return orig->GetFVF(pFVF);
}

HRESULT Direct3DDeviceWrapper::CreateVertexShader(CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	return orig->CreateVertexShader(pFunction, ppShader);
}

HRESULT Direct3DDeviceWrapper::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	return orig->SetVertexShader(pShader);
}

HRESULT Direct3DDeviceWrapper::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	return orig->GetVertexShader(ppShader);
}

HRESULT Direct3DDeviceWrapper::SetVertexShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return orig->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT Direct3DDeviceWrapper::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return orig->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT Direct3DDeviceWrapper::SetVertexShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return orig->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT Direct3DDeviceWrapper::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return orig->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT Direct3DDeviceWrapper::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT BoolCount)
{
	return orig->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT Direct3DDeviceWrapper::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return orig->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT Direct3DDeviceWrapper::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	return orig->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT Direct3DDeviceWrapper::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* OffsetInBytes, UINT* pStride)
{
	return orig->GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride);
}

HRESULT Direct3DDeviceWrapper::SetStreamSourceFreq(UINT StreamNumber, UINT Divider)
{
	return orig->SetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT Direct3DDeviceWrapper::GetStreamSourceFreq(UINT StreamNumber, UINT* Divider)
{
	return orig->GetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT Direct3DDeviceWrapper::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	return orig->SetIndices(pIndexData);
}

HRESULT Direct3DDeviceWrapper::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	return orig->GetIndices(ppIndexData);
}

HRESULT Direct3DDeviceWrapper::CreatePixelShader(CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	return orig->CreatePixelShader(pFunction, ppShader);
}

HRESULT Direct3DDeviceWrapper::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	return orig->SetPixelShader(pShader);
}

HRESULT Direct3DDeviceWrapper::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	return orig->GetPixelShader(ppShader);
}

HRESULT Direct3DDeviceWrapper::SetPixelShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return orig->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT Direct3DDeviceWrapper::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return orig->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT Direct3DDeviceWrapper::SetPixelShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return orig->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT Direct3DDeviceWrapper::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return orig->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT Direct3DDeviceWrapper::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT BoolCount)
{
	return orig->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT Direct3DDeviceWrapper::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return orig->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT Direct3DDeviceWrapper::DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return orig->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT Direct3DDeviceWrapper::DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return orig->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT Direct3DDeviceWrapper::DeletePatch(UINT Handle)
{
	return orig->DeletePatch(Handle);
}

HRESULT Direct3DDeviceWrapper::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	return orig->CreateQuery(Type, ppQuery);
}

HRESULT Direct3DWrapper::QueryInterface(REFIID riid, void** ppvObj)
{
	return orig->QueryInterface(riid, ppvObj);
}

ULONG Direct3DWrapper::AddRef(void)
{
	return orig->AddRef();
}

HRESULT Direct3DWrapper::RegisterSoftwareDevice(void* pInitializeFunction)
{
	return orig->RegisterSoftwareDevice(pInitializeFunction);
}

UINT Direct3DWrapper::GetAdapterCount(void)
{
	return orig->GetAdapterCount();
}

HRESULT Direct3DWrapper::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier)
{
	return orig->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT Direct3DWrapper::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
	return orig->GetAdapterModeCount(Adapter, Format);
}

HRESULT Direct3DWrapper::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)
{
	return orig->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT Direct3DWrapper::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
	return orig->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT Direct3DWrapper::CheckDeviceType(UINT iAdapter, D3DDEVTYPE DevType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
	return orig->CheckDeviceType(iAdapter, DevType, DisplayFormat, BackBufferFormat, bWindowed);
}

HRESULT Direct3DWrapper::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return orig->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT Direct3DWrapper::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels)
{
	return orig->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT Direct3DWrapper::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return orig->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT Direct3DWrapper::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
	return orig->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT Direct3DWrapper::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{
	return orig->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR Direct3DWrapper::GetAdapterMonitor(UINT Adapter)
{
	return orig->GetAdapterMonitor(Adapter);
}