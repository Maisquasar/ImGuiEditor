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
	//ImGui::ShowStyleEditor();
	//ImGui::ShowMetricsWindow();
	if (ImGui::Begin("Canvas"))
	{
		size_t index = 0;
		for (const auto& weakObject : hierarchy->GetRoot()->p_children)
		{
			DisplayObject(weakObject.lock(), ++index);
		}
		/*
		ImGui::PushID(1);
		if (ImGui::BeginTabBar("TabBar"))
		{
			ImGui::PushID(2);
			if (ImGui::BeginTabItem("TabItem"))
			{
				ImGui::PushID(3);
				ImGui::TextUnformatted("Text");
				ImGui::PopID();
				ImGui::EndTabItem();
			}
			ImGui::PopID();
			ImGui::PushID(4);

			if (ImGui::BeginTabItem("TabItem"))
			{
				ImGui::EndTabItem();
			}

			ImGui::PopID();
			ImGui::EndTabBar();
		}
		ImGui::PopID();
		*/
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
	for (auto& style : object->p_styleColors)
	{
		style.Use(styleColorCount);
	}
	int styleVarCount = 0;
	for (size_t i = 0; i < object->p_styleVars.size(); i++)
	{
		object->p_styleVars[i]->ApplyStyle(styleVarCount);
	}


	ImGui::PushID(index);
	object->Draw();
	ImGui::PopID();
	object->PostDraw();

	if (object->Begin())
	{
		for (auto& child : object->p_children)
		{
			DisplayObject(child.lock(), ++index);
		}
		object->End();
	}

	ImGui::PopStyleColor(styleColorCount);
	ImGui::PopStyleVar(styleVarCount);
}

void Canvas::Update() const
{
	if (m_hoveredObject && ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		m_hoveredObject->p_position = m_hoveredObject->p_position + ImGui::GetIO().MouseDelta;
	}
}

