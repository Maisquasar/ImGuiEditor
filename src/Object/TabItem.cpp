#include "Object/TabItem.h"

#include <random>

#include "Canvas.h"
#include "Editor.h"
#include "Inspector.h"

void TabItem::Initialize()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());

	std::uniform_int_distribution<uint64_t> distrib;
	m_randomValue = distrib(gen);
	auto style = ImGui::GetStyle();

	AddStyleVar("Tab Rounding", style.TabRounding, ImGuiStyleVar_TabRounding);

	AddStyleColor("Tab", ImGuiCol_Tab);
	AddStyleColor("Tab Active", ImGuiCol_TabActive);
	AddStyleColor("Tab Unfocused", ImGuiCol_TabUnfocused);
	AddStyleColor("Tab Unfocused Active", ImGuiCol_TabUnfocusedActive);
}

void TabItem::PostDraw()
{
	static Canvas* canvas = Editor::Get()->GetCanvas();
	static Inspector* inspector = Editor::Get()->GetInspector();

	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		inspector->SetSelected(this);
	if (ImGui::IsWindowHovered(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(this);
	else if (canvas->GetHoveredObject() == this && !ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(nullptr);
}

bool TabItem::Begin()
{
	return ImGui::BeginTabItem((p_name + "##" + std::to_string(m_randomValue)).c_str());
}

void TabItem::End()
{
	ImGui::EndTabItem();

	if (p_sameLine)
		ImGui::SameLine();
}

void TabItem::Serialize(std::string& content) const
{
	content += "if (ImGui::BeginTabItem(\"" + p_name + "\"))\n{\n";
	SerializeChildren(content);
	content += "ImGui::EndTabItem();\n}\n";
}

void TabItem::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
}

void TabItem::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
}
