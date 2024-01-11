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
}

bool Group::Begin()
{
	ImGui::BeginGroup();

	return true;
}

void Group::End()
{
	ImGui::EndGroup();

	if (m_hasBorder)
		ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax()
			, ImGui::ColorConvertFloat4ToU32(m_borderColor), m_borderRounding
			, ImDrawFlags_None, m_borderWidth);

	p_size = ImGui::GetItemRectSize();

	if (p_selected)
	{
		Vec2f min = ImGui::GetItemRectMin();
		Vec2f max = ImGui::GetItemRectMax();
		ImGui::GetWindowDrawList()->AddRect(min, max, IM_COL32(255, 255, 0, 255));
	}

	if (p_sameLine)
		ImGui::SameLine();
}

void Group::DisplayOnInspector()
{
	ImGui::Checkbox("Has Border", &m_hasBorder);
	ImGui::BeginDisabled(!m_hasBorder);
	ImGui::ColorEdit4("Border Color", &m_borderColor.x, ImGuiColorEditFlags_NoInputs);
	ImGui::DragFloat("Border Rounding", &m_borderRounding);
	ImGui::DragFloat("Border Width", &m_borderWidth);
	ImGui::EndDisabled();
	Object::DisplayOnInspector();
}

void Group::Serialize(std::string& content) const
{
	const auto size = p_size.ToVec2i();
	content += "ImGui::BeginGroup();\n";
	for (auto& child : p_children)
	{
		child.lock()->InternalSerialize(content);
	}
	content += "ImGui::EndGroup();\n";
	if (m_hasBorder)
	{
		content += "ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax()\n";
		content += "\t, " + std::to_string(ImGui::ColorConvertFloat4ToU32(m_borderColor)) + ", " + std::to_string(m_borderRounding) + "\n";
		content += "\t, ImDrawFlags_None, " + std::to_string(m_borderWidth) + ");\n";
	}
	if (p_sameLine)
		content += "ImGui::SameLine();\n";

}

void Group::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::KEY << "Has Border" << Pair::VALUE << m_hasBorder;
	serializer << Pair::KEY << "Border Color" << Pair::VALUE << m_borderColor;
	serializer << Pair::KEY << "Border Rounding" << Pair::VALUE << m_borderRounding;
	serializer << Pair::KEY << "Border Width" << Pair::VALUE << m_borderWidth;
}

void Group::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_hasBorder = parser["Has Border"].As<bool>();
	m_borderColor = parser["Border Color"].As<Vec4f>();
	m_borderRounding = parser["Border Rounding"].As<float>();
	m_borderWidth = parser["Border Width"].As<float>();
}
