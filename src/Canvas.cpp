#include "Canvas.h"
#include "Object/IObject.h"

#include "Editor.h"
#include "Hierarchy.h"
#include "Inspector.h"

void Canvas::Initialize()
{
	m_objects = &Editor::Get()->GetHierarchy()->m_objects;
}

void Canvas::Draw() const
{
	static Hierarchy* hierarchy = Editor::Get()->GetHierarchy();
	ImGui::ShowStyleEditor();
	//ImGui::ShowMetricsWindow();
	if (ImGui::Begin("Canvas"))
	{
		size_t index = 0;
		for (const auto& weakObject : hierarchy->GetRoot()->p_children)
		{
			DisplayObject(weakObject.lock(), ++index);
		}
		ImGui::PushID(881134931);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7.000000, 7.000000));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.000000);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.000000);
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.000000, 0.000000, 0.000000, 0.500000));
		ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.000000, 0.000000, 0.000000, 0.000000));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.160784, 0.156863, 0.164706, 1.000000));
		if (ImGui::BeginChildFrame(ImGuiID("ChildObject"), ImVec2(142, 200)))
		{
			ImGui::PushID(1496750022);
			ImGui::Image(0, ImVec2(128.000000, 128.000000)); // Image path : D:\Code\Moteurs\GalaxyEngine\GalaxyCore\CoreResources\textures\debug_texture.png
			ImGui::PopID();
			ImGui::PushID(819570321);
			ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 0, ImGui::GetCursorPosY() + -150));
			bool variable819570321 = 0;
			float sizeY = ImGui::GetContentRegionAvail().y;
			ImGui::Selectable("##Selectable", &variable819570321, 0, ImVec2(0.000000, sizeY));
			ImGui::PopID();

			ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() - 55.f));
			const char* text = "Resource name";
			ImGui::PushID(1095439681);
			ImVec2 realPos = ImGui::GetCursorPos();
			ImVec2 textSize = ImGui::CalcTextSize(text);
			ImVec2 windowSize = ImVec2(ImGui::GetWindowSize().x - realPos.x * 2, ImGui::GetWindowSize().y - realPos.y * 2);
			ImVec2 pos = ImVec2((windowSize.x - textSize.x) * 0.500000, (windowSize.y - textSize.y) * 0.000000);
			ImGui::SetCursorPos(ImVec2(realPos.x + pos.x, realPos.y + pos.y));
			ImGui::TextWrapped(text);
			ImGui::PopID();

			ImGui::PushID(431035082);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.696078, 0.696078, 0.696078, 1.000000));
			ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 0, ImGui::GetCursorPosY() + 15));
			ImGui::TextUnformatted("Text");
			ImGui::PopStyleColor(1);
			ImGui::PopID();
		}
		ImGui::EndChildFrame();
		ImGui::SameLine();
		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(3);
		ImGui::PopID();

#if 0
		ImGui::PushID(77879106);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7.000000, 7.000000));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.000000);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.000000);
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.000000, 0.000000, 0.000000, 0.500000));
		ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.000000, 0.000000, 0.000000, 0.000000));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.160784, 0.156863, 0.164706, 1.000000));
		if (ImGui::BeginChildFrame(ImGuiID("ChildObject"), ImVec2(142, 200)))
		{
			ImGui::PushID(1133263622);
			ImGui::Image(0, ImVec2(128.000000, 128.000000)); // Image path : D:\Code\Moteurs\GalaxyEngine\GalaxyCore\CoreResources\textures\debug_texture.png
			ImGui::PopID();
			ImGui::PushID(1855782205);
			ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 0, ImGui::GetCursorPosY() + -150));
			bool variable1855782205 = false;
			ImGui::Selectable("##Selectable", &variable1855782205, 0, ImVec2(0.000000, ImGui::GetContentRegionAvail().y));
			ImGui::PopID();
			ImGui::PushID(607866083);
			const ImVec2 realPos = ImGui::GetCursorPos();
			const char* text = "Resource name";
			const ImVec2 textSize = ImGui::CalcTextSize(text);
			const ImVec2 windowSize = ImVec2(ImGui::GetWindowSize().x - realPos.x * 2, ImGui::GetWindowSize().y - realPos.y * 2);
			const ImVec2 pos = ImVec2((windowSize.x - textSize.x) * 0.500000, (windowSize.y - textSize.y) * 0.000000);
			ImGui::SetCursorPos(ImVec2(realPos.x + pos.x, realPos.y + pos.y));
			ImGui::TextWrapped(text);
			ImGui::PopID();
			ImGui::PushID(517573314);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.696078, 0.696078, 0.696078, 1.000000));
			ImGui::SetCursorPos(ImVec2(ImGui::GetWindowContentRegionMin().x, ImGui::GetWindowContentRegionMin().y + 165));
			ImGui::TextUnformatted("Resource Type");
			ImGui::PopStyleColor(1);
			ImGui::PopID();
		}
		ImGui::EndChildFrame();
		ImGui::SameLine();
		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(3);
		ImGui::PopID();
#endif
	}
	ImGui::End();
}

void Canvas::DisplayObject(std::shared_ptr<Object> object, size_t& index) const
{
	object->p_id = index;
	if (!m_isStatic) {
		const Vec2f value = object->GetPosition() + ImGui::GetWindowContentRegionMin();
		object->p_realPos = value;
	}
	else
	{
		object->p_realPos = ImGui::GetCursorPos() + object->GetPosition();
	}
	ImGui::SetCursorPos(object->p_realPos);

	int styleColorCount = 0;
	for (const auto& style : object->p_styleColors)
	{
		style.Use(styleColorCount);
	}
	int styleVarCount = 0;
	for (const auto& p_styleVar : object->p_styleVars)
	{
		p_styleVar->ApplyStyle(styleVarCount);
	}

	ImGui::BeginDisabled(object->p_disabled);
	ImGui::PushID(object->p_uuid);
	object->Draw();
	ImGui::PopID();
	object->PostDraw(Editor::IsUserMode());

	if (object->Begin())
	{
		for (auto& child : object->p_children)
		{
			DisplayObject(child.lock(), ++index);
		}
		object->End();
	}
	object->PostEnd();

	ImGui::PopStyleColor(styleColorCount);
	ImGui::PopStyleVar(styleVarCount);
	ImGui::EndDisabled();
}

void Canvas::Update() const
{
	if (Editor::Get()->IsUserMode())
		return;
	if (m_hoveredObject && ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		m_hoveredObject->p_position = m_hoveredObject->p_position + ImGui::GetIO().MouseDelta;
	}
}

