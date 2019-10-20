Texture2D tex; //Declare Texture

SamplerState splr;  //Sampler State that is binded

float4 main(float2 tc : TexCoord) : SV_Target //Take in interplated cordinate
{
	return tex.Sample(splr,tc);
}