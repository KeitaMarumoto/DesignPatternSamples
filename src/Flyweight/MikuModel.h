#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/ObjLoader.h"
#include "cinder/TriMesh.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//�~�N�̃��f���̒��ŕs�ς̂��́A���L�ł�����̂��܂Ƃ߂��N���X�B
//1��ނɂ�1�̃C���X�^���X�B
class MikuModel {
private:
	TriMesh _mesh;
	gl::Texture _texture;

public:
	MikuModel() = default;

	// mesh_path_ = Obj�`���̃t�@�C���p�X
	// texture_path_ = Obj�ɒ���t����e�N�X�`���̃p�X
	// ���f���f�[�^��ǂݍ��ށB
	MikuModel(string mesh_path_, string texture_path_)
	{
		ObjLoader _loader = ObjLoader(loadAsset(mesh_path_));
		_loader.load(&_mesh,
					 boost::logic::indeterminate,
					 boost::logic::indeterminate,
					 false);
		_texture = loadImage(loadAsset(texture_path_));
	}

	//�e�N�X�`���̎Q�Ƃ�Ԃ��B
	inline const gl::Texture& getTexture() const
	{
		return _texture;
	}

	//���b�V���̎Q�Ƃ�Ԃ��B
	inline const TriMesh& getTriMesh() const
	{
		return _mesh;
	}
};