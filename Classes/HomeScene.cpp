#include "HomeScene.h"
#include"utils//Definitions.h"
bool HomeScene::init()
{
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->setSwallowTouches(true);
	m_touchListener->onTouchBegan = CC_CALLBACK_2(HomeScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(HomeScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(HomeScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);

	auto menuItemPlayButton = MenuItemImage::create("button_play.png", "button_play_clicked.png",CC_CALLBACK_0(HomeScene::OnPlayButtonClicked,this));
	auto menu = Menu::create(menuItemPlayButton, nullptr);
	this->addChild(menu);
	menuItemPlayButton->setScale(100.0f / menuItemPlayButton->getContentSize().width);

	m_bestScore = Label::createWithSystemFont("BEST 1234", "Calibri",30.0f);
	this->addChild(m_bestScore);
	m_bestScore->setPosition(Vec2(0.0f, m_visibleSize.height / 4) + m_visibleSize / 2);

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

void HomeScene::Show()
{
	CCLOG("Show homeScene");
	this->setVisible(true);
	_eventDispatcher->resumeEventListenersForTarget(this);
}

void HomeScene::Hide()
{
	CCLOG("Hide HomeScene");
	this->setVisible(false);
	_eventDispatcher->pauseEventListenersForTarget(this);
}

void HomeScene::OnPlayButtonClicked()
{
	if(m_callback!=nullptr)
		m_callback->OnPlayButtonClicked();
}