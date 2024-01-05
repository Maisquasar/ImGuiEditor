#include "pch.h"

class Object;
class Hierarchy
{
public:
	Hierarchy() = default;

	void Draw();


	void AddObject(std::shared_ptr<Object> object);


private:

	friend class Canvas;
	std::vector<std::shared_ptr<Object>> m_objects;
};