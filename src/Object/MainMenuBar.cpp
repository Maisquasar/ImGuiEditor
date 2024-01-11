#include "Object/MainMenuBar.h"

#include "Canvas.h"
#include "Editor.h"
#include "Inspector.h"

void MainMenuBar::PostDraw()
{
}

bool MainMenuBar::Begin()
{
	return ImGui::BeginMainMenuBar();
}

void MainMenuBar::End()
{
	ImGui::EndMainMenuBar();

	if (!Editor::Get()->IsUserMode()) {
		static Canvas* canvas = Editor::Get()->GetCanvas();
		static Inspector* inspector = Editor::Get()->GetInspector();

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			inspector->SetSelected(this);
		if (ImGui::IsItemHovered(ImGuiMouseButton_Left))
			canvas->SetHoveredObject(this);
		else if (canvas->GetHoveredObject() == this && !ImGui::IsMouseReleased(ImGuiMouseButton_Left))
			canvas->SetHoveredObject(nullptr);
	}

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
