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
	CCLOG("Player created %d",this->getChildrenCount());
}

void Character::MoveToTarget(const Vec2 & target)
{
	this->runAction(MoveTo::create(1.0f, target));
}

