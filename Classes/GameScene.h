#pragma once
#include"cocos2d.h"
#include"Pillar.h"
#include"list.h"
#include"ActionRunner.h"
#include"Character.h"
#include"Background.h"
class GameScene: public cocos2d::Layer{

public:

	static cocos2d::Scene* createScene();
	virtual ~GameScene()override;
	virtual bool init() override;
	virtual void update(float deltaTime)override;


private:
	
	Pillar* createPillar(const cocos2d::Vec2& origin,bool atInit = false);
	void moveCamera(cocos2d::Camera*camera);
	void doSomethingOnAStickFellDown();

	//Pillar is a normal object
	List<Pillar*>m_pillars;
	//This is a node pointer
	ListNode<Pillar*>*m_pPillarNodePointer;


	//cocos2d::Sprite* m_background;
	
	//normal object
	Character*m_character;

	Background*m_pBackground;
	
	bool m_cameraMoving = false;
	
	CREATE_FUNC(GameScene);

	void menuPauseCallback(cocos2d::Ref*pSender);
	void menuGameOverCallback(cocos2d::Ref*pSender);
	
	void SetPhysicsWorld(cocos2d::PhysicsWorld*world) { sceneWorld = world; }
	
	cocos2d::PhysicsWorld*sceneWorld;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	void setupMenu();
	void setupEventHandler();
	bool onTouchBegan(cocos2d::Touch*touch, cocos2d::Event*ev)override;
	void onTouchMoved(cocos2d::Touch*touch, cocos2d::Event*ev)override;
	void onTouchEnded(cocos2d::Touch*touch, cocos2d::Event*ev)override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*event)override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*event)override;

};
