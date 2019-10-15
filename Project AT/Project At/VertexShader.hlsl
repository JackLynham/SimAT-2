cbuffer CBuf
{						// This has to match in Graphics as DX Maths are row Makor
	 matrix transform; //Needs to be Row Major for Objects not to be stretched
};


float4 main(float3 pos : Position) :SV_Position
{
	 return mul(float4(pos,1.0f), transform);//Mul allows us to multiply by the vertices
	
}