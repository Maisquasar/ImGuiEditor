#include "Object/Scope/Tree.h"
#include "Editor.h"

void Tree::Initialize()
{

}

bool Tree::Begin()
{
	bool value = ImGui::TreeNodeEx(p_name.c_str(), m_flags);

	if (p_sameLine)
		ImGui::SameLine();

	if (!Editor::IsUserMode()) {
		SelectUpdate(ImGui::IsItemClicked(ImGuiMouseButton_Left), ImGui::IsItemHovered(ImGuiMouseButton_Left));

		if (p_selected)
			ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255));
	}
	return value;
}

void Tree::End()
{
	ImGui::TreePop();
}

void Tree::DisplayOnInspector()
{
	ImGui::SeparatorText("Flags");
	ImGui::CheckboxFlags("Allow item overlap", &m_flags, ImGuiTreeNodeFlags_AllowItemOverlap);
	ImGui::CheckboxFlags("Open on arrow", &m_flags, ImGuiTreeNodeFlags_OpenOnArrow);
	ImGui::CheckboxFlags("Open on double click", &m_flags, ImGuiTreeNodeFlags_OpenOnDoubleClick);
	ImGui::CheckboxFlags("Bullet", &m_flags, ImGuiTreeNodeFlags_Bullet);
	ImGui::CheckboxFlags("Frame padding", &m_flags, ImGuiTreeNodeFlags_FramePadding);
	ImGui::CheckboxFlags("Span full width", &m_flags, ImGuiTreeNodeFlags_SpanFullWidth);
	ImGui::CheckboxFlags("Span Available Width", &m_flags, ImGuiTreeNodeFlags_SpanAvailWidth);
	ImGui::CheckboxFlags("Default open", &m_flags, ImGuiTreeNodeFlags_DefaultOpen);
	ImGui::CheckboxFlags("Selected", &m_flags, ImGuiTreeNodeFlags_Selected);
	ImGui::CheckboxFlags("Framed", &m_flags, ImGuiTreeNodeFlags_Framed);
	ImGui::CheckboxFlags("No Tree Push On Open", &m_flags, ImGuiTreeNodeFlags_NoTreePushOnOpen);
	ImGui::CheckboxFlags("No Auto Open On Log", &m_flags, ImGuiTreeNodeFlags_NoAutoOpenOnLog);
	ImGui::CheckboxFlags("Leaf", &m_flags, ImGuiTreeNodeFlags_Leaf);

	Object::DisplayOnInspector();
}

void Tree::Serialize(std::string& content) const
{
	content += "if (ImGui::TreeNodeEx(\"" + p_name + "\", " + std::to_string(m_flags) + "))\n{\n";
	if (p_sameLine)
		content += "ImGui::SameLine();\n";
	SerializeChildren(content);
	content += "ImGui::TreePop();\n}\n";
}

void Tree::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
	serializer << Pair::Key << "Flags" << Pair::Value << (int)m_flags;
}

void Tree::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
	m_flags = parser["Flags"].As<int>();
}

void Tree::InternalSerialize(std::string& content) const
{
	// Use Object base internal Serialize for sameline;
	Object::InternalSerialize(content);
}
