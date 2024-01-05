#include "pch.h"

class Object;
class Inspector
{
public:
	Inspector() = default;

	void Draw();

	void SetSelected(Object* object);
	void SetHovered(Object* object);

	void DrawSelected() const;

	Object* GetHoveredObject() const { return m_hoveredObject; }
private:
	Object* m_selectedObject;
	Object* m_hoveredObject;

};
