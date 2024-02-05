#include "pch.h"
#include "Application.h"

#include <filesystem>

#include "Editor.h"
#include "ImageLoader.h"

void Application::Initialize()
{
	// Initialize GLFW
	if (!glfwInit())
		return;

	// Set OpenGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
	m_window = glfwCreateWindow(1600, 900, "ImGuiEditor", NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		return;
	}

	GLFWimage images[1];
	images[0].pixels = ImageLoader::Load("icons/ImGuiEditorLogo.png", &images[0].width, &images[0].height, nullptr, 4);
	glfwSetWindowIcon(m_window, 1, images);
	ImageLoader::ImageFree(images[0].pixels);

	if (!std::filesystem::exists("Saves"))
		std::filesystem::create_directory("Saves");

	// Make the window's context current
	glfwMakeContextCurrent(m_window);

	// Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
}

void Application::Update()
{
	Editor* editor = Editor::Get();
	editor->m_app = this;
	editor->Initialize();
	while (!glfwWindowShouldClose(m_window)) {
		// Poll and handle events (inputs, window resize, etc.)
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Rendering ImGui demo window (just for demonstration)
		editor->Draw();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = m_window;
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		// Swap front and back buffers
		glfwSwapBuffers(m_window);
	}
}

void Application::Destroy() const
{
	Editor::Get()->Destroy();
	Editor::DestroyInstance();
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Application::SetClipboardText(const char* text) const
{
	glfwSetClipboardString(m_window, text);
}

