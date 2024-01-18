#include "Object/MainMenuBar.h"

#include "Canvas.h"
#include "Editor.h"
#include "Inspector.h"

void MainMenuBar::Initialize()
{
	AddStyleColor("Menu Bar Background", ImGuiCol_MenuBarBg);
}

bool MainMenuBar::Begin()
{
	bool begin = ImGui::BeginMainMenuBar();

	return begin;
}

void MainMenuBar::End()
{
	ImGui::EndMainMenuBar();

	if (p_sameLine)
		ImGui::SameLine();
}

void MainMenuBar::Serialize(std::string& content) const
{
	content += "if (ImGui::BeginMainMenuBar())\n{\n";
	SerializeChildren(content);
	content += "ImGui::EndMainMenuBar();\n}\n";
}

void MainMenuBar::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
}

void MainMenuBar::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
}
