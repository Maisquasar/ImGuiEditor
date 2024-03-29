#pragma once
#include <vector>

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

	static void DestroyInstance() {
		if (m_instance)
			delete m_instance;
		m_instance = nullptr;
	}

	class Application* GetApplication() const { return m_app; }
	class Hierarchy* GetHierarchy() const { return m_hierarchy; }
	class Inspector* GetInspector() const { return m_inspector; }
	class Canvas* GetCanvas() const { return m_canvas; }
	class ObjectWindow* GetObjectWindow() const { return m_objectWindow; }
	static bool IsUserMode() { return m_instance->m_userMode; }
private:
	friend class Application;
	class Application* m_app;
	static Editor* m_instance;

	class Hierarchy* m_hierarchy;
	class Inspector* m_inspector;
	class Canvas* m_canvas;
	class ObjectWindow* m_objectWindow;

	bool m_userMode = false;
};

struct Filter
{
	std::string name;
	// ex : "Text file"
	std::string spec;
	// ex : "txt"
};

std::string OpenFileExplorer(const std::vector<Filter>& filters);
std::string SaveFileExplorer(const std::vector<Filter>& filters);