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
class GameScene: public GameLayer{
	CREATE_FUNC(GameScene);
	

	
	void setupEventHandler();
	bool onTouchBegan(Touch*touch, Event*ev)override;
	void onTouchMoved(Touch*touch, Event*ev)override;
	void onTouchEnded(Touch*touch, Event*ev)override;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*event)override;
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*event)override;


	void setupMenu();
	void menuPauseCallback(Ref*pSender);
	void menuGameOverCallback(Ref*pSender);

	void initGameObject();


	Layer*m_pZoomingLayer;//scale variance factor greater
	Layer*m_pZoomingLayer2;//scale variance factor smaller

	OnScreenInfoDisplay*m_pOnScreenInfoDisplay;

	Platform*m_pPlatform;
	Character*m_pCharacter;
	Background*m_pBackground;
	Clouds*m_pClouds;

	int m_score;
public:
	
	static Scene* createScene();
	virtual ~GameScene()override;
	virtual bool init() override;
	virtual void update(float deltaTime)override;

};
