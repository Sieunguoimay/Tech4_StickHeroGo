#pragma once
#include"GameLayer.h"
class OnScreenInfoDisplay :public GameLayer{
	Label*m_pTextScore;
public:
	CREATE_FUNC(OnScreenInfoDisplay);
	bool init()override;
	~OnScreenInfoDisplay()override;
	void SetScore(int score) { m_pTextScore->setString(std::to_string(score)); }
};
