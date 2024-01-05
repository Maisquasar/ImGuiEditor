#include "pch.h"

class Editor
{
public:
	Editor() = default;

	void Initialize();
	void Draw();
	void DrawMainDock();
	void Destroy() const;

	static Editor* Get() {
		if (!m_instance)
			m_instance = new Editor();
		return m_instance;
	}

	class Hierarchy* GetHierarchy() const { return m_hierarchy; }
	class Inspector* GetInspector() const { return m_inspector; }
	class Canvas* GetCanvas() const { return m_canvas; }
	class ObjectWindow* GetObjectWindow() const { return m_objectWindow; }
private:
	static Editor* m_instance;

	class Hierarchy* m_hierarchy;
	class Inspector* m_inspector;
	class Canvas* m_canvas;
	class ObjectWindow* m_objectWindow;
};