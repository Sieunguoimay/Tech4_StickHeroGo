#include"GameScene.h"
#include"PauseScene.h"
#include"Platform.h"
#include"utils/Definitions.h"
#include"utils/Utils.h"
Scene * GameScene::createScene()
{
	auto gameScene = Scene::create();
	gameScene->addChild(GameScene::create());
	return gameScene;
}

GameScene::~GameScene()
{
	CCLOG("GameScene Deleted");
}


bool GameScene::init()
{
	if (!Layer::init()) return false;
	srand(time(0));
	scheduleUpdate();
	setupEventHandler();

	initGameObject();


	CCLOG("GameScene Created %f %f %d",m_visibleSize.width,m_visibleSize.height,this->getChildrenCount());
	return true;
}



void GameScene::update(float deltaTime)
{
	auto pillar = m_pPlatform->GetCurrentPillar();
	auto nextPillar = m_pPlatform->GetNextPillar();

	if (pillar != nullptr
		&&nextPillar!=nullptr
		&&pillar->GetStick()->GetState() == FELL) {

		auto scale = m_pPlatform->MoveAndCalculateScale();
		if (scale > 0) {
			m_pZoomingLayer->runAction(ScaleTo::create(1.0f, scale));
			m_pZoomingLayer2->runAction(ScaleTo::create(1.0f, Utils::map(scale,0.0f,1.0f,0.75f,1.0f)));
		}
		m_pCharacter->MoveToTarget(Vec2(
			nextPillar->GetTopRightPoint().x - m_pCharacter->getContentSize().width / 2,
			nextPillar->GetTopRightPoint().y + m_pCharacter->getContentSize().height / 2));
	}

}







void GameScene::setupEventHandler()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}





bool GameScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * ev)
{
	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * ev)
{
}

void GameScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * ev)
{
}




void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	const float cameraSpeed = 10.0f;
	auto camera = Camera::getDefaultCamera();
	auto pillar = m_pPlatform->GetCurrentPillar();

	CCLOG(" key pressed %d", keyCode);
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		camera->setPosition(camera->getPosition() + Vec2(-cameraSpeed, 0));
		break;
	case EventKeyboard::KeyCode::KEY_D:
		camera->setPosition(camera->getPosition() + Vec2(cameraSpeed, 0));
		break;
	case EventKeyboard::KeyCode::KEY_S:
		camera->setPosition(camera->getPosition() + Vec2(0,-cameraSpeed));
		break;
	case EventKeyboard::KeyCode::KEY_W:
		camera->setPosition(camera->getPosition() + Vec2(0, cameraSpeed));
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (pillar != nullptr&&pillar->GetStick()->GetState() == START)
			pillar->GetStick()->SetState(ENLONGATING);
		break;
	}
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	auto pillar = m_pPlatform->GetCurrentPillar();
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		break;
	case EventKeyboard::KeyCode::KEY_D:
		break;
	case EventKeyboard::KeyCode::KEY_S:
		break;
	case EventKeyboard::KeyCode::KEY_W:
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (pillar != nullptr&&pillar->GetStick()->GetState() == ENLONGATING)
			pillar->GetStick()->SetState(ENLONGATED);
		break;
	}
}




void GameScene::setupMenu()
{
	auto button = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameScene::menuPauseCallback, this));
	if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
		printf("Error while loading: %s or %s\n", "CloseNormal.png", "CloseSelected.png");
	else
		button->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));

	auto menu = Menu::create(button, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void GameScene::menuPauseCallback(cocos2d::Ref * pSender)
{
	CCLOG("Paused");
	Director::getInstance()->pushScene(PauseScene::createScene());
}

void GameScene::menuGameOverCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(PauseScene::createScene());
}





void GameScene::initGameObject()
{
	
	m_pZoomingLayer = Layer::create();
	m_pZoomingLayer2 = Layer::create();
	m_pZoomingLayer->setAnchorPoint(Vec2(0.5f, 0.0f));
	m_pZoomingLayer2->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->addChild(m_pZoomingLayer);
	this->addChild(m_pZoomingLayer2);
	

	m_pPlatform = Platform::createPlatform();

	m_pBackground = Background::createBackground(m_pZoomingLayer, m_pPlatform);
	this->addChild(m_pBackground);

	m_pZoomingLayer->addChild(m_pPlatform);


	m_pCharacter = Character::createCharacter();
	m_pPlatform->addChild(m_pCharacter);

	m_pClouds = Clouds::createClouds();
	m_pZoomingLayer2->addChild(m_pClouds);
	m_pPlatform->RegisterMoveAlongCallback(m_pClouds);
	

}
