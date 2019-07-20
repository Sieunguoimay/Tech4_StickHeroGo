#pragma once
#include"cocos2d.h"
#include"utils/list.h"
class BaseAction {
protected:
	float m_timer = 0;
	float m_duration;
	std::function<void()>m_callback;

	friend class ActionRunner;
public:
	BaseAction(float duration, float timer = 0, const char*action_name = "", std::function<void()>callback = nullptr)
		:m_duration(duration),m_timer(timer),m_callback(callback) { CCLOG("New Action Created %s", action_name); }
	virtual ~BaseAction();
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
public:
	MoveToTarget(float duration, const cocos2d::Vec2&target, cocos2d::Node*node, std::function<void()>callback = nullptr);
	void run(float a)override;
	cocos2d::Node* m_pNode;
};

class MoveByAmount:public BaseAction {
	cocos2d::Vec2 m_amount;
	cocos2d::Vec2 m_oldPos;
	cocos2d::Node* m_pNode;
public:
	MoveByAmount(float duration, const cocos2d::Vec2& amount, cocos2d::Node* node, std::function<void()>callback = nullptr);
	void run(float a)override ;
};

class RotateByAmount:public BaseAction {
	float m_amount;
	float m_oldAngle;
	cocos2d::Node*m_pNode;
public:
	RotateByAmount(float duration, const float&amount, cocos2d::Node*node, std::function<void()>callback = nullptr);
	void run(float a)override;
};