#pragma once
#include"GameLayer.h"
class HomeScene :public GameLayer {
	EventListenerTouchOneByOne*m_touchListener;
public:
	CREATE_FUNC(HomeScene);

	bool init()override;

	bool onTouchBegan(Touch*touch, Event*ev)override;
	void onTouchMoved(Touch*touch, Event*ev)override;
	void onTouchEnded(Touch*touch, Event*ev)override;

	void AddTouchListener();
};