#include "PCH.h"
#include "Graphics.h"

// Initialize static variables
ID3D11Device* Graphics::Device = nullptr;
ID3D11DeviceContext* Graphics::Context = nullptr;
D3D11_VIEWPORT Graphics::Viewport = { NULL };

Graphics::Graphics()
{
	// Initialize pointers and variables
	m_SwapChain = nullptr;
	m_RenderTargetView = nullptr;
	m_BlendState = nullptr;

	// Set D3D version
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	m_BackgroundColor[0] = 0.0f;
	m_BackgroundColor[1] = 0.0f;
	m_BackgroundColor[2] = 0.0f;
	m_BackgroundColor[3] = 0.0f;

	m_VSync = true;
}

Graphics::~Graphics()
{
	// Releasing all objects that we got
	if (m_BlendState)
	{
		m_BlendState->Release();
		m_BlendState = nullptr;
	}

	if (m_RenderTargetView)
	{
		m_RenderTargetView->Release();
		m_RenderTargetView = nullptr;
	}

	if (m_SwapChain)
	{
		m_SwapChain->SetFullscreenState(false, NULL);
		m_SwapChain->Release();
		m_SwapChain = nullptr;
	}

	if (Context)
	{
		Context->ClearState();
		Context->Release();
		Context = nullptr;
	}

	if (Device)
	{
		Device->Release();
		Device = nullptr;
	}
}

bool Graphics::Initialize(Window* Window)
{
	unsigned int CreateDeviceFlags = 0;

	// If DEBUG use "D3D_DEVICE_DEBUG"
	#ifdef _DEBUG
		CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	// Create D3D device
	if FAILED(D3D11CreateDevice
	(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		CreateDeviceFlags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&Device,
		&m_FeatureLevel,
		&Context
	))
	{
		// Create D3D device WARP
		if FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_WARP, NULL, CreateDeviceFlags, NULL, 0, D3D11_SDK_VERSION, &Device, &m_FeatureLevel, &Context)) { return false; }
		OutputDebugString("[INFO] Using WARP Adapter: Your GPU don't suports D3D11\n");
	}

	// Get window's background's color
	COLORREF Color = Window->GetBackgroundColor();
	m_BackgroundColor[0] = GetRValue(Color) / 255.0f;
	m_BackgroundColor[1] = GetGValue(Color) / 255.0f;
	m_BackgroundColor[2] = GetBValue(Color) / 255.0f;
	m_BackgroundColor[3] = 1.0f;

	// Get DXGI device
	IDXGIDevice* DXGIDevice = nullptr;
	if FAILED(Device->QueryInterface(__uuidof(IDXGIDevice), (void**) &DXGIDevice)) { return false; }

	// Get DXGI adapater
	IDXGIAdapter* DXGIAdapter = nullptr;
	if FAILED(DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**) &DXGIAdapter)) { return false; }

	// Get DXGI factory
	IDXGIFactory* DXGIFactory = nullptr;
	if FAILED(DXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**) &DXGIFactory)) { return false; }

	// Define and setup a swap chain
	DXGI_SWAP_CHAIN_DESC SwapDesc{ NULL };
	SwapDesc.BufferDesc.Width = static_cast<unsigned int>(Window->GetSize()[0]);
	SwapDesc.BufferDesc.Height = static_cast<unsigned int>(Window->GetSize()[1]);
	SwapDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapDesc.SampleDesc.Count = 1;
	SwapDesc.SampleDesc.Quality = 0;	
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapDesc.BufferCount = 2;
	SwapDesc.OutputWindow = Window->GetId();
	SwapDesc.Windowed = (Window->GetDisplayMode() != Window::EDisplayMode::Fullscreen);
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Create swap chain and associate it to a window
	if FAILED(DXGIFactory->CreateSwapChain(Device, &SwapDesc, &m_SwapChain)) { return false; }
	if FAILED(DXGIFactory->MakeWindowAssociation(Window->GetId(), DXGI_MWA_NO_ALT_ENTER)) { return false; }

	// Create render target view and associate it to the back buffer
	ID3D11Texture2D* BackBuffer = nullptr;
	if FAILED(m_SwapChain->GetBuffer(0, __uuidof(BackBuffer), (void**) &BackBuffer)) { return false; }
	if FAILED(Device->CreateRenderTargetView(BackBuffer, NULL, &m_RenderTargetView)) { return false; }
	
	// Set render targer view to the output merger
	Context->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);

	// Settup viewport
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = static_cast<FLOAT>(Window->GetSize()[0]);
	Viewport.Height = static_cast<FLOAT>(Window->GetSize()[1]);
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 0.0f;

	//Associate viewport to the rasterizer
	Context->RSSetViewports(1, &Viewport);

	// Define and settup a blend state
	D3D11_BLEND_DESC BlendDesc = { NULL };
	BlendDesc.AlphaToCoverageEnable = false;
	BlendDesc.IndependentBlendEnable = false;
	BlendDesc.RenderTarget[0].BlendEnable = true;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	// Create blend state
	if FAILED(Device->CreateBlendState(&BlendDesc, &m_BlendState)) { return false; }

	// Associate blend state to the output merger
	Context->OMSetBlendState(m_BlendState, nullptr, 0xffffffff);

	// Release got devices
	DXGIDevice->Release();
	DXGIAdapter->Release();
	DXGIFactory->Release();
	BackBuffer->Release();

	return true;
}

void Graphics::Synchronization(bool Enable)
{
	// Set V-Sync
	m_VSync = Enable;
}

void Graphics::ClearBuffer()
{
	// Clear back buffer
	Context->ClearRenderTargetView(m_RenderTargetView, m_BackgroundColor);
}

void Graphics::PresentBuffer()
{
	// Swap back buffer with front buffer
	m_SwapChain->Present(m_VSync, NULL);
	Context->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);
}
