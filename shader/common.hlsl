

//*****************************************************************************
// �萔�o�b�t�@
//*****************************************************************************

// �}�g���N�X�o�b�t�@
cbuffer ConstantBuffer : register( b0 )
{
	matrix WorldViewProjection;
}

// �}�e���A���o�b�t�@
cbuffer MaterialBuffer : register( b1 )
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	float3		Dummy;//16bit���E�p
}



