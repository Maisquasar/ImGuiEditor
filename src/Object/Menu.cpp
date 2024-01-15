#include "Object/Menu.h"

#include "Canvas.h"
#include "Editor.h"
#include "Inspector.h"

void Menu::PostDraw()
{
}

bool Menu::Begin()
{
	ImGui::SetNextWindowSize(p_size);
	return ImGui::BeginMenu(p_name.c_str());
}

void Menu::End()
{
	ImGui::EndMenu();
}

void Menu::PostEnd()
{
	if (!Editor::Get()->IsUserMode()) {
		SelectUpdate(ImGui::IsItemClicked(), ImGui::IsItemHovered());
	}

	if (p_sameLine)
		ImGui::SameLine();
}

void Menu::Serialize(std::string& content) const
{
	if (p_size.x != 0 || p_size.y != 0)
		content += "ImGui::SetNextWindowSize(ImVec2(" + std::to_string(p_size.x) + ", " + std::to_string(p_size.y) + "));\n";
	content += "if (ImGui::BeginMenu(\"" + p_name + "\"))\n{\n";
	SerializeChildren(content);
	content += "ImGui::EndMenu();\n}\n";
}

void Menu::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
}

void Menu::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
}
