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

	if (m_hasBorder)
		ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax()
			, ImGui::ColorConvertFloat4ToU32(m_borderColor), m_borderRounding
			, ImDrawFlags_None, m_borderWidth);

	p_size = ImGui::GetItemRectSize();

	if (p_sameLine)
		ImGui::SameLine();
}

void Group::DisplayOnInspector()
{
	Object::DisplayOnInspector();
	ImGui::Checkbox("Has Border", &m_hasBorder);
	ImGui::BeginDisabled(!m_hasBorder);
	ImGui::ColorEdit4("Border Color", &m_borderColor.x, ImGuiColorEditFlags_NoInputs);
	ImGui::DragFloat("Border Rounding", &m_borderRounding);
	ImGui::DragFloat("Border Width", &m_borderWidth);
	ImGui::EndDisabled();
}

void Group::Serialize(std::string& content) const
{

}
