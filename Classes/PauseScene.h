#pragma once
#include"cocos2d.h"
class PauseScene :public cocos2d::Layer {
public:
	virtual bool init()override;
	
	static cocos2d::Scene* createScene();

	CREATE_FUNC(PauseScene);
	void menuResumeGameCallback(cocos2d::Ref*pSender);
	void menuBackToHomeCallback(cocos2d::Ref*pSender);
};