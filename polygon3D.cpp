/*==============================================================================

   ���_�Ǘ� [polygon3D.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon3D.h"
#include "sprite.h"
#include "Camera.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	BOX_NUM_VERTEX	(36)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static	Camera		g_CameraObject;	//�J�����\����
static	Object3D	g_Object1;		//3D�|���S���I�u�W�F�N�g�\����
static	ID3D11VertexShader* g_VertexShader;	//���_�V�F�[�_�[�I�u�W�F�N�g�|�C���^
static	ID3D11PixelShader* g_PixelShader;	//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�|�C���^
static	ID3D11InputLayout* g_VertexLayout;	//���_���C�A�E�g�I�u�W�F�N�g�|�C���^

static	ID3D11Buffer* g_VertexBuffer;	//�e�X�g�p���_�o�b�t�@
static	ID3D11Buffer* g_IndexBuffer;	//�e�X�g�p�C���f�b�N�X�o�b�t�@


//���_�f�[�^
/*
      V0------------------V1
      |                  |
     |      �V��        |
    |                  |
   V2-----------------V3


	  V5------------------V4
	  |                  |
	 |       ���       |
	|                  |
   V7-----------------V6
*/




VERTEX_3D	Box[BOX_NUM_VERTEX] =
{
	//�V��////////////////////////////////////////////
	{//���_V0 LEFT-TOP
		XMFLOAT3(-0.5f, 0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V1 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V2 LEFT-BOTTOM
		XMFLOAT3(-0.5f, 0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},

	{//���_V3 RIGHT-BOTTOM
		XMFLOAT3(0.5f, 0.5f, -0.5f),		//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V2 LEFT-BOTTOM
		XMFLOAT3(-0.5f, 0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V1 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},


	//�O��////////////////////////////////////////////
	{//���_V2 LEFT-TOP
		XMFLOAT3(-0.5f, 0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V3 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V7 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V6 RIGHT-BOTTOM
		XMFLOAT3(0.5f,-0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V7 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V3 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},



	//�E����////////////////////////////////////////////
	{//���_V3 LEFT-TOP
		XMFLOAT3(0.5f, 0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V1 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V6 LEFT-BOTTOM
		XMFLOAT3(0.5f,-0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V4 RIGHT-BOTTOM
		XMFLOAT3(0.5f, -0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V6 LEFT-BOTTOM
		XMFLOAT3(0.5f,-0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V1 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},



	//�w��////////////////////////////////////////////
	{//���_V1 LEFT-TOP
		XMFLOAT3(0.5f, 0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V0 RIGHT-TOP
		XMFLOAT3(-0.5f, 0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V4 LEFT-BOTTOM
		XMFLOAT3(0.5f, -0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V5 RIGHT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V4 LEFT-BOTTOM
		XMFLOAT3(0.5f, -0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V0 RIGHT-TOP
		XMFLOAT3(-0.5f, 0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},



	//������////////////////////////////////////////////
	{//���_V0 LEFT-TOP
		XMFLOAT3(-0.5f, 0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V2 RIGHT-TOP
		XMFLOAT3(-0.5f, 0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V5 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},

	{//���_V2 RIGHT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V7 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V5 RIGHT-TOP
		XMFLOAT3(-0.5f, 0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},


	//���////////////////////////////////////////////
	{//���_V7 LEFT-TOP
		XMFLOAT3(-0.5f, -0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V6 RIGHT-TOP
		XMFLOAT3(0.5f,-0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},
	{//���_V5 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},

	{//���_V6 RIGHT-BOTTOM
		XMFLOAT3(0.5f,-0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V4 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, 0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(0.0f,1.0f)				//�e�N�X�`�����W
	},
	{//���_V5 RIGHT-TOP
		XMFLOAT3(0.5f, -0.5f, -0.5f),	//���_���W
		XMFLOAT3(0.0f,0.0f,0.0f),		//�@��
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//�J���[
		XMFLOAT2(1.0f,0.0f)				//�e�N�X�`�����W
	},

};





//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygon3D(void)
{

	//�e�N�X�`���ǂݍ���
	int Texture = TextureLoad(L"asset\\texture\\sura.jpg");

	//�V�F�[�_�[�ǂݍ���
	CreateVertexShader(&g_VertexShader, &g_VertexLayout, "testshaderVS.cso");
	CreatePixelShader(&g_PixelShader, "testshaderPS.cso");

	//�J�����̏�����
	g_CameraObject.Position = XMFLOAT3(0.0f, 0.0f, -5.0f);
	g_CameraObject.UpVector = XMFLOAT3(0.0f, 1.0f, 0.0f);
	g_CameraObject.AtPosition = XMFLOAT3(0.0f, 0.0f, 1.0f);
	g_CameraObject.Fov = 45.0f;
	g_CameraObject.Nearclip = 0.5f;
	g_CameraObject.Farclip = 1000.0f;

	//���_�o�b�t�@�쐬
	{
		D3D11_BUFFER_DESC	bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * BOX_NUM_VERTEX;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

		//���_�o�b�t�@�̏������ݐ�̃|�C���^�[���擾
		D3D11_MAPPED_SUBRESOURCE	msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		//���_�f�[�^���R�s�[
		CopyMemory(&vertex[0], &Box[0], sizeof(VERTEX_3D) * BOX_NUM_VERTEX);
		//�������݊���
		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	//3D�I�u�W�F�N�g�Ǘ��\���̂̏�����
	g_Object1.Position = XMFLOAT3(1.5f, 0.0f, 0.0f);
	g_Object1.Rotate = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Object1.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	g_Object1.TexID = Texture;


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void FinalizePolygon3D(void)
{
	//��������̂����
	g_VertexShader->Release();
	g_VertexLayout->Release();
	g_PixelShader->Release();

	g_VertexBuffer->Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon3D(void)
{
	//�K���ɉ�]
	g_Object1.Rotate.y += 0.3f;
	g_Object1.Rotate.x += 0.1f;

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon3D(void)
{
	//���_���C�A�E�g��ݒ�
	GetDeviceContext()->IASetInputLayout(g_VertexLayout);
	//���_�V�F�[�_�[���Z�b�g
	GetDeviceContext()->VSSetShader(g_VertexShader, NULL, 0);
	//�s�N�Z���V�F�[�_�[���Z�b�g
	GetDeviceContext()->PSSetShader(g_PixelShader, NULL, 0);

	//3D�p�s��ݒ�
	SetDepthEnable(true);		//���s�������L��

	//�v���W�F�N�V�����s����쐬
	XMMATRIX	ProjectionMatrix =
		XMMatrixPerspectiveFovLH(
			XMConvertToRadians(g_CameraObject.Fov),//��p
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,//�A�X�y�N�g��
			g_CameraObject.Nearclip,//�߃N���b�v����
			g_CameraObject.Farclip//���N���b�v����
		);
	//DirectX�փZ�b�g
	SetProjectionMatrix(ProjectionMatrix);

	//�J�����s����쐬
	XMVECTOR	eyev = XMLoadFloat3(&g_CameraObject.AtPosition);//�ʒu
	XMVECTOR	pos = XMLoadFloat3(&g_CameraObject.Position);//�����_
	XMVECTOR	up = XMLoadFloat3(&g_CameraObject.UpVector);//����x�N�g���i1.0�Œ�j

	XMMATRIX	ViewMatrix =
		XMMatrixLookAtLH(pos, eyev, up);//����n���b�N�A�b�g�J����

	//DirectX�փZ�b�g
	SetViewMatrix(ViewMatrix);

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

		//���_�o�b�t�@���Z�b�g
		UINT	stride = sizeof(VERTEX_3D);
		UINT	offset = 0;
		GetDeviceContext()->IASetVertexBuffers(
			0,
			1,
			&g_VertexBuffer,
			&stride,
			&offset
		);

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
		GetDeviceContext()->Draw(BOX_NUM_VERTEX, 0);//�C���f�b�N�X�����`��
	}


}
