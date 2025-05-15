
#include "common.hlsl"


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Texture2D		g_Texture : register( t0 );		//�e�N�X�`���ϐ�
SamplerState	g_SamplerState : register( s0 );//�T���v���[�ϐ�

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
void main( in  float4 inPosition	: POSITION0,	//�s�N�Z���̍��W
		   in  float4 inNormal		: NORMAL0,		//�s�N�Z���̖@��
		   in  float4 inDiffuse		: COLOR0,		//�s�N�Z���̃J���[
		   in float2  inTexCoord	: TEXCOORD0,	//�s�N�Z���̃e�N�X�`�����W
   		   out float4 outDiffuse	: SV_Target )	//�ŏI�I�ȃs�N�Z���̃J���[
{
	//�e�N�Z�����t�F�b�`���ďo��
	outDiffuse = g_Texture.Sample(g_SamplerState, inTexCoord);

}
