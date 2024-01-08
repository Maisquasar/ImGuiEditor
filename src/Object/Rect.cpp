#include "Object/Rect.h"

#include "Editor.h"
#include "Inspector.h"
#include "Canvas.h"

void Rect::Initialize()
{
	p_size = Vec2f(100, 100);
	p_position = Vec2f(50, 50);
}

void Rect::Draw()
{
	const auto color = m_color * 255.f;	
	ImGui::GetWindowDrawList()->AddRectFilled(GetMin(),GetMax(), IM_COL32(color.x, color.y, color.z, color.w));
}

void Rect::PostDraw()
{
	static Canvas* canvas = Editor::Get()->GetCanvas();
	static Inspector* inspector = Editor::Get()->GetInspector();
	const bool hovered = ImGui::IsMouseHoveringRect(GetMin(), GetMax());
	// MB TODO : add for all object a invisible button or selectable to check if the object is selected or hovered
	if (hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		inspector->SetSelected(this);
	if (hovered)
		canvas->SetHoveredObject(this);
	else if (canvas->GetHoveredObject() == this && !ImGui::IsMouseDown(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(nullptr);

	if (p_selected)
		ImGui::GetWindowDrawList()->AddRect(GetMin(), GetMax(), IM_COL32(255, 255, 0, 255));

	if (p_sameLine)
		ImGui::SameLine();
}

void Rect::DisplayOnInspector()
{
	ImGui::ColorEdit4("Color", &m_color.x, ImGuiColorEditFlags_NoInputs);
}

std::string Rect::GetTypeName() const
{
	return "Rect";
}

void Rect::Serialize(std::string& content) const
{

}

Vec2f Rect::GetMin() const
{
	const Vec2f min = ImGui::GetWindowPos() + ImGui::GetWindowContentRegionMin() + p_position - p_size / 2;
	return min;
}

Vec2f Rect::GetMax() const
{
	const Vec2f max = ImGui::GetWindowPos() + ImGui::GetWindowContentRegionMin() + p_position + p_size / 2;
	return max;
}