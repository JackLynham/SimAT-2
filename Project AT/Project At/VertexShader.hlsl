struct VSOut
{
	float3 color : Color;
	float4 pos : SV_Position;
};

cbuffer CBuf
{
	row_major matrix transform; //Needs to be Row Major for Objects not to be stretched
};


VSOut main(float2 pos : Position, float3 color : Color)
{
	VSOut vso;
	vso.pos = mul(float4(pos.x, pos.y, 0.0f, 1.0f), transform);//Mul allows us to multiply by the vertices
	vso.color = color;
	return vso;
}