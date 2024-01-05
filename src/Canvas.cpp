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
	if (ImGui::Begin("Canvas")) {

		for (const auto& weakObject : hierarchy->GetRoot()->p_children)
		{
			DisplayObject(weakObject.lock());
		}
	}
	ImGui::End();
}

void Canvas::DisplayObject(std::shared_ptr<Object> object) const
{
	if (!m_isStatic) {
		auto vec = ImGui::GetCursorPos();
		auto pos = object->GetPosition() - object->GetSize();
		ImGui::SetCursorPos(Vec2f(8, 27) + object->GetPosition());
	}

	int styleColorCount = 0;
	for (auto& style : object->p_styleColors)
	{
		style.Use(styleColorCount);
	}
	int styleVarCount = 0;
	for (size_t i = 0; i < object->p_styleVars.size(); i++)
	{
		object->p_styleVars[i]->ApplyStyle(styleVarCount);
	}

	object->Draw();
	object->PostDraw();

	//ImGui::BeginChild(object->GetName().c_str(), object->GetSize());
	for (auto& child : object->p_children)
	{
		DisplayObject(child.lock());
	}
	//ImGui::EndChild();

	ImGui::PopStyleColor(styleColorCount);
	ImGui::PopStyleVar(styleVarCount);
}

void Canvas::Update()
{
	if (m_hoveredObject && ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		m_hoveredObject->p_position = m_hoveredObject->p_position + ImGui::GetIO().MouseDelta;
	}
}

