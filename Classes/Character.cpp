#include "Character.h"
#include"GameParticleSystem.h"
#include"utils/Definitions.h"
#include"SimpleAudioEngine.h"
Character::~Character()
{
	CCLOG("Deleted player");
}

Character * Character::createCharacter()
{
	auto character = new Character();
	if (character&&character->initWithSpriteFrameName("main_character.png")) {
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
	m_state = CS_STANDING;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main_character_run.plist");
	this->addChild(SpriteBatchNode::create("main_character_run.png"));

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main_character_stand.plist");
	this->addChild(SpriteBatchNode::create("main_character_stand.png"));


	//standing
	auto animation_stand = Animation::create();
	for (int i = 0; i < 6; i++) {
		auto s = String::createWithFormat("main_character_stand_%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(s->getCString());
		animation_stand->addSpriteFrame(frame);
	}
	animation_stand->setDelayPerUnit(0.1f);
	animation_stand->setRestoreOriginalFrame(true);
	m_animateActions[CS_STANDING] = RepeatForever::create(Animate::create(animation_stand));
	m_animateActions[CS_STANDING]->retain();

	//running
	auto animation_run = Animation::create();
	for (int i = 0; i < 8; i++) {
		auto s = String::createWithFormat("main_character_run_%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(s->getCString());
		animation_run->addSpriteFrame(frame);
	}
	animation_run->setDelayPerUnit(0.1f);
	animation_run->setRestoreOriginalFrame(true);
	m_animateActions[CS_RUNNING] = RepeatForever::create(Animate::create(animation_run));
	m_animateActions[CS_RUNNING]->retain();

	this->runAction(m_animateActions[CS_STANDING]);

	CCLOG("Player created %d",this->getChildrenCount());
}

void Character::update(float deltaTime) {


	if (m_state == CS_FALL_START)m_state = CS_FALLING;
	else if (m_state == CS_DIED) m_state = CS_DONE;
	else if (m_state == CS_STAND) m_state = CS_STANDING;
	else if (m_state == CS_RUN)m_state = CS_RUNNING;
		
}

void Character::FirstMovementOnGameStart(const Vec2& pos)
{
	this->runAction(MoveTo::create(0.4f, pos));
}

void Character::MoveToTarget(float distance, float fallDistance)
{
	m_xTarget = distance;
	if (fallDistance > 0) {
		fallDistance += GetWidth() / 2 + 10;
		m_state = CS_FALL;
		m_fallPoint = _position.x + fallDistance;
		m_xTarget = fallDistance;
	}
	else {
		m_state = CS_RUN;
	}

	m_moveAction = MoveBy::create(1.0f, Vec2(m_xTarget, 0.0f));
	this->stopAllActions();
	this->runAction(
		Sequence::create(m_moveAction, 
			CallFunc::create([=]() {

				this->stopAllActions();

				if (m_state == CS_RUNNING) {
					m_state = CS_STAND;
					this->runAction(m_animateActions[CS_STANDING]);
				}
				else if(m_state == CS_FALL){
					m_state = CS_FALL_START;
					this->runAction(Sequence::create(
						EaseOut::create(MoveBy::create(0.5f, Vec2(0.0f, -_position.y)), 0.3f),
						CallFunc::create([this]() {
							if (m_state == CS_FALLING) m_state = CS_DIED;
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/fall_into_water.mp3");
							}), nullptr));

				}
			}),nullptr));
	this->runAction(m_animateActions[CS_RUNNING]);
}

