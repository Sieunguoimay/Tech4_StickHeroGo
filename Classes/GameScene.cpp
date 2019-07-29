#include"GameScene.h"
#include"PauseScene.h"
#include"Platform.h"
#include"utils/Definitions.h"
#include"utils/Utils.h"
#include"GameParticleSystem.h"
#include"SimpleAudioEngine.h"
Scene * GameScene::createScene()
{
	auto gameScene = Scene::create();
	gameScene->addChild(GameScene::create());
	return gameScene;
}

GameScene::~GameScene()
{
	delete m_followers;
	CCLOG("GameScene Deleted");
}


bool GameScene::init()
{
	if (!Layer::init()) return false;
	scheduleUpdate();
	setupEventHandler();

	initAudio();
	initGameObject();


	CCLOG("GameScene Created %f %f %d",m_visibleSize.width,m_visibleSize.height,this->getChildrenCount());
	return true;
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
	auto pillar = m_pPlatform->GetCurrentPillar();
	if (pillar != nullptr )
		pillar->GetStick()->Enlongate();
	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * ev)
{
}

void GameScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * ev)
{
	auto pillar = m_pPlatform->GetCurrentPillar();
	if (pillar != nullptr && pillar->GetStick()->GetState() == ENLONGATING)
		pillar->GetStick()->SetState(ENLONGATED);
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
		m_particleSystems[PS_WATER]->SetAngleDirEnd(180.0f);
		m_particleSystems[PS_WATER]->Emit(0.1f, m_visibleSize / 2);
		break;
	case EventKeyboard::KeyCode::KEY_W:
		m_particleSystems[PS_STARS]->SetAngleDirEnd(180.0f);
		m_particleSystems[PS_STARS]->Emit(0.1f, m_visibleSize / 2);
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		m_particleSystems[PS_SMOKE]->SetAngleDirEnd(180.0f);
		m_particleSystems[PS_SMOKE]->Emit(0.1f, m_visibleSize / 2);

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




void GameScene::OnPlayButtonClicked(int callerId)
{
	if (callerId == CI_HOME_SCENE) {
		m_pHomeScene->Hide();

		CCLOG("Start game from here...");

		_eventDispatcher->resumeEventListenersForTarget(this);
		m_pOnScreenInfoDisplay->setVisible(true);
		m_pPlatform->FirstMovementOnGameStart();
		m_pCharacter->MoveToTarget(m_pPlatform->GetFirstPillar()->GetTopRightPoint().x - m_pCharacter->getContentSize().width / 2 - m_pCharacter->getPosition().x - 5, 0.0f);
	}
	else if (callerId == CI_SHOW_SCORE_SCENE) {
		resetGame();
	}
	
}



void GameScene::initAudio()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/reward_good.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/reward_great.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/reward_perfect1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/reward_perfect2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/reward_perfect3.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/stick_enlongating.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/fall_into_water.mp3");
}


void GameScene::update(float deltaTime)
{
	if (m_pPlatform->GetState() == PFS_SPAWN_PILLAR) {
		//some conditions here...
		if(m_pPlatform->GetPillarCount()%2==0)
			m_pPlatform->GetLastPillar()->SetFollower(m_followers->SpawnFollower());

	}

	auto pillar = m_pPlatform->GetCurrentPillar();

	if (pillar != nullptr) {
		if (pillar->GetStick()->GetState() == FELL) {

			auto nextPillar = m_pPlatform->GetNextPillar();
			auto pillar = m_pPlatform->GetCurrentPillar();

			float perfectLength = nextPillar->getPosition().x - pillar->GetTopRightPoint().x;
			float stickLength = pillar->GetStick()->GetLength();
			float nextPillarHalfWidth = (nextPillar->GetWidth() / 2);
			float distanceFromCenter = std::min(std::abs(perfectLength - stickLength), nextPillarHalfWidth);

			int score = 0;// Utils::map(distanceFromCenter, 0.0f, nextPillarHalfWidth, MAX_SCORE_FOR_ONE_PILLAR, 0.0f);
			if (distanceFromCenter <= nextPillar->GetWidth1()) score = 4;
			else if (distanceFromCenter <= nextPillar->GetWidth2()) score = 3;
			else if (distanceFromCenter < nextPillarHalfWidth) score = 2;


			if (score > 0) {

				auto ps_pos = Vec2(pillar->GetStick()->getPosition().x + pillar->GetStick()->GetLength(), pillar->GetTopRightPoint().y);
				m_particleSystems[PS_SMOKE]->SetAngleDirEnd(180.0f).Emit(0.2f, ps_pos);
				m_particleSystems[PS_STARS]->SetAngleDirEnd(180.0f).SetSize(15).SetColor(235, 159, 159).Emit(0.1f, ps_pos);

				int gainScore = pow(2, score);
				if (score == 4) m_scoreManager.IncPerfectCount();
				else m_scoreManager.SetPerfectCount(0);
				if (m_scoreManager.GetPerfectCount() > 1) gainScore += pow(2, m_scoreManager.GetPerfectCount());
				m_scoreManager.AddScore(gainScore);
				m_pOnScreenInfoDisplay->ShowRewardForEachPillar(score - 2, m_scoreManager.GetPerfectCount(), gainScore);
				m_pOnScreenInfoDisplay->SetScore(m_scoreManager.GetScore());




				if (nextPillar->GetFollower() != nullptr) {
					m_followers->AddFollower(nextPillar->GetFollower(), [this, score]() {
						NextStep(score);
						});
					nextPillar->SetFollower(nullptr);
				}
				else NextStep(score);
			}
			else NextStep(score);
		}
		else if (pillar->GetStick()->GetState() == ENLONGATED) {
			pillar->RemoveRuler();
		}
	}
	if (m_pCharacter->GetState() == CharacterState::CS_FALL_START) {
		m_pPlatform->StopMoving();
		CCLOG("CS_FALL_START");
	}
	else if (m_pCharacter->GetState() == CharacterState::CS_STAND) {
		if(m_pPlatform->GetPillarCount()<7)
			m_pPlatform->AddRulerToCurrentPilar();
	}
	if (m_pCharacter->GetState() == CharacterState::CS_DIED) {
		m_particleSystems[PS_WATER]
			->SetMeanDistance(70.0f).SetDistanceVar(65.0f).SetMeanTime(0.7f).SetAngleDirEnd(180.0f).SetAngleDirStart(0.0f).SetSize(15.0f)
			.SetEmittingRate(200.0f)
			.SetCallback([this]() {
			onGameover();
		}).Emit(0.1f, m_pCharacter->getPosition() + Vec2(0.0f, m_pCharacter->GetHeight() / 2));
	}

	m_followers->Update(deltaTime);
}

