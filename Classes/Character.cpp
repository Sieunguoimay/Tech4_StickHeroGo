#include "Character.h"
#include"GameParticleSystem.h"
#include"utils/Definitions.h"
Character::~Character()
{
	CCLOG("Deleted player");
}

Character * Character::createCharacter()
{
	auto character = new Character();
	if (character&&character->initWithFile("main_character.png")) {
		character->initCharacter();
		character->autorelease();
		return character;
	}
	CC_SAFE_DELETE(character);
	return nullptr;
}

void Character::initCharacter()
{
	this->setGlobalZOrder(GAME_LAYER_1);
	this->scheduleUpdate();
	m_state = CS_LIVE;
	CCLOG("Player created %d",this->getChildrenCount());
}

void Character::update(float deltaTime) {
	if ((m_state == CS_FALL)&&_position.x>= m_fallPoint) {
		m_state = CS_FALL_START;
		this->stopAction(m_moveAction);
		this->runAction(Sequence::create(
			MoveBy::create(0.5f, Vec2(0.0f, -_position.y)),
			CallFunc::create([this]() {
				if (m_state == CS_FALLING) m_state = CS_DIED;
			})
		,nullptr));
	}else if (m_state == CS_FALL_START)m_state = CS_FALLING;
	else if (m_state == CS_DIED) m_state = CS_DONE;
	
}

void Character::MoveToTarget(float distance, float fallDistance)
{
	if (fallDistance > 0) {
		fallDistance += GetWidth() / 2 + 10;
		m_state = CS_FALL;
		m_fallPoint = _position.x + fallDistance;
	}


	m_moveAction = MoveBy::create(1.0f, Vec2(std::max(distance, fallDistance), 0.0f));
	this->runAction(m_moveAction);
}

