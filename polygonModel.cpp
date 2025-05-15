/*==============================================================================

   ���_�Ǘ� [polygon3D.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygonModel.h"
#include "sprite.h"
#include "Camera.h"
#include "texture.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//�J�����͕�������ƃ_���Ȃ̂ŊO��
static	ObjectModel	g_Object1;		//3D�|���S���I�u�W�F�N�g�\����
static	ID3D11VertexShader* g_VertexShader;	//���_�V�F�[�_�[�I�u�W�F�N�g�|�C���^
static	ID3D11PixelShader* g_PixelShader;	//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�|�C���^
static	ID3D11InputLayout* g_VertexLayout;	//���_���C�A�E�g�I�u�W�F�N�g�|�C���^

static	MODEL* PlayerModel;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygonModel(void)
{

	//�V�F�[�_�[�ǂݍ���
	CreateVertexShader(&g_VertexShader, &g_VertexLayout, "shaderVS.cso");
	CreatePixelShader(&g_PixelShader, "shaderPS.cso");

	//3D�I�u�W�F�N�g�Ǘ��\���̂̏�����
	g_Object1.Position = XMFLOAT3(0.0f, 0.0f, 1.0f);
	g_Object1.Rotate = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Object1.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);



	//���f���ǂݍ���
	PlayerModel = ModelLoad("asset\\model\\test.fbx");




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void FinalizePolygonModel(void)
{
	//��������̂����
	g_VertexShader->Release();
	g_VertexLayout->Release();
	g_PixelShader->Release();

	ModelRelease(PlayerModel);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygonModel(void)
{
	//�K���ɉ�]
	g_Object1.Rotate.y += 0.3f;
	g_Object1.Rotate.x += 0.1f;

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygonModel(void)
{
	//���_���C�A�E�g��ݒ�
	GetDeviceContext()->IASetInputLayout(g_VertexLayout);
	//���_�V�F�[�_�[���Z�b�g
	GetDeviceContext()->VSSetShader(g_VertexShader, NULL, 0);
	//�s�N�Z���V�F�[�_�[���Z�b�g
	GetDeviceContext()->PSSetShader(g_PixelShader, NULL, 0);

	//3D�p�s��ݒ�
	//ResetWorldViewProjection3D();//3D�`��ɐ؂�ւ���
	SetDepthEnable(true);		//���s�������L��

	//�J�����͋��L�̏�񂪐ݒ肳��Ă���Ƃ���

	{//3D�|���S���P���̏���
		//�e�N�X�`�����Z�b�g
		ID3D11ShaderResourceView* tex = GetTexture(g_Object1.TexID);
		GetDeviceContext()->PSSetShaderResources(0, 1, &tex);

		//���s�ړ��s��쐬
		XMMATRIX	TranslationMatrix =
			XMMatrixTranslation(
				g_Object1.Position.x,
				g_Object1.Position.y,
				g_Object1.Position.z
			);
		//��]�s��쐬
		XMMATRIX	RotationMatrix =
			XMMatrixRotationRollPitchYaw(
				XMConvertToRadians(g_Object1.Rotate.x),
				XMConvertToRadians(g_Object1.Rotate.y),
				XMConvertToRadians(g_Object1.Rotate.z)
			);
		//�X�P�[�����O�s��쐬
		XMMATRIX	ScalingMatrix =
			XMMatrixScaling(
				g_Object1.Scale.x,
				g_Object1.Scale.y,
				g_Object1.Scale.z
			);
		//���[���h�s��쐬 ����Z�̏��Ԃɒ���
		XMMATRIX	WorldMatrix =
			ScalingMatrix *
			RotationMatrix *
			TranslationMatrix;
		//DirectX�փZ�b�g
		SetWorldMatrix(WorldMatrix);

		//�v���~�e�B�u�g�|���W�[�̐ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);
		//�}�e���A���ݒ�
		MATERIAL	material;
		ZeroMemory(&material, sizeof(MATERIAL));
		material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		SetMaterial(material);

		//�`��
		ModelDraw(PlayerModel);
	}


}
