#include "Canvas.h"
#include "Object/IObject.h"

#include "Editor.h"
#include "Hierarchy.h"
#include "Inspector.h"

void Canvas::Initialize()
{
}

void Canvas::Draw() const
{
	static float pos = 0;
	static Hierarchy* hierarchy = Editor::Get()->GetHierarchy();
	//ImGui::ShowStyleEditor();
	//ImGui::ShowMetricsWindow();
	if (ImGui::Begin("Canvas", nullptr))
	{
		size_t index = 0;
		for (const auto& weakObject : hierarchy->GetRoot()->p_children)
		{
			DisplayObject(weakObject.lock(), ++index);
		}
	}
	ImGui::End();
}

void Canvas::DisplayObject(std::shared_ptr<Object> object, size_t& index) const
{
	if (!object->p_enable)
		return;
	object->p_id = index;
	if (!m_isDynamic) {
		const Vec2f anchorPosition = (Vec2f)ImGui::GetWindowContentRegionMin() + object->p_anchorPosition *
			((Vec2f)ImGui::GetWindowContentRegionMax() + object->GetPosition() - object->p_realSize - (Vec2f)ImGui::GetWindowContentRegionMin());
		const Vec2f value = object->GetPosition() + anchorPosition;
		object->p_realPos = value;
	}
	else
	{
		const Vec2f anchorPosition = (Vec2f)ImGui::GetCursorPos() + object->p_anchorPosition *
			((Vec2f)ImGui::GetWindowContentRegionMax() + object->GetPosition() - object->p_realSize - (Vec2f)ImGui::GetCursorPos());
		object->p_realPos = object->GetPosition() + anchorPosition;
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
	if (Editor::IsUserMode())
		return;
	if (m_hoveredObject && ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		m_hoveredObject->p_position = m_hoveredObject->p_position + ImGui::GetIO().MouseDelta;
	}
}

