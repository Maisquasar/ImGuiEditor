#include "pch.h"

#include "Editor.h"
#include "Inspector.h"
#include "Hierarchy.h"
#include "ObjectWindow.h"

#include "Object/IObject.h"

#include "Parser.h"

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

	if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey_C))
	{
		CopyObject();
	}
	else if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey_V))
	{
		PasteObject();
	}
	m_hasSelected = false;
}

void Inspector::CopyObject()
{
	const auto selected = m_selectedObject.lock();
	if (!selected)
		return;

	Serializer serializer;

	serializer << Pair::BEGIN_MAP << selected->GetTypeName();
	selected->Serialize(serializer);
	serializer << Pair::END_MAP << selected->GetTypeName();

	m_clipBoard = serializer.GetContent();
}

void Inspector::PasteObject() const
{
	if (m_clipBoard.empty())
		return;
	const auto objectList = Editor::Get()->GetObjectWindow()->GetAvailableObjects();

	auto hierarchy = Editor::Get()->GetHierarchy();

	Parser parser(m_clipBoard);

	std::shared_ptr<Object> object;
	const auto typeName = parser["Type"].As<std::string>();
	for (auto& _object : objectList)
	{
		if (_object->GetTypeName() == typeName)
		{
			object = _object->Clone();
			break;
		}
	}
	hierarchy->AddObject(object);
	object->Initialize();
	const auto selected = m_selectedObject.lock();
	if (selected)
		selected->AddChild(object);
	else
		hierarchy->GetRoot()->AddChild(object);

	object->Deserialize(parser);
	object->PostInitialize();
}

void Inspector::SetSelected(Object* object)
{
	if (m_hasSelected)
		return;
	m_hasSelected = true;

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
	ImGui::Checkbox("Disabled", &selectedObject->p_disabled);
	ImGui::SeparatorText("Parameters");
	selectedObject->DisplayOnInspector();
}
