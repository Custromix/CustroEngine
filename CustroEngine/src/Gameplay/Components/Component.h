#pragma once

class GameObject;

class Component
{
	
public:
	Component();
	virtual ~Component();

	GameObject* Owner() const { return _Owner; }
	
	virtual void SetOwner(GameObject* owner) { _Owner = owner; }
	
protected:
	GameObject* _Owner;
};
