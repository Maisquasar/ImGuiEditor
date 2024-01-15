#include "Object/Selectable.h"

void Selectable::Initialize()
{

}

void Selectable::Draw()
{
	ImGui::Selectable(p_name.c_str(), &m_selected, m_flags, p_size);
}

void Selectable::DisplayOnInspector()
{
	ImGui::Checkbox("Selected", &m_selected);

	ImGui::SeparatorText("Flags");
	ImGui::CheckboxFlags("Allow Item Overlap", &m_flags, ImGuiSelectableFlags_AllowItemOverlap);
	ImGui::CheckboxFlags("Select On Click", &m_flags, ImGuiSelectableFlags_SelectOnClick);
	ImGui::CheckboxFlags("Select On Release", &m_flags, ImGuiSelectableFlags_SelectOnRelease);
	ImGui::CheckboxFlags("Disabled", &m_flags, ImGuiSelectableFlags_Disabled);
	ImGui::CheckboxFlags("Span All Columns", &m_flags, ImGuiSelectableFlags_SpanAllColumns);

	Object::DisplayOnInspector();
}

void Selectable::Serialize(std::string& content) const
{
	content += "ImGui::Selectable(\"" + p_name + "\", " + std::to_string(m_selected) + ", " + std::to_string(m_flags) + ", ImVec2(" + std::to_string(p_size.x) + ", " + std::to_string(p_size.y) + "));\n";
	SerializeChildren(content);
}

void Selectable::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
	serializer << Pair::KEY << "Selected" << Pair::VALUE << m_selected;
	serializer << Pair::KEY << "Flags" << Pair::VALUE << (int)m_flags;
}

void Selectable::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
	m_selected = parser["Selected"].As<bool>();
	m_flags = parser["Flags"].As<int>();
}

