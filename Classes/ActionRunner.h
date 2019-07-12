#pragma once
#include"cocos2d.h"
#include"list.h"
class BaseAction {
protected:
	float m_timer = 0;
	float m_duration;
	friend class ActionRunner;
public:
	BaseAction(float duration, float timer = 0, const char*action_name = "")
		:m_duration(duration),m_timer(timer) { CCLOG("New Action Created %s", action_name); }
	virtual ~BaseAction(){ CCLOG("Another Action Deleted"); }
	virtual void run(float a)=0;
};

class ActionRunner {
	List<BaseAction *>m_actions;
	static ActionRunner*s_instance;

	ActionRunner(){CCLOG("Created ActionRunner");}
	ActionRunner(const ActionRunner&){}
	ActionRunner&operator=(const ActionRunner&){}
public:
	~ActionRunner();
	static void cleanUp();
	static ActionRunner*getInstance();
	void addAction(BaseAction *action) { m_actions.push_back(action); }
	void update(float deltaTime);
};









class MoveToTarget :public BaseAction {
	cocos2d::Vec2 m_target;
	cocos2d::Vec2 m_oldPos;
	cocos2d::Node*m_pNode;
public:
	MoveToTarget(float duration, const cocos2d::Vec2&target, cocos2d::Node*node);
	void run(float a)override;
};

class RotateByAmount:public BaseAction {
	float m_amount;
	float m_oldAngle;
	cocos2d::Node*m_pNode;
	std::function<void()>m_callback;
public:
	RotateByAmount(float duration, const float&amount, cocos2d::Node*node, std::function<void()>callback);
	~RotateByAmount()override;
	void run(float a)override;
};