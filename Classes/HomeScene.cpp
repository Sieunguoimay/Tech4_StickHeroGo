#include "HomeScene.h"
#include"utils//Definitions.h"
#include"SimpleAudioEngine.h"
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
	menuItemPlayButton->setPosition(0, -m_visibleSize.height/4);
	



	auto logo = Sprite::createWithSpriteFrameName("logo.png");
	this->addChild(logo);
	logo->setPosition(Vec2(10.0f, m_visibleSize.height / 3) + m_visibleSize / 2);


	m_bestScore = Label::createWithSystemFont("BEST 1234", "Calibri", 25.0f);
	this->addChild(m_bestScore);
	m_bestScore->setPosition(Vec2(m_visibleSize.width/2, logo->getPosition().y-logo->getContentSize().height/2-20));
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
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button_clicked.mp3");

	if(m_callback!=nullptr)
		m_callback->OnPlayButtonClicked(CI_HOME_SCENE);
}

void HomeScene::SetBestScore(int score)
{
	char s[10];
	sprintf(s, "BEST %d", score);
	m_bestScore->setString(s);
}
