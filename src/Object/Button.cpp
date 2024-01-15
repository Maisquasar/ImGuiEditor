#include "Object/Button.h"

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
	if (!m_small)
		ImGui::Button(m_text.c_str(), p_size);
	else
		ImGui::SmallButton(m_text.c_str());
}

void Button::DisplayOnInspector()
{
	ImGui::InputText("Text", &m_text);
	ImGui::Checkbox("Small", &m_small);
	Object::DisplayOnInspector();
}

void Button::Serialize(std::string& content) const
{
	content += "ImGui::Button(\"" + m_text + "\");\n";
	SerializeChildren(content);
}

void Button::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
	serializer << Pair::KEY << "Text" << Pair::VALUE << m_text;
	serializer << Pair::KEY << "Small" << Pair::VALUE << m_small;
}

void Button::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
	m_text = parser["Text"].As<std::string>();
	m_small = parser["Small"].As<bool>();
}
