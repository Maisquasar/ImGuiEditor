#include "Object/Item/Button.h"

#include "Editor.h"
#include "Inspector.h"
#include "Canvas.h"

void Button::Initialize()
{
	AddStyleColor("Button Color", ImGuiCol_Button);
	AddStyleColor("Button Hovered Color", ImGuiCol_ButtonHovered);
	AddStyleColor("Button Active Color", ImGuiCol_ButtonActive);
	AddStyleColor("Text Color", ImGuiCol_Text);
	AddStyleColor("Border Color", ImGuiCol_Border);
	AddStyleColor("Border Shadow", ImGuiCol_BorderShadow);

	AddStyleVar("Frame Rounding", ImGui::GetStyle().FrameRounding, ImGuiStyleVar_FrameRounding);
	AddStyleVar("Frame Padding", ImGui::GetStyle().FramePadding, ImGuiStyleVar_FramePadding);
	AddStyleVar("Frame Border Size", ImGui::GetStyle().FrameBorderSize, ImGuiStyleVar_FrameBorderSize);
	AddStyleVar("Button Text Align", ImGui::GetStyle().ButtonTextAlign, ImGuiStyleVar_ButtonTextAlign);

	m_text = "Button";
}

void Button::Draw()
{
	if (m_arrowButton)
	{
		if (p_size.x != 0.f || p_size.y != 0.f)
			ImGui::ArrowButtonEx(p_name.c_str(), m_arrowDir, p_size);
		else
			ImGui::ArrowButton(p_name.c_str(), m_arrowDir);
	}
	else {
		if (!m_small)
			ImGui::Button(m_text.c_str(), p_size);
		else
			ImGui::SmallButton(m_text.c_str());
	}
}

static const char* ImGuiDirEnumToString()
{
	return "Left\0Right\0Up\0Down\0";
}

void Button::DisplayOnInspector()
{
	ImGui::Checkbox("Arrow Button", &m_arrowButton);
	if (m_arrowButton)
	{
		int arrowDir = (int)m_arrowDir;
		ImGui::Combo("Arrow Direction", &arrowDir, ImGuiDirEnumToString());
		m_arrowDir = (ImGuiDir_)arrowDir;
	}
	else
	{
		ImGui::InputText("Text", &m_text);
		ImGui::Checkbox("Small", &m_small);
	}
	Object::DisplayOnInspector();
}

void Button::Serialize(std::string& content) const
{
	if (m_arrowButton)
	{
		if (p_size.x != 0.f || p_size.y != 0.f)
			content += "ImGui::ArrowButtonEx(\"" + p_name + "\", " + std::to_string((int)m_arrowDir) + ", ImVec2(" + std::to_string(p_size.x) + ", " + std::to_string(p_size.y) + "));\n";
		else
			content += "ImGui::ArrowButton(\"" + p_name + "\", " + std::to_string((int)m_arrowDir) + ");\n";
	}
	else {
		if (!m_small) {
			if (p_size.x == 0.f && p_size.y == 0.f)
				content += "ImGui::Button(\"" + m_text + "\");\n";
			else
				content += "ImGui::Button(\"" + m_text + "\", ImVec2(" + std::to_string(p_size.x) + ", " + std::to_string(p_size.y) + "));\n";
		}
		else
			content += "ImGui::SmallButton(\"" + m_text + "\");\n";
	}
	SerializeChildren(content);
}

void Button::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
	serializer << Pair::Key << "Text" << Pair::Value << m_text;
	serializer << Pair::Key << "Small" << Pair::Value << m_small;
	serializer << Pair::Key << "Arrow Button" << Pair::Value << m_arrowButton;
	serializer << Pair::Key << "Arrow Direction" << Pair::Value << (int)m_arrowDir;
}

void Button::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
	m_text = parser["Text"].As<std::string>();
	m_small = parser["Small"].As<bool>();
	m_arrowButton = parser["Arrow Button"].As<bool>();
	m_arrowDir = (ImGuiDir_)parser["Arrow Direction"].As<int>();
}
