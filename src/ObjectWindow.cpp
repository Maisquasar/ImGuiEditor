#include "ObjectWindow.h"

#include "Editor.h"
#include "Hierarchy.h"

#include "Object/Button.h"
#include "Object/Text.h"
#include "Object/ChildObject.h"
#include "Object/Rect.h"
#include "Object/Group.h"
#include "Object/Image.h"
#include "Object/MainMenuBar.h"
#include "Object/Menu.h"
#include "Object/MenuItem.h"
#include "Object/TabBar.h"
#include "Object/TabItem.h"
#include "Object/Input.h"
#include "Object/Drag.h"
#include "Object/Slider.h"
#include "Object/ComboBox.h"
#include "Object/Selectable.h"
#include "Object/Checkbox.h"
#include "Object/Separator.h"
#include "Object/Tree.h"

void ObjectWindow::Initialize()
{
	m_availableObjects.push_back(std::make_shared<Button>());
	m_availableObjects.push_back(std::make_shared<Text>());
	m_availableObjects.push_back(std::make_shared<Image>());
	m_availableObjects.push_back(std::make_shared<Input>());
	m_availableObjects.push_back(std::make_shared<Drag>());
	m_availableObjects.push_back(std::make_shared<Slider>());
	m_availableObjects.push_back(std::make_shared<ComboBox>());
	m_availableObjects.push_back(std::make_shared<Selectable>());
	m_availableObjects.push_back(std::make_shared<Checkbox>());
	m_availableObjects.push_back(std::make_shared<Separator>());
	m_availableObjects.push_back(std::make_shared<Tree>());

	m_availableObjects.push_back(std::make_shared<TabBar>());
	m_availableObjects.push_back(std::make_shared<TabItem>());
	m_availableObjects.push_back(std::make_shared<ChildObject>());
	m_availableObjects.push_back(std::make_shared<Group>());

	m_availableObjects.push_back(std::make_shared<Rect>());
	m_availableObjects.push_back(std::make_shared<MainMenuBar>());
	m_availableObjects.push_back(std::make_shared<Menu>());
	m_availableObjects.push_back(std::make_shared<MenuItem>());
}

void ObjectWindow::Draw() const
{
	if (ImGui::Begin("Create"))
	{
		ImGui::TextUnformatted("Create");
		const Vec2f buttonSize = { ImGui::GetContentRegionAvail().x, 50 };
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

