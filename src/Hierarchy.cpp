#include "Hierarchy.h"

#include "Editor.h"
#include "Inspector.h"
#include "Object/IObject.h"

void Hierarchy::Draw()
{
	static Editor* editor = Editor::Get();
	if (ImGui::Begin("Hierarchy"))
	{
		for (auto& object : m_objects)
		{
			ImGui::PushID(object.get());
			if (ImGui::Selectable(object->GetName().c_str(), &object->p_selected))
			{
				editor->GetInspector()->SetSelected(object.get());
			}
			ImGui::PopID();
		}
	}
	ImGui::End();
}

void Hierarchy::AddObject(std::shared_ptr<Object> object)
{
	object->Initialize();
	m_objects.push_back(object);
}
