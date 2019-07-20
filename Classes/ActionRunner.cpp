#include "ActionRunner.h"
#include"utils/Utils.h"
BaseAction::~BaseAction() {
	CCLOG("Another Action Deleted"); 	

	if (m_callback != nullptr) {
		try {
			m_callback();
		}
		catch (int e) {}
		m_callback = nullptr;
	}
}

ActionRunner*ActionRunner::s_instance = nullptr;
void ActionRunner::cleanUp()
{
	delete s_instance;
	s_instance = nullptr;
}
ActionRunner * ActionRunner::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new ActionRunner();
	}
	return s_instance;
}



ActionRunner::~ActionRunner()
{
	for (auto it = m_actions.first(); it != m_actions.tail; it = it->next) {
		delete it->data;
	}
	CCLOG("Deleted ActionRunner");
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









MoveToTarget::MoveToTarget(float duration, const cocos2d::Vec2 & target, cocos2d::Node * node, std::function<void()>callback)
	:BaseAction(duration,0,"MoveToTarget",callback)
	,m_target(target), m_pNode(node),m_oldPos(node->getPosition())
{}

void MoveToTarget::run(float a)
{
	if (m_pNode == nullptr)return;
	float b = Utils::bezier4(0, 0.0, 1.0, 1.0, a);
	m_pNode->setPosition(m_oldPos + b*(m_target - m_oldPos));
}








RotateByAmount::RotateByAmount(float duration, const float & amount, cocos2d::Node * node, std::function<void()>callback)
	:BaseAction(duration,0,"RotateByAmount", callback)
	,m_amount(amount)
	,m_oldAngle(node->getRotation())
	,m_pNode(node)
{}


void RotateByAmount::run(float a)
{
	if (m_pNode == nullptr)return;
	const float b = Utils::bezier4(0.0f, 0.0f, 0.0f, 1.0, a);
   	m_pNode->setRotation(m_oldAngle + b*m_amount);
}

MoveByAmount::MoveByAmount(float duration, const cocos2d::Vec2& amount, cocos2d::Node* node, std::function<void()> callback)
	:BaseAction(duration,0,"MoveByAmount", callback),m_amount(amount),m_pNode(node)
{}


void MoveByAmount::run(float a)
{
	if (m_pNode == nullptr)return;
	const float b = Utils::bezier4(0.0f, 0.0f, 0.0f, 1.0, a);
	m_pNode->setPosition(m_oldPos + b * m_amount);
}
