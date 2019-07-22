#include "OnScreenInfoDisplay.h"
#include"utils/Definitions.h"
bool OnScreenInfoDisplay::init()
{
	if (!Layer::init())return false;
	this->setGlobalZOrder(GAME_LAYER_3);

	m_pTextScore = Label::createWithSystemFont("0", "Calibri", 30.0f);
	this->addChild(m_pTextScore);
	m_pTextScore->setPosition(Vec2(0.0f, m_visibleSize.height / 4)+ m_visibleSize / 2);
	CCLOG("OnScreenInfoDisplay created");
	return true;
}

OnScreenInfoDisplay::~OnScreenInfoDisplay()
{
	CCLOG("OnScreenInfoDisplay deleted");
}
