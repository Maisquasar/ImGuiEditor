#pragma once
#include "pch.h"

class Object;
class Hierarchy
{
public:
	Hierarchy() = default;

	void Initialize();

	void Draw();

	void Serialize() const;

	void AddObject(std::shared_ptr<Object> object);

	void RemoveObject(const Object* object);

	void AddObjectToRoot(std::shared_ptr<Object> object);

	std::shared_ptr<Object> GetWithIndex(size_t index);
	std::weak_ptr<Object> GetWithPtr(const Object* object);

	void DisplayOnHierarchy(std::shared_ptr<Object> object, size_t& index);

	std::shared_ptr<Object> GetRoot() const { return m_root; }
private:

	friend class Canvas;
	std::vector<std::shared_ptr<Object>> m_objects;
	std::shared_ptr<Object> m_root;
};