void GameScene::NextStep(int score)
{

	auto nextPillar = m_pPlatform->GetNextPillar();
	auto pillar = m_pPlatform->GetCurrentPillar();
	float stickLength = pillar->GetStick()->GetLength();

	m_pCharacter->MoveToTarget(
		nextPillar->GetTopRightPoint().x - m_pCharacter->getContentSize().width / 2 - m_pCharacter->getPosition().x - 5,
		(score > 0 ? -1.0f : pillar->GetTopRightPoint().x + stickLength - m_pCharacter->getPosition().x));

	nextPillar->RemoveRect();

	auto scale = m_pPlatform->MoveAndCalculateScale();
	if (scale > 0) {
		m_pZoomingLayer->runAction(ScaleTo::create(1.0f, scale));
		m_pZoomingLayer2->runAction(ScaleTo::create(1.0f, Utils::map(scale, 0.0f, 1.0f, 0.75f, 1.0f)));
	}


}



void GameScene::initGameObject()
{

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_sprites.plist");
	this->addChild(SpriteBatchNode::create("common_sprites.png"));

	m_themeIndex = (rand() % 100)%3+1;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(String::createWithFormat("theme%d.plist", m_themeIndex)->getCString());
	this->addChild(SpriteBatchNode::create(String::createWithFormat("theme%d.png", m_themeIndex)->getCString()));


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dog_run.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dog_stand.plist");


	m_pZoomingLayer = Layer::create();
	m_pZoomingLayer2 = Layer::create();
	m_pZoomingLayer->setAnchorPoint(Vec2(0.5f, 0.0f));
	m_pZoomingLayer2->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->addChild(m_pZoomingLayer,GAME_LAYER_NEG_1);
	this->addChild(m_pZoomingLayer2);
	

	m_pPlatform = Platform::createPlatform();

	m_pBackground = Background::createBackground(m_pZoomingLayer, m_pPlatform);
	this->addChild(m_pBackground, GAME_LAYER_NEG_2);
	m_pZoomingLayer->addChild(m_pPlatform);

	for (int i = 0; i < PS_TOTAL_NUM; i++) {
		m_particleSystems[i] = GameParticleSystem::createParticleSystemByType(i);
		m_pPlatform->addChild(m_particleSystems[i],GAME_LAYER_1);
	}
	m_particleSystems[PS_SMOKE]->SetMeanDistance(50);
	m_particleSystems[PS_WATER]->setGlobalZOrder(GAME_LAYER_2);

	m_pCharacter = Character::createCharacter();
	m_pPlatform->addChild(m_pCharacter);
	m_pCharacter->setPosition(
		m_pPlatform->GetCurrentPillar()->getPosition() 
		+ Vec2(0.0f,m_pPlatform->GetCurrentPillar()->GetHeight()/2+m_pCharacter->GetHeight()/2));

	m_pClouds = Clouds::createClouds();
	m_pZoomingLayer2->addChild(m_pClouds);
	m_pPlatform->RegisterMoveAlongCallback(m_pClouds);
	m_pPlatform->RegisterMoveAlongCallback(m_particleSystems[PS_WATER]);
	m_pPlatform->RegisterMoveAlongCallback(m_particleSystems[PS_SMOKE]);
	m_pPlatform->RegisterMoveAlongCallback(m_particleSystems[PS_STARS]);





	m_pHomeScene = HomeScene::create();
	this->addChild(m_pHomeScene, GAME_LAYER_3);
	m_pHomeScene->SetCallback(this);
	m_pHomeScene->Show();
	m_pHomeScene->SetBestScore(m_scoreManager.GetHighScore());
	_eventDispatcher->pauseEventListenersForTarget(this);

	m_pOnScreenInfoDisplay = OnScreenInfoDisplay::create();
	this->addChild(m_pOnScreenInfoDisplay, GAME_LAYER_3);
	m_pOnScreenInfoDisplay->setVisible(false);
	m_pOnScreenInfoDisplay->SetHistoryHigh(m_scoreManager.GetHighScore());


	m_followers = new Followers(m_pPlatform, m_pCharacter);
}

void GameScene::onGameover()
{
	m_pShowScoreScene = ShowScoreScene::create();
	this->addChild(m_pShowScoreScene, GAME_LAYER_3);
	m_pShowScoreScene->SetCallback(this);
	m_pShowScoreScene->Show();
	m_pShowScoreScene->SetBestScore(m_scoreManager.GetHighScore());
	m_pShowScoreScene->SetScore(m_scoreManager.GetScore());
	_eventDispatcher->pauseEventListenersForTarget(this);


}

void GameScene::resetGame()
{
	m_scoreManager.SaveData();
	SpriteFrameCache::getInstance()->destroyInstance();

	CCLOG("GAME OVER");
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f,GameScene::createScene(), Color3B(255, 255, 255)));
}
