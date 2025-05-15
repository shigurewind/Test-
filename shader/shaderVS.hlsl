
#include "common.hlsl"

//*****************************************************************************
// �萔�o�b�t�@
//*****************************************************************************

//=============================================================================
// ���_�V�F�[�_
//=============================================================================
void main( in  float4 inPosition	: POSITION0,	//���_���W
		   in  float4 inNormal		: NORMAL0,		//���_�@��
		   in  float4 inDiffuse		: COLOR0,		//���_�J���[
		   in  float2 inTexCoord	: TEXCOORD0,	//�e�N�X�`�����W

		   out float4 outPosition	: SV_POSITION,	//�ϊ��㒸�_���W
		   out float4 outNormal		: NORMAL0,		//���_�@��
		   out float4 outDiffuse	: COLOR0,		//���_�J���[
		   out float2 outTexCoord	: TEXCOORD0		 //�e�N�X�`�����W
		)
{
	//���_���W��WVP�ϊ����ďo��
	outPosition = mul( inPosition, WorldViewProjection );
	//�@�����o��
	outNormal =	inNormal;
	//�e�N�X�`�����W���o��
	outTexCoord = inTexCoord;
	//���_�J���[�ƃ}�e���A���F���������ďo��
	outDiffuse = inDiffuse * Diffuse;

}


