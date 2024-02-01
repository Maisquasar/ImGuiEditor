#include <GLFW/glfw3.h>

class Application
{
public:
	Application() = default;
	~Application() = default;

	void Initialize();
	void Update();
	void Destroy() const;

	void SetClipboardText(const char* text) const;
private:
	GLFWwindow* m_window = nullptr;
};