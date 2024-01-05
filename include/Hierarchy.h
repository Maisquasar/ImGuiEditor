#pragma once
#include "pch.h"

class Object;
class Hierarchy
{
public:
	Hierarchy() = default;

	void Initialize();

	void Draw();

	void AddObject(std::shared_ptr<Object> object);

	void AddObjectToRoot(std::shared_ptr<Object> object);

	std::shared_ptr<Object> GetWithIndex(size_t index);

	void DisplayOnHierarchy(std::shared_ptr<Object> object, size_t& index);

	std::shared_ptr<Object> GetRoot() const { return m_root; }
private:

	friend class Canvas;
	std::vector<std::shared_ptr<Object>> m_objects;
	std::shared_ptr<Object> m_root;
};