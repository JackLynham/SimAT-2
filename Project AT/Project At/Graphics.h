#pragma once
#include "Win.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include "ChiliException.h"

class Graphics 
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void Draw(float angle, float x, float y);			//	(How many vertices, Where to start) 

	void VertexBuffer();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice; //Used for allocating Afectivly Create
	Microsoft::WRL::ComPtr <IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr <ID3D11DeviceContext> pContext; //Used for Issuing Rending Comands
	Microsoft::WRL::ComPtr <ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr <ID3D11DepthStencilView> pDSV;
};
