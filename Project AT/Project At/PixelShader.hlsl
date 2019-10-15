cbuffer CBuf
{
	float4 face_colors[6];  //Aray of colours
};
float4 main(uint tid :SV_PrimitiveID) : SV_Target
{
		return face_colors[tid / 2];    //tid stands for triangle
}