#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Light.h"
#include "cinder/gl/Material.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"

#include "Observers/FanfareSound.h"
#include "Observers/Achievements.h"
#include "Node/ObserverNode.h"
#include "Node/Observer.h"
#include "Subject/Subject.h"


using namespace ci;
using namespace ci::app;
using namespace std;

enum {
	WINDOW_WIDTH = 800,
	WINDOW_HEIGHT = 600
};


// オブザーバパターンを実装。
// キーボードのXかYを押したとき。
// ないし、マウスの右クリック5回か左クリック5回のときに通知が送られる。
// Xボタン：色が赤になり、Fight.wavが再生。
// Yボタン：色が青になり、trans-am_raiser.mp3が再生。
// マウスの左ボタンを計5回押す：色が緑色になり、gundam00_op1.mp3が再生。
// マウスの右ボタンを計5回押す：色が紫色になり、gundam00_op2.mp3が再生。
// Spaceキーを押す：色が白に戻り、音楽再生も止まる。
class ObserverApp : public AppNative {
private:
	CameraPersp camera;

	gl::Light *light;
	gl::Material material;

	Subject input_event;

	ObserverNode* achievements_node;
	ObserverNode* fanfare_sound_node;

	Entity entity;
	Color color;

	float angle;
	float angle_speed;
	int left_click_count;
	int right_click_count;

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
	void keyDown(KeyEvent event);
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

	entity = Entity();
	achievements_node = new ObserverNode(std::make_shared<Achievements>());
	fanfare_sound_node = new ObserverNode(std::make_shared<FanfareSound>());

	input_event.addObserver(achievements_node);
	input_event.addObserver(fanfare_sound_node);

	entity.setColor(Color(1.f, 1.f, 1.f));
	color = entity.getColor();

	angle = 0.0f;
	angle_speed = 0.0f;
	left_click_count = 0;
	right_click_count = 0;
}

void ObserverApp::shutdown()
{
	delete light;
	delete achievements_node;
	delete fanfare_sound_node;
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
	entity.setMouseEvent(event);

	//左クリック
	if (event.isLeft()) {
		left_click_count++;
		if ((left_click_count != 0) && ((left_click_count % 5) == 0)) {
			input_event.notify(entity, Events::LEFT_CLICK_FIVE_TIMES);
			left_click_count = 0;
			angle_speed = 0.5f;
		}
	}
	//右クリック
	else if (event.isRight()) {
		right_click_count++;
		if ((right_click_count != 0) && ((right_click_count % 5) == 0)) {
			input_event.notify(entity, Events::RIGHT_CLICK_FIVE_TIMES);
			right_click_count = 0;
			angle_speed = 0.3f;
		}
	}
}

void ObserverApp::keyDown(KeyEvent event)
{
	entity.setKeyEvent(event);
	int code = event.getCode();

	//Xのキーが押された
	if (code == KeyEvent::KEY_x) {
		input_event.notify(entity, Events::PUSH_KEY_X);
		angle_speed = 2.1f;
	}
	//Yのキーが押された
	else if (code == KeyEvent::KEY_y) {
		input_event.notify(entity, Events::PUSH_KEY_Y);
		angle_speed = 1.4f;
	}
	//Spaceキーが押された
	else if (code == KeyEvent::KEY_SPACE) {
		input_event.notify(entity, Events::PUSH_KEY_SPACE);
		angle_speed = 0.f;
	}
}

void ObserverApp::update()
{
	angle += angle_speed;
	material.setAmbient(entity.getColor());
	material.setDiffuse(entity.getColor());
}

void ObserverApp::draw()
{
	// clear out the window with black
	gl::clear(Color(0, 0, 0));

	gl::setMatrices(camera);

	gl::enable(GL_LIGHTING);
	gl::enable(GL_NORMALIZE);
	light->enable();
	material.apply();

	gl::pushModelView();
	gl::rotate(Vec3f(angle, angle, angle*0.3f));
	gl::drawCube(Vec3f(0, 0, 0), Vec3f(1, 1, 1));
	gl::popModelView();

	light->disable();
}

CINDER_APP_NATIVE(ObserverApp, RendererGl)
