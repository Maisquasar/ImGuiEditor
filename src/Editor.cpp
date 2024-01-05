#include "Editor.h"

#include "Hierarchy.h"
#include "Inspector.h"
#include "Canvas.h"
#include "ObjectWindow.h"

Editor* Editor::m_instance;

void Editor::Initialize()
{
	m_hierarchy = new Hierarchy();
	m_inspector = new Inspector();
	m_canvas = new Canvas();
	m_objectWindow = new ObjectWindow();
	m_objectWindow->Initialize();
	m_canvas->Initialize();
}

void Editor::Draw()
{
	DrawMainDock();
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Edit"))
	{
		bool isStatic = m_canvas->IsStatic();
		ImGui::Checkbox("Is Static", &isStatic);
		m_canvas->SetStatic(isStatic);
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	m_canvas->Update();

	m_hierarchy->Draw();
	m_inspector->Draw();
	m_canvas->Draw();
	m_objectWindow->Draw();
}

void Editor::DrawMainDock()
{
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;
	ImGui::GetWindowDockID();

	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // Set window background to red
	ImGui::Begin("DockSpace", nullptr, window_flags);
	ImGui::PopStyleColor();
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	const ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		const ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	ImGui::End();
}

void Editor::Destroy() const
{
	delete m_hierarchy;
	delete m_inspector;
	delete m_canvas;
	delete m_objectWindow;
}

