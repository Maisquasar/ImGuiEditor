#include "Object/TabBar.h"

#include "Canvas.h"
#include "Editor.h"
#include "Inspector.h"

void TabBar::Initialize()
{
	AddStyleColor("Tab", ImGuiCol_Tab);
	AddStyleColor("Tab Active", ImGuiCol_TabActive);
	AddStyleColor("Tab Hovered", ImGuiCol_TabHovered);
	AddStyleColor("Tab Unfocused", ImGuiCol_TabUnfocused);
	AddStyleColor("Tab Unfocused Active", ImGuiCol_TabUnfocusedActive);

	AddStyleVar("Tab Rounding", ImGui::GetStyle().TabRounding, ImGuiStyleVar_TabRounding);
}

bool TabBar::Begin()
{
	return ImGui::BeginTabBar(p_name.c_str());
}

void TabBar::End()
{
	ImGui::EndTabBar();

	if (p_sameLine)
		ImGui::SameLine();
}

void TabBar::DisplayOnInspector()
{
	Object::DisplayOnInspector();
}

void TabBar::Serialize(std::string& content) const
{
	content += "if (ImGui::BeginTabBar(\"" + p_name + "\"))\n{\n";
	SerializeChildren(content);
	content += "ImGui::EndTabBar();\n}\n";
}

void TabBar::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
}

void TabBar::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
}
