#include "Object/TabBar.h"

#include "Canvas.h"
#include "Editor.h"
#include "Inspector.h"

void TabBar::PostDraw()
{
	static Canvas* canvas = Editor::Get()->GetCanvas();
	static Inspector* inspector = Editor::Get()->GetInspector();

	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		inspector->SetSelected(this);
	if (ImGui::IsWindowHovered(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(this);
	else if (canvas->GetHoveredObject() == this && !ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(nullptr);
}

bool TabBar::Begin()
{
	return ImGui::BeginTabBar(p_name.c_str());
}

void TabBar::End()
{
	ImGui::EndTabBar();

	if (p_sameLine)
		ImGui::SameLine();
}

void TabBar::Serialize(std::string& content) const
{
	content += "if (ImGui::BeginTabBar(\"" + p_name + "\"))\n{\n";
	SerializeChildren(content);
	content += "ImGui::EndTabBar();\n}\n";
}

void TabBar::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
}

void TabBar::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
}
