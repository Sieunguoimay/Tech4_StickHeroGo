#include"ShowScoreScene.h"

bool ShowScoreScene::init() {

	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->setSwallowTouches(true);
	m_touchListener->onTouchBegan = CC_CALLBACK_2(HomeScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(HomeScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(HomeScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);


	auto background = DrawNode::create();
	background->drawSolidRect(Vec2(0.0f,0.0f),Vec2(m_visibleSize.width,m_visibleSize.height),Color4F(19.0f/255,12.0f/255.0f,25.0f/255.0f,0.9f));
	this->addChild(background);

	auto menuItemPlayButton = MenuItemImage::create("back_button.png", "back_button_clicked.png", CC_CALLBACK_0(ShowScoreScene::OnOkButtonClicked, this));
	auto menu = Menu::create(menuItemPlayButton, nullptr);
	this->addChild(menu);
	menuItemPlayButton->setPosition(0, -m_visibleSize.height / 4);


	m_bestScore = Label::createWithSystemFont("BEST 1234", "Calibri", 35.0f);
	this->addChild(m_bestScore);
	m_bestScore->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);

	m_score = Label::createWithSystemFont("1234", "Calibri", 100.0f);
	this->addChild(m_score);
	m_score->setPosition(Vec2(0.0f, m_visibleSize.height / 8) + m_visibleSize / 2);
	
	
	return true;
}
void ShowScoreScene::OnOkButtonClicked()
{
	Hide();
}
void ShowScoreScene::Show(){
	HomeScene::Show();
	this->setPosition(0.0f, -m_visibleSize.height);
	this->runAction(MoveTo::create(0.2f,Vec2(0.0f,0.0f)));

}
void ShowScoreScene::Hide(){
	this->setPosition(0.0f, 0.0f);
	this->runAction(Sequence::create(
		MoveTo::create(0.2f, Vec2(0.0f, -m_visibleSize.height)),
		CallFunc::create([this]() {
			HomeScene::Hide();
			if (m_callback != nullptr)
				m_callback->OnPlayButtonClicked(CI_SHOW_SCORE_SCENE);
		}),nullptr));
}
