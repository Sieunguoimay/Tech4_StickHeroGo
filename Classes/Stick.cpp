#include "Stick.h"
#include"ActionRunner.h"

Stick * Stick::createStick()
{
	auto stick = Stick::create();
	
	return stick;
}

bool Stick::init()
{
	if (!DrawNode::init())return false;
	scheduleUpdate();

	this->drawSolidRect(Vec2(0, 0), Vec2(10, m_maxLength), Color4F(1.0f, 1.0f, 1.0f, 0.5f));
	this->setScaleY(0.0f);
	m_state = START;

	CCLOG("Stick created %d", this->getChildrenCount());
	return true;
}


Stick::~Stick()
{
	CCLOG("Stick deleted");
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
		m_state = FALLING;
		this->runAction(Sequence::create(
			RotateTo::create(0.5f, 90.0f), 
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

