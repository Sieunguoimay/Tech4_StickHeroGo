#include"GameScene.h"
#include"PauseScene.h"
#include"Platform.h"
#include"utils/Definitions.h"
#include"utils/Utils.h"
#include"GameParticleSystem.h"
Scene * GameScene::createScene()
{
	auto gameScene = Scene::create();
	gameScene->addChild(GameScene::create());
	return gameScene;
}

GameScene::~GameScene()
{
	GameParticleSystem::CleanUp();
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
	//Hello world of git
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



		float perfectLength = nextPillar->getPosition().x - pillar->GetTopRightPoint().x;
		float stickLength = pillar->GetStick()->GetLength();
		float nextPillarHalfWidth = (nextPillar->GetWidth() / 2);
		float distanceFromCenter = std::min(std::abs(perfectLength - stickLength), nextPillarHalfWidth);

		int score = 0;// Utils::map(distanceFromCenter, 0.0f, nextPillarHalfWidth, MAX_SCORE_FOR_ONE_PILLAR, 0.0f);
		if (distanceFromCenter <= nextPillar->GetWidth1()) score = 16;
		else if (distanceFromCenter <= nextPillar->GetWidth2()) score = 8;
		else if (distanceFromCenter < nextPillarHalfWidth) score = 4;

		CCLOG("Score %d",score);

		if (score > 0) {
			nextPillar->RemoveRect();
			 
			m_score += score;
			m_pOnScreenInfoDisplay->SetScore(m_score);

			auto ps_pos = Vec2(pillar->GetStick()->getPosition().x + pillar->GetStick()->GetLength(),
				pillar->GetTopRightPoint().y);
			GameParticleSystem::GetInstance(PS_SMOKE)->SetAngleDirEnd(180.0f).Emit(0.2f, ps_pos);
			GameParticleSystem::GetInstance(PS_STARS)->SetAngleDirEnd(180.0f).SetColor(255,200,0).Emit(0.2f, ps_pos);
		}


		m_pCharacter->MoveToTarget(
			nextPillar->GetTopRightPoint().x - m_pCharacter->getContentSize().width / 2
			- m_pCharacter->getPosition().x ,
			(score>0?-1.0f: pillar->GetTopRightPoint().x + stickLength - m_pCharacter->getPosition().x));

	}
	if (m_pCharacter->GetState() == CharacterState::CS_FALL_START) {
		m_pPlatform->StopMoving();
		CCLOG("CS_FALL_START");
	}
	if (m_pCharacter->GetState() == CharacterState::CS_DIED) {
		CCLOG("GAME OVER");
		GameParticleSystem::GetInstance(PS_WATER)
			->SetMeanDistance(70.0f).SetDistanceVar(65.0f).SetMeanTime(0.7f).SetAngleDirEnd(180.0f).SetAngleDirStart(0.0f).SetSize(15.0f)
			.SetEmittingRate(200.0f)
			.SetCallback([this]() {
				Director::getInstance()->popScene();
			})
			.Emit(0.1f, m_pCharacter->getPosition()+Vec2(0.0f,m_pCharacter->GetHeight()/2));
	}
}







void GameScene::setupEventHandler()
{
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->setSwallowTouches(true);
	m_touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}





bool GameScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * ev)
{
	GameParticleSystem::GetInstance(PS_SMOKE)->Emit(0.1f, touch->getLocation());
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
		break;
	case EventKeyboard::KeyCode::KEY_D:
		break;
	case EventKeyboard::KeyCode::KEY_S:
		GameParticleSystem::GetInstance(PS_WATER)->SetAngleDirEnd(180.0f);
		GameParticleSystem::GetInstance(PS_WATER)->Emit(0.1f, m_visibleSize / 2);
		break;
	case EventKeyboard::KeyCode::KEY_W:
		GameParticleSystem::GetInstance(PS_STARS)->SetAngleDirEnd(180.0f);
		GameParticleSystem::GetInstance(PS_STARS)->Emit(0.1f, m_visibleSize / 2);
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		GameParticleSystem::GetInstance(PS_SMOKE)->SetAngleDirEnd(180.0f);
		GameParticleSystem::GetInstance(PS_SMOKE)->Emit(0.1f, m_visibleSize/2);

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

void GameScene::showHomeScene()
{
}

void GameScene::hideHomeScene()
{
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
	m_pOnScreenInfoDisplay = OnScreenInfoDisplay::create();
	this->addChild(m_pOnScreenInfoDisplay);

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

	GameParticleSystem::Init(m_pPlatform);

	m_pCharacter = Character::createCharacter();
	m_pPlatform->addChild(m_pCharacter);
	m_pCharacter->setPosition(
		m_pPlatform->GetCurrentPillar()->getPosition() 
		+ Vec2(0.0f,m_pPlatform->GetCurrentPillar()->GetHeight()/2+m_pCharacter->GetHeight()/2));
	m_pCharacter->setGlobalZOrder(GAME_LAYER_1);

	m_pClouds = Clouds::createClouds();
	m_pZoomingLayer2->addChild(m_pClouds);
	m_pPlatform->RegisterMoveAlongCallback(m_pClouds);
	m_pPlatform->RegisterMoveAlongCallback(GameParticleSystem::GetInstance(PS_WATER));
	m_pPlatform->RegisterMoveAlongCallback(GameParticleSystem::GetInstance(PS_SMOKE));
	m_pPlatform->RegisterMoveAlongCallback(GameParticleSystem::GetInstance(PS_STARS));

	m_score = 0;

	m_pHomeScene = HomeScene::create();
	this->addChild(m_pHomeScene);
	_eventDispatcher->removeEventListener(m_touchListener);
	m_pHomeScene->AddTouchListener();
}
