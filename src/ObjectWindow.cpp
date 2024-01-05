#include "ObjectWindow.h"

#include "Object/Button.h"
#include "Object/Text.h"

#include "Editor.h"
#include "Hierarchy.h"

void ObjectWindow::Initialize()
{
	m_availableObjects.push_back(std::make_shared<Button>());
	m_availableObjects.push_back(std::make_shared<Text>());
}

void ObjectWindow::Draw() const
{
	if (ImGui::Begin("Create"))
	{
		ImGui::TextUnformatted("Create");
		const Vec2f buttonSize = { ImGui::GetContentRegionAvail().x, 0 };
		for (auto& object : m_availableObjects)
		{
			if (ImGui::Button(object->GetTypeName().c_str(), buttonSize))
			{
				Editor::Get()->GetHierarchy()->AddObject(object->Clone());
			}
		}
	}
	ImGui::End();
}
