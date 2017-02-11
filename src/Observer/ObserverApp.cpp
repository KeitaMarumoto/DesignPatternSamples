#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Light.h"
#include "cinder/gl/Material.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"

using namespace ci;
using namespace ci::app;
using namespace std;

enum {
	WINDOW_WIDTH = 1200,
	WINDOW_HEIGHT = 900
};

class ObserverApp : public AppNative {
private:
	CameraPersp camera;

	gl::Light *light;
	gl::Material material;

public:
	void prepareSettings(Settings *settings);
	void setup();
	void shutdown();
	void setupCamera();
	void setupLight();
	void setupMaterial();
	void setupFog();
	void setupDepth();
	void mouseDown(MouseEvent event);
	void update();
	void draw();
};

void ObserverApp::prepareSettings(Settings * settings)
{
	settings->setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void ObserverApp::setup()
{
	setupCamera();
	setupLight();
	setupMaterial();
	setupFog();
	setupDepth();
}

void ObserverApp::shutdown()
{
	delete light;
}

void ObserverApp::setupCamera()
{
	camera = CameraPersp(WINDOW_WIDTH, WINDOW_HEIGHT,
						 60.0f,
						 0.1f, 1000.0f);

	camera.setEyePoint(Vec3f(0.0f, 0.0f, -5.0f));
	camera.setCenterOfInterestPoint(Vec3f(0.0f, 0.0f, 1000.0f));
}

void ObserverApp::setupLight()
{
	light = new gl::Light(gl::Light::DIRECTIONAL, 0);
	light->setAmbient(Color(0.1f, 0.1f, 0.1f));      //環境光
	light->setDiffuse(Color(0.8f, 0.8f, 0.8f));      //拡散光
	light->setSpecular(Color(0.4f, 0.4f, 0.4f));     //鏡面光
	light->setDirection(Vec3f(0.0f, 0.0f, -1.0f));   //光源への向き
}

void ObserverApp::setupMaterial()
{
	material = gl::Material(ColorA(1.0, 1.0, 1.0),        //環境光
							ColorA(1.0, 1.0, 1.0),        //拡散光
							ColorA(1.0, 1.0, 1.0), 80.0,  //鏡面光
							ColorA(0.0, 0.0, 0.0));       //自己発光
}

void ObserverApp::setupFog()
{
	//FOG設定
	gl::enable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 70.0f);
	glFogf(GL_FOG_END, 100.0f);
	ColorA fog_color_ = ColorA(0.f, 0.f, 0.f, 1.0f);
	glFogfv(GL_FOG_COLOR, fog_color_);
}

void ObserverApp::setupDepth()
{
	//深度バッファとカリング、アルファブレンドの設定
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enable(GL_CULL_FACE);
	gl::enableAlphaBlending();
}

void ObserverApp::mouseDown(MouseEvent event)
{
}

void ObserverApp::update()
{
}

void ObserverApp::draw()
{
	// clear out the window with black
	gl::clear(Color(0, 0, 0));

	gl::enable(GL_LIGHTING);
	gl::enable(GL_NORMALIZE);
	light->enable();


	light->disable();
}

CINDER_APP_NATIVE(ObserverApp, RendererGl)
