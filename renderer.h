/*==============================================================================

   �����_�����O�Ǘ�[renderer.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "main.h"

//*********************************************************
// �\����
//*********************************************************

// ���_�\����
struct VERTEX_3D
{
	XMFLOAT3 Position;	//���_���W�@XMFLOAT3 ���@float x,y,z
	XMFLOAT3 Normal;	//�@���x�N�g�� 
	XMFLOAT4 Diffuse;	//�F  XMFLOAT4 = float x,y,z,w
	XMFLOAT2 TexCoord;	//�e�N�X�`�����W XMFLOAT2 = float x,y
};

// �}�e���A���\����
struct MATERIAL
{
	XMFLOAT4	Ambient;	//�A���r�G���g
	XMFLOAT4	Diffuse;	//�f�t���[�Y
	XMFLOAT4	Specular;	//�X�y�L����
	XMFLOAT4	Emission;	//�G�~�b�V�u
	float		Shininess;	//�X�y�L�����p�����[�^
	float		Dummy[3];	//16byte���E�����p�p�f�B���O
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void FinalizeRenderer(void);

void Clear(void);
void Present(void);

ID3D11Device *GetDevice( void );
ID3D11DeviceContext *GetDeviceContext( void );

void SetDepthEnable( bool Enable );

void SetWorldViewProjection2D(void);
void ResetWorldViewProjection3D(void);


void SetWorldMatrix(XMMATRIX WorldMatrix );
void SetViewMatrix(XMMATRIX ViewMatrix );
void SetProjectionMatrix(XMMATRIX ProjectionMatrix );

void SetMaterial( MATERIAL Material );

void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

