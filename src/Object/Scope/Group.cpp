#include "Object/Scope/Group.h"

#include "Editor.h"

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

	if (!Editor::Get()->IsUserMode()) {
		SelectUpdate(ImGui::IsItemClicked(ImGuiMouseButton_Left), ImGui::IsItemHovered());

		if (p_selected)
		{
			Vec2f min = ImGui::GetItemRectMin();
			Vec2f max = ImGui::GetItemRectMax();

			ImGui::GetWindowDrawList()->AddRect(min, max, IM_COL32(255, 255, 0, 255));
		}
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
	content += "ImGui::BeginGroup();\n{\n";
	SerializeChildren(content);
	content += "}\nImGui::EndGroup();\n";
	if (m_hasBorder)
	{
		content += "ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax()\n";
		content += "\t, " + std::to_string(ImGui::ColorConvertFloat4ToU32(m_borderColor)) + ", " + std::to_string(m_borderRounding) + "\n";
		content += "\t, ImDrawFlags_None, " + std::to_string(m_borderWidth) + ");\n";
	}
}

void Group::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::Key << "Has Border" << Pair::Value << m_hasBorder;
	serializer << Pair::Key << "Border Color" << Pair::Value << m_borderColor;
	serializer << Pair::Key << "Border Rounding" << Pair::Value << m_borderRounding;
	serializer << Pair::Key << "Border Width" << Pair::Value << m_borderWidth;
}

void Group::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_hasBorder = parser["Has Border"].As<bool>();
	m_borderColor = parser["Border Color"].As<Vec4f>();
	m_borderRounding = parser["Border Rounding"].As<float>();
	m_borderWidth = parser["Border Width"].As<float>();
}
