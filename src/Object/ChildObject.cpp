#include "pch.h"
#include "Object/ChildObject.h"

#include "Editor.h"
#include "Inspector.h"
#include "Canvas.h"

void ChildObject::Initialize()
{
	const auto style = ImGui::GetStyle();
	AddStyleVar("Window Padding", style.WindowPadding, ImGuiStyleVar_WindowPadding);
	AddStyleVar("Child Border Size", style.ChildBorderSize, ImGuiStyleVar_ChildBorderSize);
	AddStyleVar("Child Rounding", style.ChildRounding, ImGuiStyleVar_ChildRounding);
	AddStyleVar("Scrollbar Rounding", style.ScrollbarRounding, ImGuiStyleVar_ScrollbarRounding);

	AddStyleColor("Border", ImGuiCol_Border);
}

bool ChildObject::Begin()
{
	const bool value = ImGui::BeginChild(p_name.c_str(), p_size, m_hasBorder);

	static Canvas* canvas = Editor::Get()->GetCanvas();
	static Inspector* inspector = Editor::Get()->GetInspector();

	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		inspector->SetSelected(this);
	if (ImGui::IsWindowHovered(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(this);
	else if (canvas->GetHoveredObject() == this && !ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(nullptr);

	return value;
}


void ChildObject::End()
{
	ImGui::EndChild();
}

void ChildObject::PostEnd()
{
	if (p_sameLine)
		ImGui::SameLine();
}

void ChildObject::DisplayOnInspector()
{
	ImGui::Checkbox("Has border", &m_hasBorder);
	Object::DisplayOnInspector();
}

std::string ChildObject::GetTypeName() const
{
	return "ChildObject";
}

void ChildObject::Serialize(std::string& content) const
{
	const auto size = p_size.ToVec2i();
	content += "ImGui::BeginChild(" + p_name + ", ImVec2(" + std::to_string(size.x) + ", " + std::to_string(size.y) + "), " + std::to_string(m_hasBorder) + ");\n";
	SerializeChildren(content);
	content += "ImGui::EndChild();\n";
}

void ChildObject::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::KEY << "HasBorder" << Pair::VALUE << m_hasBorder;
}

void ChildObject::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_hasBorder = parser["HasBorder"].As<bool>();
}
