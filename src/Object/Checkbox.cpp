#include "Object/Checkbox.h"

void Checkbox::Initialize()
{
	AddStyleColor("Text Color", ImGuiCol_Text);
	AddStyleColor("Text Disabled Color", ImGuiCol_TextDisabled);
	AddStyleColor("Check Mark Color", ImGuiCol_CheckMark);
	AddStyleColor("Border Color", ImGuiCol_Border);
	AddStyleColor("Border Shadow", ImGuiCol_BorderShadow);

	AddStyleVar("Frame rounding", ImGui::GetStyle().FrameRounding, ImGuiStyleVar_FrameRounding);
	AddStyleVar("Frame padding", ImGui::GetStyle().FramePadding, ImGuiStyleVar_FramePadding);
	AddStyleVar("Frame border size", ImGui::GetStyle().FrameBorderSize, ImGuiStyleVar_FrameBorderSize);
}

void Checkbox::Draw()
{
	ImGui::Checkbox(p_name.c_str(), &m_value);
}

void Checkbox::DisplayOnInspector()
{
	ImGui::Checkbox("Value", &m_value);
	Object::DisplayOnInspector();
}

void Checkbox::Serialize(std::string& content) const
{
	std::string variableName = "variable" + std::to_string(p_uuid);
	content += "bool " + variableName + " = " + std::to_string(m_value) + "\n";
	content += "ImGui::Checkbox(\"" + p_name + "\", &" + variableName + ");\n";
	SerializeChildren(content);
}

void Checkbox::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::KEY << "Value" << Pair::VALUE << m_value;
}

void Checkbox::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_value = parser["Value"].As<bool>();
}
