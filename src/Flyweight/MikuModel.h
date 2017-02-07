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

//ミクのモデルの中で不変のもの、共有できるものをまとめたクラス。
//1種類につき1個のインスタンス。
class MikuModel {
private:
	TriMesh _mesh;
	gl::Texture _texture;

public:
	MikuModel() = default;

	// mesh_path_ = Obj形式のファイルパス
	// texture_path_ = Objに張り付けるテクスチャのパス
	// モデルデータを読み込む。
	MikuModel(string mesh_path_, string texture_path_)
	{
		ObjLoader _loader = ObjLoader(loadAsset(mesh_path_));
		_loader.load(&_mesh,
					 boost::logic::indeterminate,
					 boost::logic::indeterminate,
					 false);
		_texture = loadImage(loadAsset(texture_path_));
	}

	//テクスチャの参照を返す。
	inline const gl::Texture& getTexture() const
	{
		return _texture;
	}

	//メッシュの参照を返す。
	inline const TriMesh& getTriMesh() const
	{
		return _mesh;
	}
};