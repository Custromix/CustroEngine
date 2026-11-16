#pragma once

class GameObject;

class Component
{
	
public:
	Component();
	virtual ~Component();

	GameObject* Owner() const { return _Owner; }
	
	virtual void SetOwner(GameObject* owner) { _Owner = owner; }
	
	bool IsActive() const;
	virtual void SetActive(const bool NewActive) { isActive = NewActive; }
	virtual void OnEnable() {}
	virtual void OnDisable() {}
	
protected:
	GameObject* _Owner;
	
private:
	bool isActive = true;
};
