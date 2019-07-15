#include"GameScene.h"
#include"PauseScene.h"
USING_NS_CC;
cocos2d::Scene * GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_SHAPE);
	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

GameScene::~GameScene()
{

	ActionRunner::cleanUp();

	//how we clean up what we created
	delete m_character;
	for (ListNode<Pillar*>* it = m_pillars.first(); it != m_pillars.tail; it = it->next) {
		delete it->data;
	}
}


bool GameScene::init()
{
	if (!Layer::init()) return false;

	srand(time(0));

	setupMenu();
	setupEventHandler();
	scheduleUpdate();



	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT,3);
	//auto edgeNode = Node::create();
	//edgeNode->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//edgeNode->setPhysicsBody(edgeBody);
	//addChild(edgeNode);

	//m_background = Background::createBackground();
	//m_background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(m_background);

	m_pBackground = Background::create();
	addChild(m_pBackground);

	auto a = createPillar(Vec2(visibleSize.width/4, 0),true);
	m_pillars.push_back(a);
	a->setHasSpawnedOne(true);
	auto b = createPillar(Vec2(visibleSize.width / 4*3, 0), true);

	m_pillars.push_back(b);
	m_pPillarNodePointer = m_pillars.last();


	auto&firstSpritePos = m_pillars.first()->data->getSprite()->getPosition();
	auto&firstSpriteSize = m_pillars.first()->data->getSprite()->getContentSize();
	
	m_character = new Character(this);
	m_character->init(Vec2(firstSpritePos.x,
		firstSpritePos.y + firstSpriteSize.height / 2
		+ m_character->getSprite()->getContentSize().height / 2));
	m_character->moveToNextPillar(a);
	return true;
}



void GameScene::update(float deltaTime)
{
	const float cameraSpeed = 40.0f;
	auto camera = Camera::getDefaultCamera();
	
	ActionRunner::getInstance()->update(deltaTime);
	m_pBackground->setPosition(camera->getPosition() - visibleSize / 2);

	//loop through all the pillar for updating
	for (ListNode<Pillar*>* it = m_pillars.first(); it != m_pillars.tail; it = it->next) {
		
		auto&pillar = it->data;
		auto&pos = pillar->getSprite()->getPosition();
		auto&size = pillar->getSprite()->getContentSize();
		
		if (pillar->getStick()->hasFell()) {
			moveCamera(camera);
		}

		pillar->getStick()->update(deltaTime);

		if (pillar->checkOnCamera(visibleSize, camera->getPosition())) {
			if (!pillar->hasSpawnedOne()) {
				CCLOG("has Spawned One");
				m_pillars.push_back(createPillar(pos+Vec2(size.width/2+1,0)));
				pillar->setHasSpawnedOne(true);
			}
		}
		else {
			if (pillar->hasSpawnedOne()) {
				CCLOG("It's time to delete pillar");
				delete pillar;
				it = m_pillars.erase(it);
			}
		}

	}


}






Pillar* GameScene::createPillar(const Vec2 & origin, bool atInit /*= false*/)
{
	float r_dis = std::min(std::max(CCRANDOM_0_1(), 0.2f), 0.9f)*visibleSize.width;
	const float r_size = std::min(std::max(0.5f + CCRANDOM_0_1(), 0.7f), 1.3f);
	const auto pillar = new Pillar(this, r_size);
	auto& size = pillar->getSprite()->getContentSize();

	if (atInit) {
		pillar->init(Vec2(origin.x, size.height / 2));
	}else
		pillar->init(Vec2(origin.x + size.width / 2 + r_dis, size.height / 2));
	return pillar;
}

void GameScene::moveCamera(Camera *camera)
{

	auto temp = m_pPillarNodePointer;
	int count = 0;
	while (temp->next != m_pillars.tail) {
		count++;
		temp = temp->next;
	}
	CCLOG("How many next: %d", count);


	if (m_pPillarNodePointer->next != m_pillars.tail &&!m_cameraMoving) {
		doSomethingOnAStickFellDown();


		const float movingTime = 1.0f;
		auto&a = m_pPillarNodePointer->data->getSprite()->getPosition();
		auto&b = m_pPillarNodePointer->next->data->getSprite()->getPosition();
		auto target = Vec2((b.x + a.x)*0.5f, camera->getPosition().y);
		
		m_pBackground->moveAlongCamera(movingTime, target-camera->getPosition());

		m_cameraMoving = true;
		ActionRunner::getInstance()->addAction(new MoveToTarget(movingTime, target, camera, [this]() {
			m_cameraMoving = false;
			m_pPillarNodePointer = m_pPillarNodePointer->next;
			}));
	}
}

void GameScene::doSomethingOnAStickFellDown()
{
	m_character->moveToNextPillar(m_pPillarNodePointer->data);
}








void GameScene::setupMenu()
{
	auto button = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameScene::menuPauseCallback, this));
	if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
		printf("Error while loading: %s or %s\n", "CloseNormal.png", "CloseSelected.png");
	else
		button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	auto menu = Menu::create(button, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void GameScene::setupEventHandler()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);


}

bool GameScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * ev)
{
	if (m_cameraMoving )return true;

    //if (m_pPillarNodePointer->prev == m_pillars.head)
    //    m_pPillarNodePointer->data->getStick()->startEnlongating();
    //else
        m_pPillarNodePointer->prev->data->getStick()->startEnlongating();
	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * ev)
{
}

void GameScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * ev)
{
	if (m_cameraMoving)return;

    //if (m_pPillarNodePointer->prev == m_pillars.head)
    //    m_pPillarNodePointer->data->getStick()->stopEnlongating();
    //else
        m_pPillarNodePointer->prev->data->getStick()->stopEnlongating();
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	const float cameraSpeed = 10.0f;
	auto camera = Camera::getDefaultCamera();
	
	CCLOG(" key pressed %d", keyCode);
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		camera->setPosition(camera->getPosition() + Vec2(-cameraSpeed, 0));
		break;
	case EventKeyboard::KeyCode::KEY_D:
		camera->setPosition(camera->getPosition() + Vec2(cameraSpeed, 0));
		break;
	case EventKeyboard::KeyCode::KEY_S:
		camera->setPosition(camera->getPosition() + Vec2(0,-cameraSpeed));
		break;
	case EventKeyboard::KeyCode::KEY_W:
		camera->setPosition(camera->getPosition() + Vec2(0, cameraSpeed));
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		moveCamera(camera);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		//moveCamera(camera);
		if (m_cameraMoving)break;

		//if (m_pPillarNodePointer->prev == m_pillars.head)
		//	m_pPillarNodePointer->data->getStick()->startEnlongating();
		//else
			m_pPillarNodePointer->prev->data->getStick()->startEnlongating();
		break;
	}
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		break;
	case EventKeyboard::KeyCode::KEY_D:
		break;
	case EventKeyboard::KeyCode::KEY_S:
		break;
	case EventKeyboard::KeyCode::KEY_W:
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		//moveCamera(camera);
		if (m_cameraMoving )break;

		//if (m_pPillarNodePointer->prev == m_pillars.head)
		//	m_pPillarNodePointer->data->getStick()->stopEnlongating();
		//else
			m_pPillarNodePointer->prev->data->getStick()->stopEnlongating();
		break;
	}
}





void GameScene::menuPauseCallback(cocos2d::Ref * pSender)
{
	CCLOG("Paused");
	Director::getInstance()->pushScene(PauseScene::createScene());
}

void GameScene::menuGameOverCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(PauseScene::createScene());
}




