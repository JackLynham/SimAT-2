#pragma once
#include "Graphics.h"
#include "SolidSphere.h"
#include "ConstantBuffer.h"

class PointLight
{
public:
	PointLight(Graphics& gfx, float radius = 0.5f);
	void SpawnControlWindow() noexcept;
	void Reset() noexcept;
	void Draw(Graphics& gfx) const noexcept;
	void Bind(Graphics& gfx, DirectX::FXMMATRIX view) const noexcept;
private:
	struct PointLightCBuf
	{
		
		alignas(16) DirectX::XMFLOAT3 pos;
	 /* Pixel shader expect 16 bit values so Alignas 16 allows us to allign it to 16 bites  */
		alignas(16)DirectX::XMFLOAT3 ambient;
		alignas(16)DirectX::XMFLOAT3 diffuseColor;

		float diffuseIntensity;
		float attConst;
		float attlin;
		float attquad;
	};
private:
	PointLightCBuf cbData; //This is used to manage the above data in struct
	//mutable SolidSphere mesh;
	//mutable PixelConstantBuffer<PointLightCBuf> cbuf;
};