#include "ObjectWindow.h"

#include "Editor.h"
#include "Hierarchy.h"

#include "Object/Item/Button.h"
#include "Object/Item/Text.h"
#include "Object/Item/Image.h"
#include "Object/Item/MenuItem.h"
#include "Object/Item/Input.h"
#include "Object/Item/Drag.h"
#include "Object/Item/Slider.h"
#include "Object/Item/Selectable.h"
#include "Object/Item/Checkbox.h"
#include "Object/Item/Separator.h"
#include "Object/Item/Empty.h"

#include "Object/Scope/ChildObject.h"
#include "Object/Scope/Group.h"
#include "Object/Scope/TabBar.h"
#include "Object/Scope/TabItem.h"
#include "Object/Scope/MainMenuBar.h"
#include "Object/Scope/Menu.h"
#include "Object/Scope/ComboBox.h"
#include "Object/Scope/Tree.h"

#include "Object/Shape/Rect.h"
#include "Object/Shape/ImageRect.h"

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
	m_availableObjects.push_back(std::make_shared<ImageRect>());
	m_availableObjects.push_back(std::make_shared<Empty>());

	std::ranges::sort(m_availableObjects, [](const auto& a, const auto& b) {
		return a->GetObjectType() < b->GetObjectType();
		});
}

void ObjectWindow::Draw() const
{
	if (ImGui::Begin("Create"))
	{
		ObjectType type = ObjectType::None;
		ImGui::TextUnformatted("Create");
		const Vec2f buttonSize = { ImGui::GetContentRegionAvail().x, 50 };
		for (auto& object : m_availableObjects)
		{
			if (object->GetObjectType() != type)
			{
				type = object->GetObjectType();
				ImGui::Separator();
				ImGui::TextUnformatted(object->GetObjectTypeName().c_str());
			}
			if (ImGui::Button(object->GetTypeName().c_str(), buttonSize))
			{
				Editor::Get()->GetHierarchy()->AddObjectToRoot(object->Clone());
			}
		}
	}
	ImGui::End();
}

