#include "pch.h"
#include "Inspector.h"
#include "Object/IObject.h"

void Inspector::Draw()
{
	if (ImGui::Begin("Inspector"))
	{
		DrawSelected();
	}
	ImGui::End();
}

void Inspector::SetSelected(Object* object)
{
	if (m_selectedObject)
	{
		m_selectedObject->p_selected = false;
	}

	m_selectedObject = object;
	if (m_selectedObject)
	{
		m_selectedObject->p_selected = true;
	}
}

void Inspector::SetHovered(Object* object)
{
	m_hoveredObject = object;
}

void Inspector::DrawSelected() const
{
	if (!m_selectedObject)
		return;
	ImGui::InputText("Name", &m_selectedObject->p_name);

	const auto pos = m_selectedObject->p_position.ToVec2i();
	if (ImGui::DragInt2("Position", pos.Data()))
	{
		m_selectedObject->p_position = pos;
	}
	const auto size = m_selectedObject->p_size.ToVec2i();
	if (ImGui::DragInt2("Size", size.Data()))
	{
		m_selectedObject->p_size = size;
	}
	ImGui::SeparatorText("Parameters");
	m_selectedObject->DisplayOnInspector();
}
