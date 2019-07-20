#include "Character.h"


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
	this->scheduleUpdate();
	m_fallNow = false;
	CCLOG("Player created %d",this->getChildrenCount());
}

void Character::update(float deltaTime) {
	if (m_fallNow&&_position.x>= m_fallPoint) {
		m_fallNow = false;
		this->stopAction(m_moveAction);
		this->runAction(Sequence::create(
			MoveBy::create(0.5f, Vec2(0.0f, -_position.y)),
			CallFunc::create([this]() {
				CCLOG("GAME OVER");
			})
		,nullptr));
	}
}

void Character::MoveToTarget(float distance, float fallDistance)
{
	if (fallDistance > 0) {
		fallDistance += GetWidth() / 2 + 10;
		m_fallNow = true;
		m_fallPoint = _position.x + fallDistance;
	}


	m_moveAction = MoveBy::create(1.0f, Vec2(std::max(distance, fallDistance), 0.0f));
	this->runAction(m_moveAction);
}

