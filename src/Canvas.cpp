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
		/*
		ImGui::PushID(1737609848);
		ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 100, ImGui::GetCursorPosY() + 0));
		ImGui::BeginGroup();
		{
			ImGui::PushID(1113074549);
			ImGui::Button("Button");
			ImGui::PopID();
			ImGui::PushID(5725688);
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.000000, 1.000000, 1.000000, 1.000000));
			ImGui::Button("Button");
			ImGui::PopStyleColor(1);
			ImGui::PopID();
		}
		ImGui::EndGroup();
		ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax()
			, 4294967295, 0.000000
			, ImDrawFlags_None, 0.000000);
		ImGui::SameLine();
		ImGui::SameLine();
		ImGui::PopID();
		*/
	}
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

