#include "Stick.h"
#include"ActionRunner.h"
USING_NS_CC;
Stick::Stick(cocos2d::Layer * pLayer)
	:m_pLayer(pLayer)
{
	CCLOG("Created a stick");

	m_drawer = DrawNode::create();
	pLayer->addChild(m_drawer);
	m_drawer->drawSolidRect(Vec2(0, 0), Vec2(10, m_maxLength), Color4F(1.0f, 1.0f, 1.0f, 0.5f));
	m_drawer->setScaleY(0.0f);
	m_length = 0.0f;
}

Stick::~Stick()
{
	m_pLayer->removeChild(m_drawer,true);
	CCLOG("Deleted a stick");
}

void Stick::update(float deltaTime)
{
	if (m_state == ENLONGATING) {
		if (m_length < m_maxLength) {
			m_length = std::min(m_length + m_enLongatingSpeed*deltaTime, m_maxLength);
			m_drawer->setScaleY(m_length / m_maxLength);
		}
	}
	else if (m_state == ENLONGATED) {
		m_state = FALLING;
		ActionRunner::getInstance()->addAction(RotateByAmount::create(1.0f,90.0f,m_drawer,	
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
