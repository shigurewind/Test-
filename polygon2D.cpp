/*==============================================================================

   ���_�Ǘ� [polygon2D.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon2D.h"
#include "sprite.h"
#include "Camera.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static	Object2D	g_Object1;				//2D�|���S���\����
static	ID3D11VertexShader* g_VertexShader;	//���_�V�F�[�_�[�I�u�W�F�N�g�|�C���^
static	ID3D11PixelShader* g_PixelShader;	//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�|�C���^
static	ID3D11InputLayout* g_VertexLayout;	//���_���C�A�E�g�I�u�W�F�N�g�|�C���^

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygon2D(void)
{
	// �e�N�X�`���ǂݍ���
	int Texture = TextureLoad(L"asset\\texture\\texture.jpg");

	//�V�F�[�_�[�ǂݍ���
	CreateVertexShader(&g_VertexShader, &g_VertexLayout, "shaderVS.cso");
	CreatePixelShader(&g_PixelShader, "shaderPS.cso");

	//2D�I�u�W�F�N�g������
	g_Object1.Position = XMFLOAT3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2, 0.0f);
	g_Object1.Color = XMFLOAT4(1.0f, 0.2f, 0.2f, 1.0f);
	g_Object1.Scale = XMFLOAT2(1.0f, 1.0f);
	g_Object1.Size = XMFLOAT2(200.0f, 200.0f);
	g_Object1.Rotate = 0.0f;
	g_Object1.TexID = Texture;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void FinalizePolygon2D(void)
{
	//��������̂����
	g_VertexShader->Release();
	g_VertexLayout->Release();
	g_PixelShader->Release();


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon2D(void)
{
	//�K���ɉ�]
	g_Object1.Rotate += 0.2f;

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon2D(void)
{

	//���_���C�A�E�g��ݒ�
	GetDeviceContext()->IASetInputLayout(g_VertexLayout);
	//���_�V�F�[�_�[���Z�b�g
	GetDeviceContext()->VSSetShader(g_VertexShader, NULL, 0);
	//�s�N�Z���V�F�[�_�[���Z�b�g
	GetDeviceContext()->PSSetShader(g_PixelShader, NULL, 0);

	//���s��������OFF
	SetDepthEnable(false);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	{//2D�|���S��1�����ŕK�v�ȏ���

		//�e�N�X�`�����Z�b�g
		ID3D11ShaderResourceView* tex = GetTexture(g_Object1.TexID);
		GetDeviceContext()->PSSetShaderResources(0, 1, &tex);

		//���s�ړ��s��̍쐬�i�\�����W�����߂�j
		XMMATRIX	TranslationMatrix = XMMatrixTranslation(
			g_Object1.Position.x, g_Object1.Position.y, 0.0f);

		//��]�s��iZ��]�j�s��̍쐬
		XMMATRIX	RotationMatrix = XMMatrixRotationZ(XMConvertToRadians(g_Object1.Rotate));

		//�X�P�[�����O�s��쐬�i�{��1.0�����{�A0�{�̓_���I�j
		XMMATRIX	ScalingMatrix = XMMatrixScaling(g_Object1.Scale.x,g_Object1.Scale.y, 1.0f);

		//���[���h�s��̍쐬�i�|���S���̕\���̎d�����w�肷��ŏI�I�ȍs��
		XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

		//���[���h�s���DirectX�փZ�b�g
		SetWorldMatrix(WorldMatrix);

		// �|���S���`��
		DrawSprite(g_Object1.Size, g_Object1.Color);
	}


}
