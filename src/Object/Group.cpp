#include "Object/Group.h"

#include "Editor.h"
#include "Canvas.h"
#include "Inspector.h"

void Group::PostDraw()
{
	static Canvas* canvas = Editor::Get()->GetCanvas();
	static Inspector* inspector = Editor::Get()->GetInspector();

	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		inspector->SetSelected(this);
	if (ImGui::IsWindowHovered(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(this);
	else if (canvas->GetHoveredObject() == this && !ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(nullptr);

	if (p_selected)
	{
		Vec2f min = ImGui::GetItemRectMin();
		Vec2f max = ImGui::GetItemRectMax();
		ImGui::GetWindowDrawList()->AddRect(min, max, IM_COL32(255, 255, 0, 255));
	}

}

void Group::Begin()
{
	ImGui::BeginGroup();
}

void Group::End()
{
	ImGui::EndGroup();

	if (p_sameLine)
		ImGui::SameLine();
}

void Group::Serialize(std::string& content) const
{

}
