#include "Object/ComboBox.h"
#include "Editor.h"

void ComboBox::Initialize()
{

}

bool ComboBox::Begin()
{
	if (p_size.x != 0.f)
		ImGui::SetNextItemWidth(p_size.x);
	return ImGui::BeginCombo(p_name.c_str(), p_children.empty() ? "" : p_children[0].lock()->GetName().c_str(), m_flags);
}

void ComboBox::End()
{
	ImGui::EndCombo();
}

void ComboBox::PostEnd()
{
	if (!Editor::Get()->IsUserMode()) {
		SelectUpdate(ImGui::IsItemClicked(), ImGui::IsItemHovered());

		if (p_selected)
			ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255));
	}

	if (p_sameLine)
		ImGui::SameLine();
}

void ComboBox::DisplayOnInspector()
{
	ImGui::SeparatorText("Flags");
	ImGui::CheckboxFlags("No Arrow Button", &m_flags, ImGuiComboFlags_NoArrowButton);
	ImGui::CheckboxFlags("No Preview", &m_flags, ImGuiComboFlags_NoPreview);
	ImGui::CheckboxFlags("Height Small", &m_flags, ImGuiComboFlags_HeightSmall);
	ImGui::CheckboxFlags("Height Large", &m_flags, ImGuiComboFlags_HeightLarge);
	ImGui::CheckboxFlags("Height Largest", &m_flags, ImGuiComboFlags_HeightLargest);
	ImGui::CheckboxFlags("Height Regular", &m_flags, ImGuiComboFlags_HeightRegular);
	ImGui::CheckboxFlags("Popup Align Left", &m_flags, ImGuiComboFlags_PopupAlignLeft);

	Object::DisplayOnInspector();
}

void ComboBox::Serialize(std::string& content) const
{
	content += "if (ImGui::BeginCombo(\"" + p_name + "\", \"" + p_children[0].lock()->GetName() + "\"))\n{\n";
	SerializeChildren(content);
	content += "}\nImGui::EndCombo();\n";
}

void ComboBox::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
}

void ComboBox::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
}

