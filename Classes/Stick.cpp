#include "Stick.h"
#include"ActionRunner.h"
#include"utils/Definitions.h"
#include"SimpleAudioEngine.h"
Stick * Stick::createStick()
{
	auto stick = Stick::create();
	
	return stick;
}

bool Stick::init()
{
	if (!DrawNode::init())return false;
	scheduleUpdate();
	this->drawSolidRect(Vec2(0, 5), Vec2(5, m_maxLength+5), Color4F(0.4f, 0.2f, 0.2f, 1.0f));
	this->setScaleY(0.0f);
	m_state = START;

	CCLOG("Stick created %d", this->getChildrenCount());
	return true;
}


Stick::~Stick()
{
	CCLOG("Stick deleted %f %f", _position.x, _position.y);
}

void Stick::update(float deltaTime)
{
	if (m_state == ENLONGATING) {
		if (m_length < m_maxLength) {
			m_length = std::min(m_length + m_enLongatingSpeed*deltaTime, m_maxLength);
			setScaleY(m_length / m_maxLength);
		}
	}
	else if (m_state == ENLONGATED) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(m_soundId);
		m_state = FALLING;
		this->runAction(Sequence::create(
			EaseOut::create(RotateTo::create(0.4f, 90.0f),0.25f), 
			CallFunc::create([this]() {
				m_state = FELL;
			}), nullptr));
		CCLOG("ENLONGATED");
	}
	else if (m_state == FELL) {
		m_state = DONE;
		CCLOG("DONE");
	}
}

void Stick::Enlongate()
{
	if (m_state == START) {
		m_state = ENLONGATING;
		CCLOG("Speak up");
		m_soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/stick_enlongating.mp3",true);
	}
}

void Stick::Fall()
{
	this->runAction(EaseOut::create(RotateTo::create(0.4f, 180.0f), 0.25f));
}
