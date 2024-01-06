#include "pch.h"
#include "Object/ChildObject.h"

#include "Editor.h"
#include "Inspector.h"
#include "Canvas.h"

void ChildObject::Begin()
{
	ImGui::BeginChild(p_name.c_str(), p_size, m_hasBorder);
	static Canvas* canvas = Editor::Get()->GetCanvas();
	static Inspector* inspector = Editor::Get()->GetInspector();

	if (ImGui::IsWindowHovered(ImGuiMouseButton_Left) && !inspector->HasSelected())
		inspector->SetSelected(this);
	if (ImGui::IsWindowHovered(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(this);
	else if (canvas->GetHoveredObject() == this && !ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(nullptr);
}

void ChildObject::End()
{
	ImGui::EndChild();
}

std::string ChildObject::GetTypeName() const
{
	return "ChildObject";
}

void ChildObject::Serialize(std::string& content) const
{
	const auto size = p_size.ToVec2i();
	EndSerializeStyle(content);
	BeginSerializeStyle(content);
	content += "ImGui::BeginChild(" + p_name + ", ImVec2(" + std::to_string(size.x) + ", " + std::to_string(size.y) + "), " + std::to_string(m_hasBorder) + ");\n";
	SerializeChildren(content);
	content += "ImGui::EndChild();\n";
	EndSerializeStyle(content);
}
