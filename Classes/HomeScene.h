#pragma once
#include"GameLayer.h"
enum CallerId {
	CI_HOME_SCENE,
	CI_SHOW_SCORE_SCENE
};
class HomeSceneCallback {
public:
	virtual void OnPlayButtonClicked(int callerId) = 0;
};
class HomeScene :public GameLayer {
protected:
	EventListenerTouchOneByOne*m_touchListener;
	HomeSceneCallback*m_callback;
	Label* m_bestScore;
public:
	CREATE_FUNC(HomeScene);

	bool init()override;

	bool onTouchBegan(Touch*touch, Event*ev)override;
	void onTouchMoved(Touch*touch, Event*ev)override;
	void onTouchEnded(Touch*touch, Event*ev)override;

	virtual void Show();
	virtual void Hide();
	void SetCallback(HomeSceneCallback*callback) { this->m_callback = callback; }

	void OnPlayButtonClicked();

	void SetBestScore(int score);
};