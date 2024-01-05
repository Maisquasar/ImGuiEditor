#include "pch.h"

class Object;
class Canvas
{
public:
	Canvas() = default;

	void Initialize();

	void Draw() const;
	void Update();
	void DisplayObject(std::shared_ptr<Object> object) const;

	bool IsStatic() const { return m_isStatic; }
	void SetStatic(const bool val) { m_isStatic = val; }

	Object* GetHoveredObject() const { return m_hoveredObject; }
	void SetHoveredObject(Object* val) { m_hoveredObject = val; }
private:
	std::vector<std::shared_ptr<Object>>* m_objects;

	Object* m_hoveredObject = nullptr;

	bool m_isStatic = false;
};