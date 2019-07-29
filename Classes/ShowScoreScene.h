#pragma once
#include"HomeScene.h"
class ShowScoreScene :public HomeScene {
	Label* m_score;
public:
	CREATE_FUNC(ShowScoreScene);

	bool init()override;
	void OnOkButtonClicked();

	void Show()override;
	void Hide()override;
	void SetScore(int score) { m_score->setString(std::to_string(score)); }
};