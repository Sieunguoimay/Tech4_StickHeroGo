#include "Stick.h"
#include"ActionRunner.h"
USING_NS_CC;
Stick::Stick()
{
	CCLOG("Created a stick");
	m_length = 0.0f;
}

bool Stick::init()
{
	DrawNode::init();
	drawSolidRect(Vec2(0, 0), Vec2(10, m_maxLength), Color4F(1.0f, 1.0f, 1.0f, 0.5f));
	setScaleY(0.0f);
	return true;
}

Stick::~Stick()
{
	CCLOG("Deleted a stick");
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
		ActionRunner::getInstance()->addAction(new RotateByAmount(0.5f,90.0f,this,	
			[this]() {
				if (m_state == FALLING)
					m_state = FELL;
			}));
	}
	else if (m_state == FELL) {
		m_state = DONE;
	}
}


void Stick::fall()
{
}
