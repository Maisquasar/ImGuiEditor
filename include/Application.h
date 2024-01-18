#include <GLFW/glfw3.h>

class Application
{
public:
	Application() = default;
	~Application() = default;

	void Initialize();
	void Update();
	void Destroy();

	void SetClipboardText(const char* text);
private:
	GLFWwindow* m_window = nullptr;
};