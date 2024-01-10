#pragma once
#include "pch.h"
#include "Object/IObject.h"

class ObjectWindow
{
public:
	ObjectWindow() = default;

	void Initialize();
	
	void Draw() const;

	const std::vector<std::shared_ptr<Object>>& GetAvailableObjects() const { return m_availableObjects; }
private:
	std::vector<std::shared_ptr<Object>> m_availableObjects;

};