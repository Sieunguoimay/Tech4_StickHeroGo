#pragma once
#include"GameLayer.h"
class HomeSceneCallback {
public:
	virtual void OnPlayButtonClicked() = 0;
};
class HomeScene :public GameLayer {
	EventListenerTouchOneByOne*m_touchListener;
	HomeSceneCallback*m_callback;
	Label* m_bestScore;
public:
	CREATE_FUNC(HomeScene);

	bool init()override;

	bool onTouchBegan(Touch*touch, Event*ev)override;
	void onTouchMoved(Touch*touch, Event*ev)override;
	void onTouchEnded(Touch*touch, Event*ev)override;

	void Show();
	void Hide();
	void SetCallback(HomeSceneCallback*callback) { this->m_callback = callback; }

	void OnPlayButtonClicked();

	void SetBestScore(int score);
};