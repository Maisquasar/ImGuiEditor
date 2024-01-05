#include <GLFW/glfw3.h>

class Application
{
public:
	Application() = default;
	~Application() = default;

	void Initialize();
	void Update();
	void Destroy();
private:
	GLFWwindow* m_window = nullptr;
};