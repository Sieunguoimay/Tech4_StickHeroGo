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
	
	auto pillar = Pillar::createPillar(this,true);
	this->addChild(pillar);
	pillar->initPillar(this, 
		Vec2(m_visibleSize.width / 2, pillar->getContentSize().height / 2)
	,1.0f,true,0);
	m_pillars.push_back(pillar);

	auto pillar2 = Pillar::createPillar(this);
	this->addChild(pillar2);
	pillar2->initPillar(this,
		Vec2(Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, 0.1f, 0.5f) *m_visibleSize.width
			+ m_visibleSize.width / 2
			+ pillar->GetWidth()/2+pillar2->GetWidth()/2
		, pillar2->getContentSize().height / 2)
	,1.0f,false,1);
	m_pillars.push_back(pillar2);

	m_nextPillarIndex = 1;
	m_moveFlag = false;

	m_pillarCountSoFar = 1;

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


		float posVar = Utils::map(m_pillarCountSoFar, 0, 100, 0.5f, 1.2f);
		float r_pos = Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, posVar/5.0f, posVar);
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


		pillar->initPillar(this, pos, r_size,false, m_pillarCountSoFar);

		m_pillars.push_back(pillar);
		m_pillarCountSoFar++;

		resetPosition();
	}


}

float Platform::MoveAndCalculateScale()
{
	if (m_moveFlag) return -1.0f;
	auto& pillar1Pos = m_pillars[m_nextPillarIndex]->getPosition();
	auto& pillar1Size = m_pillars[m_nextPillarIndex]->getContentSize();
	auto pillar1ScaleX = m_pillars[m_nextPillarIndex]->getScaleX();

	auto& pillar2Pos = m_pillars[m_nextPillarIndex + 1]->getPosition();
	auto& pillar2Size = m_pillars[m_nextPillarIndex + 1]->getContentSize();
	auto pillar2ScaleX = m_pillars[m_nextPillarIndex + 1]->getScaleX();


	auto target = 0.5f * (pillar1Pos.x - pillar1Size.width * pillar1ScaleX / 2 + pillar2Pos.x + pillar2Size.width * pillar2ScaleX / 2);
	float distance = target - (-this->_position.x) - m_visibleSize.width / 2;


	m_moveFlag = true;
	m_pMoveAction = Sequence::create(
		MoveBy::create(1.0f, Vec2(-distance, 0)),
		CallFunc::create([this]() {
			m_moveFlag = false;
			m_nextPillarIndex++;
			CCLOG("Sequence done");
		}), nullptr);

	this->runAction(m_pMoveAction);



	float pillarDistance = std::abs(pillar1Pos.x - pillar2Pos.x) + pillar1Size.width * pillar1ScaleX / 2 + pillar2Size.width * pillar2ScaleX / 2 + pillar2Size.width;
	float scale = std::min(1.0f, m_visibleSize.width / pillarDistance);
	return scale;
}

void Platform::FirstMovementOnGameStart()
{
	auto& pillar1Pos = m_pillars[0]->getPosition();
	auto& pillar1Size = m_pillars[0]->getContentSize();
	auto pillar1ScaleX = m_pillars[0]->getScaleX();

	auto& pillar2Pos = m_pillars[1]->getPosition();
	auto& pillar2Size = m_pillars[1]->getContentSize();
	auto pillar2ScaleX = m_pillars[1]->getScaleX();

	auto target = 0.5f * (pillar1Pos.x - pillar1Size.width * pillar1ScaleX / 2 + pillar2Pos.x + pillar2Size.width * pillar2ScaleX / 2);
	float distance = target - (-this->_position.x) - m_visibleSize.width / 2;

	this->runAction(MoveBy::create(0.5f, Vec2(-distance,0.0f)));
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
