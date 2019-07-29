#pragma once
#include"cocos2d.h"
#include"utils/list.h"
#include"Character.h"
#include"Background.h"
#include"Platform.h"
#include"Clouds.h"
#include"Wave.h"
#include"GameParticleSystem.h"
#include"OnScreenInfoDisplay.h"
#include"HomeScene.h"
#include"ScoreManager.h"
#include"Followers.h"
#include"ShowScoreScene.h"
class GameScene: public GameLayer, public HomeSceneCallback{
	CREATE_FUNC(GameScene);
	

	
	void setupEventHandler();
	bool onTouchBegan(Touch*touch, Event*ev)override;
	void onTouchMoved(Touch*touch, Event*ev)override;
	void onTouchEnded(Touch*touch, Event*ev)override;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*event)override;
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*event)override;

	void OnPlayButtonClicked(int callerId)override;
	void NextStep(int score);

	void setupMenu();
	void menuPauseCallback(Ref*pSender);
	void menuGameOverCallback(Ref*pSender);

	void initGameObject();
	void onGameover();
	void resetGame();

	Layer*m_pZoomingLayer;//scale variance factor greater
	Layer*m_pZoomingLayer2;//scale variance factor smaller

	OnScreenInfoDisplay*m_pOnScreenInfoDisplay;
	HomeScene*m_pHomeScene;
	ShowScoreScene* m_pShowScoreScene;
	EventListenerTouchOneByOne*m_touchListener;

	GameParticleSystem*m_particleSystems[PS_TOTAL_NUM];
	Platform*m_pPlatform;
	Character*m_pCharacter;
	Background*m_pBackground;
	Clouds*m_pClouds;
	ScoreManager m_scoreManager;
	Followers*m_followers;

	int m_themeIndex;
public:
	
	static Scene* createScene();
	virtual ~GameScene()override;
	virtual bool init() override;
	virtual void update(float deltaTime)override;

};
