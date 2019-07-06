#include "ActionRunner.h"
#include"Utils.h"
ActionRunner*ActionRunner::s_instance = nullptr;
void ActionRunner::cleanUp()
{
	delete s_instance;
	s_instance = nullptr;
	CCLOG("Deleted ActionRunner");
}
ActionRunner * ActionRunner::getInstance()
{
	if (s_instance == nullptr) {
		CCLOG("Created ActionRunner");
		s_instance = new ActionRunner();
	}
	return s_instance;
}
void ActionRunner::update(float deltaTime)
{
	for (auto it = m_actions.first(); it != m_actions.tail; it = it->next) {
		it->data->m_timer = std::min(it->data->m_timer+deltaTime, it->data->m_duration);
		it->data->run(it->data->m_timer/it->data->m_duration);
		if (it->data->m_timer >= it->data->m_duration) {
			delete it->data;
			it = m_actions.erase(it);
		}
	}
}

MyAction * MoveToTarget::create(float duration, const cocos2d::Vec2 & target, cocos2d::Node * node)
{

	auto action = new MoveToTarget();
	action->m_duration = duration;
	action->m_target = target;
	action->m_pNode = node;
	action->m_oldPos = node->getPosition();
	return action;
}

void MoveToTarget::run(float a)
{
	float b = bezier4(0, 0.0, 1.0, 1.0, a);
	m_pNode->setPosition(m_oldPos + b*(m_target - m_oldPos));
}

RotateByAmount::~RotateByAmount()
{
	if (m_callback!= nullptr) {
		m_callback();
		m_callback = nullptr;
	}
}

MyAction * RotateByAmount::create(float duration, const float & amount, cocos2d::Node * node, std::function<void()>callback)
{
	auto action = new RotateByAmount();
	action->m_timer = 0;
	action->m_duration = duration;
	action->m_amount = amount;
	action->m_oldAngle = node->getRotation();
	action->m_pNode = node;
	action->m_callback = callback;
	return action;
}

void RotateByAmount::run(float a)
{
	float b = bezier4(0.0f, 0.0f, 0.0f, 1.0, a);
	m_pNode->setRotation(m_oldAngle + b*m_amount);
}
