#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Light.h"
#include "cinder/gl/Material.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"
#include <memory>
#include "cinder/Rand.h"

#include "../src/Flyweight/Miku.h"
#include "../src/Flyweight/MikuModel.h"

#include <omp.h>         //OpenMPで並列forを実装するため。

using namespace ci;
using namespace ci::app;
using namespace std;

enum {
	WINDOW_WIDTH = 1200,
	WINDOW_HEIGHT = 800,
	NUM = 5000           //ミクさんの数
};

class TestProjectApp : public AppNative {
private:
	CameraPersp camera;

	gl::Light *light;
	gl::Material material;

	std::shared_ptr<MikuModel> _miku_model;
	std::vector<std::shared_ptr<Miku>> _miku;

public:
	TestProjectApp() = default;
	void prepareSettings(Settings *settings);
	void setup();
	void shutdown();
	void setupCamera();
	void setupLight();
	void setupMaterial();
	void setupFog();
	void setupDepth();
	void draw();
};

void TestProjectApp::prepareSettings(Settings * settings)
{
	settings->setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void TestProjectApp::setup()
{
	setupCamera();
	setupLight();
	setupMaterial();
	setupFog();
	setupDepth();

	Rand::randomize();

	//種類ごとのモデルのメッシュファイル(今回は*.OBJのみ対応)と貼り付けるテクスチャを読み込み。
	_miku_model = std::make_shared<MikuModel>("Flyweight/negimiku.obj", "Flyweight/miku.png");

	//NUMの数だけモデルをインスタンスして可変長配列へ格納。
	for (int i = 0; i < NUM; i++) {
		Vec3f __pos = Vec3f(randFloat(-15.0f, 15.0f), randFloat(-10.0f, 10.0f), randFloat(-1.0f, 70.0f));
		float __speed = randFloat(0.1f, 1.0f);
		_miku.push_back(std::make_shared<Miku>(_miku_model, __pos, __speed));
	}

	//モデルへのライティング設定
	ColorA lmodel_ambient(0.2f, 0.2f, 0.2f, 1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
				   lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,
				  GL_SEPARATE_SPECULAR_COLOR);
}

void TestProjectApp::shutdown()
{
	delete light;
}

void TestProjectApp::setupCamera()
{
	camera = CameraPersp(WINDOW_WIDTH, WINDOW_HEIGHT,
						 60.0f,
						 0.1f, 1000.0f);

	camera.setEyePoint(Vec3f(0.0f, 0.0f, -5.0f));
	camera.setCenterOfInterestPoint(Vec3f(0.0f, 0.0f, 300.0f));
}

void TestProjectApp::setupLight()
{
	light = new gl::Light(gl::Light::DIRECTIONAL, 0);
	light->setAmbient(Color(0.1f, 0.1f, 0.1f));      //環境光
	light->setDiffuse(Color(0.8f, 0.8f, 0.8f));      //拡散光
	light->setSpecular(Color(0.4f, 0.4f, 0.4f));     //鏡面光
	light->setDirection(Vec3f(0.0f, 0.0f, -1.0f));   //光源への向き
}

void TestProjectApp::setupMaterial()
{
	material = gl::Material(ColorA(1.0, 1.0, 1.0),        //環境光
							ColorA(1.0, 1.0, 1.0),        //拡散光
							ColorA(1.0, 1.0, 1.0), 80.0,  //鏡面光
							ColorA(0.0, 0.0, 0.0));       //自己発光
}

void TestProjectApp::setupFog()
{
	//FOG設定
	gl::enable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 70.0f);
	glFogf(GL_FOG_END, 100.0f);
	ColorA fog_color_ = ColorA(0.f, 0.f, 0.f, 1.0f);
	glFogfv(GL_FOG_COLOR, fog_color_);
}

void TestProjectApp::setupDepth()
{
	//深度バッファとカリング、アルファブレンドの設定
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enable(GL_CULL_FACE);
	gl::enableAlphaBlending();
}

void TestProjectApp::draw()
{
	gl::clear(Color(0, 0, 0));
	gl::setMatrices(camera);

	gl::enable(GL_LIGHTING);
	gl::enable(GL_NORMALIZE);
	light->enable();

	material.apply();

	gl::pushModelView();

	gl::translate(Vec3f(0, 0, 0));


	//大量のミクさん描画
	//このfor文を並列処理させる。
	#pragma omp parallel for
	for (int i = 0; i < NUM; i++) {
		gl::pushMatrices();

		gl::translate(_miku[i]->getPos());                  //ミクさん表示したい場所を原点に
		gl::rotate(Vec3f(0.0f, _miku[i]->getRot(), 0.0f));  //ミクさん原点にして回転

		//テクスチャを有効にしてメッシュを描画。
		_miku[i]->getMikuModel().getTexture().enableAndBind();
		gl::draw(_miku[i]->getMikuModel().getTriMesh());
		_miku[i]->getMikuModel().getTexture().disable();
		_miku[i]->move();

		gl::popMatrices();
	}

	gl::popModelView();

	light->disable();
}
CINDER_APP_NATIVE(TestProjectApp, RendererGl)
