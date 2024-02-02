#include "Object/Shape/Rect.h"

#include "Editor.h"

void Rect::Initialize()
{
	ShapeObject::Initialize();
	p_size = Vec2f(100, 100);
	p_position = Vec2f(50, 50);
}

void Rect::Draw()
{
	if (m_filled)
		ImGui::GetWindowDrawList()->AddRectFilled(GetMin(), GetMax(), ImGui::ColorConvertFloat4ToU32(m_color), m_rounding, p_flags);
	else
		ImGui::GetWindowDrawList()->AddRect(GetMin(), GetMax(), ImGui::ColorConvertFloat4ToU32(m_color), m_rounding, p_flags, m_thickness);
	}

void Rect::DisplayOnInspector()
{
	ImGui::ColorEdit4("Color", &m_color.x, ImGuiColorEditFlags_NoInputs);

	ImGui::Checkbox("Filled", &m_filled);
	ImGui::DragFloat("Rounding", &m_rounding);
	ImGui::BeginDisabled(m_filled);
	ImGui::DragFloat("Thickness", &m_thickness);
	ImGui::EndDisabled();

	ShapeObject::DisplayOnInspector();
}

std::string Rect::GetTypeName() const
{
	return "Rect";
}

void Rect::Serialize(std::string& content) const
{
	//ImGui::GetWindowDrawList()->AddRectFilled(GetMin(), GetMax(), ImGui::ColorConvertFloat4ToU32(m_color));
	if (m_filled)
		content += "ImGui::GetWindowDrawList()->AddRectFilled(";
	else
		content += "ImGui::GetWindowDrawList()->AddRect(";
	content += "ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMin().x";

	const float minSizeX = p_position.x - p_size.x / 2;
	if (minSizeX != 0.0f)
	{
		content += " + " + std::to_string(minSizeX);
	}
	content += ", \n";
	content += "\tImGui::GetWindowPos().y + ImGui::GetWindowContentRegionMin().y";
	const float minSizeY = p_position.y - p_size.y / 2;
	if (minSizeY != 0.0f)
	{
		content += " + " + std::to_string(minSizeY);
	}
	content += "), \n";

	content += "\tImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMin().x";
	const float maxSizeX = p_position.x + p_size.x / 2;
	if (maxSizeX != 0.0f)
	{
		content += " + " + std::to_string(maxSizeX);
	}
	content += ", \n";
	content += "\tImGui::GetWindowPos().y + ImGui::GetWindowContentRegionMin().y";
	const float maxSizeY = p_position.y + p_size.y / 2;
	if (maxSizeY != 0.0f)
	{
		content += " + " + std::to_string(maxSizeY);
	}
	content += "), \n";


	content += '\t' + std::to_string(ImGui::ColorConvertFloat4ToU32(m_color))
		+ ", " + std::to_string(m_rounding) + ", " + std::to_string(p_flags);
	if (!m_filled)
	{
		content += ", " + std::to_string(m_thickness);
	}
	content += ");\n";

	SerializeChildren(content);
}

void Rect::Serialize(Serializer& serializer) const
{
	ShapeObject::Serialize(serializer);

	serializer << Pair::Key << "Color" << Pair::Value << m_color;
	serializer << Pair::Key << "Filled" << Pair::Value << m_filled;
	serializer << Pair::Key << "Rounding" << Pair::Value << m_rounding;
}

void Rect::Deserialize(Parser& parser)
{
	ShapeObject::Deserialize(parser);

	m_color = parser["Color"].As<Vec4f>();
	m_filled = parser["Filled"].As<bool>();
	m_rounding = parser["Rounding"].As<float>();
}
