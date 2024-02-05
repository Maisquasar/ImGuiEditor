#include "pch.h"

class Object;
class Canvas
{
public:
	Canvas() = default;

	void Initialize();

	void Draw() const;
	void Update() const;
	void DisplayObject(std::shared_ptr<Object> object, size_t& index) const;

	bool IsDynamic() const { return m_isDynamic; }
	void SetDynamic(const bool val) { m_isDynamic = val; }

	Object* GetHoveredObject() const { return m_hoveredObject; }
	void SetHoveredObject(Object* val) { m_hoveredObject = val; }
private:

	Object* m_hoveredObject = nullptr;

	bool m_isDynamic = true;
};