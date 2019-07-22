#include "HomeScene.h"

bool HomeScene::init()
{

	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->setSwallowTouches(true);
	m_touchListener->onTouchBegan = CC_CALLBACK_2(HomeScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(HomeScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(HomeScene::onTouchEnded, this);
	return true;
}

bool HomeScene::onTouchBegan(Touch * touch, Event * ev)
{
	CCLOG("touch ,.,..,");
	return true;
}

void HomeScene::onTouchMoved(Touch * touch, Event * ev)
{
}

void HomeScene::onTouchEnded(Touch * touch, Event * ev)
{
}

void HomeScene::AddTouchListener()
{
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
}
