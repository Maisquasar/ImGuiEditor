#include "Object/Item/Separator.h"

void Separator::Initialize()
{
	AddStyleColor("Text Color", ImGuiCol_Text);
	AddStyleColor("Text Disabled Color", ImGuiCol_TextDisabled);
	AddStyleColor("Separator Color", ImGuiCol_Separator);
	AddStyleColor("Separator Hovered Color", ImGuiCol_SeparatorHovered);
	AddStyleColor("Separator Active Color", ImGuiCol_SeparatorActive);
	AddStyleColor("Border Color", ImGuiCol_Border);
	AddStyleColor("Border Shadow", ImGuiCol_BorderShadow);

	AddStyleVar("Border size", ImGui::GetStyle().SeparatorTextBorderSize, ImGuiStyleVar_SeparatorTextBorderSize);
	AddStyleVar("Text padding", ImGui::GetStyle().SeparatorTextPadding, ImGuiStyleVar_SeparatorTextPadding);
	AddStyleVar("Text align", ImGui::GetStyle().SeparatorTextAlign, ImGuiStyleVar_SeparatorTextAlign);
}

void Separator::Draw()
{
	ImGui::SeparatorText(m_text.c_str());
}

void Separator::DisplayOnInspector()
{
	ImGui::InputText("Text", &m_text);
	Object::DisplayOnInspector();
}

void Separator::Serialize(std::string& content) const
{
	content += "ImGui::SeparatorText(\"" + m_text + "\");\n";

	SerializeChildren(content);
}

void Separator::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::Key << "Text" << Pair::Value << m_text;
}

void Separator::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_text = parser["Text"].As<std::string>();
}