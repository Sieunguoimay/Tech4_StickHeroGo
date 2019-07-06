#pragma once
#include"cocos2d.h"
#include"list.h"
class MyAction {
protected:
	float m_timer = 0;
	float m_duration;
	friend class ActionRunner;
public:
	virtual ~MyAction(){}
	virtual void run(float a)=0;
};

class ActionRunner {
	List<MyAction *>m_actions;
	static ActionRunner*s_instance;
public:
	static void cleanUp();
	static ActionRunner*getInstance();
	void addAction(MyAction *action) { m_actions.push_back(action); }
	void update(float deltaTime);
};


class MoveToTarget :public MyAction {
	cocos2d::Vec2 m_target;
	cocos2d::Vec2 m_oldPos;
	cocos2d::Node*m_pNode;
public:
	static MyAction * create(float duration, const cocos2d::Vec2&target, cocos2d::Node*node);
	void run(float a)override;
};

class RotateByAmount:public MyAction {
	float m_amount;
	float m_oldAngle;
	cocos2d::Node*m_pNode;
	std::function<void()>m_callback;
public:
	~RotateByAmount()override;
	static MyAction * create(float duration, const float&amount, cocos2d::Node*node, std::function<void()>callback);
	void run(float a)override;
};