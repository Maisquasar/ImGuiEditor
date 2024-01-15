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
	ImGui::GetWindowDrawList()->AddRectFilled(GetMin(), GetMax(), ImGui::ColorConvertFloat4ToU32(m_color));
}

void Rect::PostDraw()
{
	static Canvas* canvas = Editor::Get()->GetCanvas();
	static Inspector* inspector = Editor::Get()->GetInspector();

	if (!Editor::Get()->IsUserMode()) {

		const bool hovered = ImGui::IsMouseHoveringRect(GetMin(), GetMax());
		SelectUpdate(hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left), hovered);

		if (p_selected)
			ImGui::GetWindowDrawList()->AddRect(GetMin(), GetMax(), IM_COL32(255, 255, 0, 255));
	}

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
	//ImGui::GetWindowDrawList()->AddRectFilled(GetMin(), GetMax(), ImGui::ColorConvertFloat4ToU32(m_color));
	content += "ImGui::GetWindowDrawList()->AddRectFilled((ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMin().x";

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


	content += '\t' + std::to_string(ImGui::ColorConvertFloat4ToU32(m_color)) + ");\n";

	SerializeChildren(content);
}

void Rect::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::KEY << "Color" << Pair::VALUE << m_color;
}

void Rect::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_color = parser["Color"].As<Vec4f>();
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
