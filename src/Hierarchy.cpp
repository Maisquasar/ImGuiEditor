#include "Hierarchy.h"

#include "Editor.h"
#include "Inspector.h"

#include "Object/IObject.h"
#include "Object/Button.h"

void Hierarchy::Initialize()
{
	m_root = std::make_shared<Button>();
	m_root->p_name = "Root";
}

void Hierarchy::Draw()
{
	if (ImGui::Begin("Hierarchy"))
	{
		size_t index = 0;
		DisplayOnHierarchy(m_root, index);
	}
	ImGui::End();
}

void Hierarchy::DisplayOnHierarchy(std::shared_ptr<Object> object, size_t& index)
{
	static Editor* editor = Editor::Get();

	object->p_index = index;

	ImGui::PushID(object.get());

	if (object->p_children.empty())
		ImGui::Button("#");
	else if (ImGui::ArrowButton("##", object->p_open ? ImGuiDir_Down : ImGuiDir_Right))
		object->p_open = !object->p_open;
	ImGui::SameLine();
	if (ImGui::Selectable(object->GetName().c_str(), &object->p_selected))
	{
		editor->GetInspector()->SetSelected(object.get());
	}

	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("OBJECT_CELL", &object->p_index, sizeof(size_t));

		ImGui::Text("Moving %s", object->GetName().c_str());

		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OBJECT_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(size_t));
			size_t draggedIndex = *(const size_t*)payload->Data;

			auto childObject = GetWithIndex(draggedIndex);
			if (childObject)
			{
				object->AddChild(childObject);
			}
		}
		ImGui::EndDragDropTarget();
	}
	ImGui::PopID();

	//TODO : only children item can have children
	if (object->p_open)
	{
		for (auto child : object->p_children)
		{
			ImGui::TreePush(child.lock()->p_name.c_str());
			index++;
			DisplayOnHierarchy(child.lock(), index);
			ImGui::TreePop();
		}
	}
}

void Hierarchy::AddObject(std::shared_ptr<Object> object)
{
	object->Initialize();
	m_objects.push_back(object);
}

void Hierarchy::AddObjectToRoot(std::shared_ptr<Object> object)
{
	m_root->AddChild(object);
	object->Initialize();
	m_objects.push_back(object);
}

std::shared_ptr<Object> Hierarchy::GetWithIndex(size_t index)
{
	for (auto object : m_objects)
	{
		if (object->p_index == index)
			return object;
	}
	return nullptr;
}
