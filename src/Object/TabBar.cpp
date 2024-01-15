#include "Object/TabBar.h"

#include "Canvas.h"
#include "Editor.h"
#include "Inspector.h"

void TabBar::PostDraw()
{
	static Canvas* canvas = Editor::Get()->GetCanvas();
	static Inspector* inspector = Editor::Get()->GetInspector();
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
