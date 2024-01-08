#include "pch.h"

#include "Editor.h"
#include "Inspector.h"
#include "Hierarchy.h"

#include "Object/IObject.h"

void Inspector::Draw()
{
	if (ImGui::IsKeyPressed(ImGuiKey_Delete) && m_selectedObject.lock())
	{
		m_selectedObject.lock()->Destroy();
	}
	if (ImGui::Begin("Inspector"))
	{
		DrawSelected();
	}
	ImGui::End();
}

void Inspector::SetSelected(Object* object)
{
	const auto weakObject = Editor::Get()->GetHierarchy()->GetWithPtr(object);

	if (m_selectedObject.lock())
	{
		m_selectedObject.lock()->p_selected = false;
	}

	m_selectedObject = weakObject;
	if (m_selectedObject.lock())
	{
		m_selectedObject.lock()->p_selected = true;
	}
}

void Inspector::DrawSelected() const
{
	static bool KeepAspectRatio = false;
	const auto selectedObject = m_selectedObject.lock();
	if (!selectedObject)
		return;
	ImGui::InputText("Name", &selectedObject->p_name);

	const auto pos = selectedObject->p_position.ToVec2i();
	if (ImGui::DragInt2("Position", pos.Data()))
	{
		selectedObject->p_position = pos;
	}
	auto size = selectedObject->p_size.ToVec2i();
	if (ImGui::DragInt2("Size", size.Data()))
	{
		Vec2f newSize = size;
		if (KeepAspectRatio) {
			if (size.x != static_cast<int>(selectedObject->p_size.x))
			{
				newSize.y = newSize.x * selectedObject->p_size.y / selectedObject->p_size.x;
			}
			else if (size.y != static_cast<int>(selectedObject->p_size.y))
			{
				newSize.x = newSize.y * selectedObject->p_size.x / selectedObject->p_size.y;
			}
		}
		selectedObject->p_size = newSize;
	}
	ImGui::Checkbox("Keep aspect ratio", &KeepAspectRatio);
	ImGui::NewLine();
	ImGui::Checkbox("Same line", &selectedObject->p_sameLine);
	ImGui::SeparatorText("Parameters");
	selectedObject->DisplayOnInspector();
}
