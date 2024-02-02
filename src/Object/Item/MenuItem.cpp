#include "Object/Item/MenuItem.h"

#include "Canvas.h"
#include "Editor.h"
#include "Inspector.h"

void MenuItem::Draw()
{
	ImGui::MenuItem(p_name.c_str(), m_shortcut.c_str());

	if (!Editor::Get()->IsUserMode()) {
		SelectUpdate(ImGui::IsItemClicked(), ImGui::IsItemHovered());
	}
}

void MenuItem::Serialize(std::string& content) const
{
	content += "if (ImGui::MenuItem(\"" + p_name + "\", \"" + m_shortcut.c_str() + "\"))\n{\n";
	SerializeChildren(content);
	content += "}\n";
}

void MenuItem::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
	serializer << Pair::Key << "Shortcut" << Pair::Value << m_shortcut;
}

void MenuItem::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
	m_shortcut = parser["Shortcut"].As<std::string>();
}

void MenuItem::DisplayOnInspector()
{
	ImGui::InputText("Shortcut", &m_shortcut);
	Object::DisplayOnInspector();
}
