#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include "Window.h"

class RGraphics
{
public:
	RGraphics();
	~RGraphics();

	// D3D devices and viewport
	static ID3D11Device* Device;
	static ID3D11DeviceContext* Context;
	static D3D11_VIEWPORT Viewport;

	// === Main Methods ===
	bool Initialize(CWindow* Window);
	void SetVerticalSynchronization(bool Enable);
	void ClearBuffer();
	void PresentBuffer();

private:
	// Private attributes
	IDXGISwapChain* m_SwapChain;
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11BlendState* m_BlendState;
	D3D_FEATURE_LEVEL m_FeatureLevel;

	float m_BackgroundColor[4];
	bool m_VSync;
};

#endif
