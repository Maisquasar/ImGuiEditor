#include "ObjectWindow.h"

#include "Editor.h"
#include "Hierarchy.h"

#include "Object/Button.h"
#include "Object/Text.h"
#include "Object/ChildObject.h"
#include "Object/Rect.h"
#include "Object/Group.h"
#include "Object/Image.h"

void ObjectWindow::Initialize()
{
	m_availableObjects.push_back(std::make_shared<Button>());
	m_availableObjects.push_back(std::make_shared<Text>());
	m_availableObjects.push_back(std::make_shared<ChildObject>());
	m_availableObjects.push_back(std::make_shared<Rect>());
	m_availableObjects.push_back(std::make_shared<Group>());
	m_availableObjects.push_back(std::make_shared<Image>());
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
				Editor::Get()->GetHierarchy()->AddObjectToRoot(object->Clone());
			}
		}
	}
	ImGui::End();
}

