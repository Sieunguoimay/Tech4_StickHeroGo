#include "Platform.h"
#include"utils/Utils.h"
#include"utils/Definitions.h"
Platform::~Platform()
{
	CCLOG("Platform deleted");
}


Platform * Platform::createPlatform()
{
	auto platform = Platform::create();

	//pass in something here..
	
	return platform;
}

bool Platform::init()
{
	if (!Layer::init())return false;
	this->scheduleUpdate();
	//create children here..
	
	auto pillar = Pillar::createPillar(this);
	this->addChild(pillar);
	m_pillars.push_back(pillar);
	pillar->setPosition(Vec2(m_visibleSize.width / 4, pillar->getContentSize().height / 2));

	auto pillar2 = Pillar::createPillar(this);
	this->addChild(pillar2);
	m_pillars.push_back(pillar2);
	pillar2->setPosition(Vec2(m_visibleSize.width / 4*3, pillar2->getContentSize().height / 2));

	m_nextPillarIndex = 1;
	m_moveFlag = false;
	CCLOG("Platform created %d %f %f",this->getChildrenCount(),this->getAnchorPointInPoints().x, this->getAnchorPointInPoints().y);
	return true;
}

void Platform::update(float deltaTime)
{
	for (auto&callback : m_callbacks)
		callback->UpdatePosition(_position);

	if (m_pillars.size() <= 0) return;

	if (m_pillars[0]->HasDone()) {
		this->removeChild(m_pillars[0]);
		m_pillars.erase(m_pillars.begin());
		m_nextPillarIndex--;
	}

	if (m_pillars.back()->ReadyForSpawning()) {


		auto pillar = Pillar::createPillar(this);
		this->addChild(pillar);

		float r_pos = Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, 0.0f, 1.0f);
		float r_size = Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, 0.4f, 1.5f);

		float deltaOffScreenOfTheLastPillar = std::max(
			m_pillars.back()->getPosition().x + m_pillars.back()->GetWidth() / 2 
				+ _position.x - m_visibleSize.width, 0.0f);
		Vec2 pos(
			-_position.x + m_visibleSize.width +
			deltaOffScreenOfTheLastPillar +
			pillar->GetWidth() / 2 +
			m_visibleSize.width*r_pos,
			pillar->getContentSize().height / 2);

		pillar->setScaleX(r_size);
		pillar->setPosition(pos);

		m_pillars.push_back(pillar);



		resetPosition();
	}


}

float Platform::MoveAndCalculateScale()
{
	if (m_moveFlag) return -1.0f;

	auto&pillar1Pos = m_pillars[m_nextPillarIndex]->getPosition();
	auto&pillar1Size = m_pillars[m_nextPillarIndex]->getContentSize();
	auto pillar1ScaleX = m_pillars[m_nextPillarIndex]->getScaleX();

	auto&pillar2Pos = m_pillars[m_nextPillarIndex+1]->getPosition();
	auto&pillar2Size = m_pillars[m_nextPillarIndex+1]->getContentSize();
	auto pillar2ScaleX = m_pillars[m_nextPillarIndex+1]->getScaleX();




	float pillarDistance = std::abs(pillar1Pos.x - pillar2Pos.x) + pillar1Size.width*pillar1ScaleX / 2 + pillar2Size.width*pillar2ScaleX / 2+ pillar2Size.width;
	float scale = std::min(1.0f, m_visibleSize.width / pillarDistance);



	auto target = 0.5f*(pillar1Pos.x-pillar1Size.width*pillar1ScaleX/2 + pillar2Pos.x+pillar2Size.width*pillar2ScaleX/2);
	float distance = target - (-this->_position.x) - m_visibleSize.width/2;

	m_moveFlag = true;
	this->runAction(Sequence::create(
		MoveBy::create(1.0f, Vec2(-distance, 0)),
		CallFunc::create([this]() {
			m_moveFlag = false;
			m_nextPillarIndex++;
			CCLOG("Sequence done");
		}), nullptr));

	return scale;
}

void Platform::resetPosition()
{
	CCLOG("Pos %f", _position.x);
	if (_position.x < -2000) {
		for (auto&child : _children)
			child->setPosition(child->getPosition()+ Vec2(_position.x,0));
		this->setPosition(0.0f, _position.y);


		for (auto&callback : m_callbacks)
			callback->ResetPosition();
	}
}
