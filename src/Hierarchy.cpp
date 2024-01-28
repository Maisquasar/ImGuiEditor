#include "Hierarchy.h"

#include "Object/Item/Button.h"

#include "Parser.h"

#include "Editor.h"
#include "Inspector.h"
#include "ObjectWindow.h"

#include "Application.h"

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

void Hierarchy::Serialize() const
{
	std::string content;
	m_root->SerializeChildren(content);

	std::cout << content << std::endl;

	Editor::Get()->GetApplication()->SetClipboardText(content.c_str());
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
		ImGui::SetDragDropPayload("OBJECT_CELL", &object->p_uuid, sizeof(int));

		ImGui::Text("Moving %s", object->GetName().c_str());

		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OBJECT_CELL");
			payload /*&& std::dynamic_pointer_cast<ChildObject>(object)*/)
		{
			IM_ASSERT(payload->DataSize == sizeof(int));
			int draggedIndex = *(const int*)payload->Data;

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
		size_t indexChild = 0;
		for (auto child : object->p_children)
		{
			if (!child.lock()) {
				std::cout << "Error with child, delete it" << std::endl;
				object->p_children.erase(std::next(object->p_children.begin(), index));
				continue;
			}
			ImGui::TreePush(child.lock()->p_name.c_str());
			index++;
			indexChild++;
			DisplayOnHierarchy(child.lock(), index);
			ImGui::TreePop();
		}
	}
}

void Hierarchy::AddObject(std::shared_ptr<Object> object)
{
	m_objects.push_back(object);
}

void Hierarchy::RemoveObject(const Object* object)
{
	for (auto it = m_objects.begin(); it != m_objects.end(); it++)
	{
		if (it->get() == object)
		{
			m_objects.erase(it);
			break;
		}
	}
}

void Hierarchy::AddObjectToRoot(std::shared_ptr<Object> object, bool addToSelected /*= true*/)
{
	auto parent = m_root.get();
	if (addToSelected) {
		if (auto select = Editor::Get()->GetInspector()->GetSelected())
			parent = select;
	}
	parent->AddChild(object);
	object->Initialize();
	object->PostInitialize();
	m_objects.push_back(object);
}

void Hierarchy::SaveScene(const std::string& path) const
{
	Serializer serializer(path);
	for (auto& child : m_root->p_children)
	{
		serializer << Pair::BEGIN_MAP << child.lock()->GetTypeName();
		child.lock()->Serialize(serializer);
		serializer << Pair::END_MAP << child.lock()->GetTypeName();
	}
}

void Hierarchy::LoadScene(const std::string& path)
{
	for (auto child : m_root->p_children)
		if (child.lock())
			child.lock()->Destroy();

	const auto filePath = std::filesystem::path(path);
	Parser parser(filePath);
	const auto objectList = Editor::Get()->GetObjectWindow()->GetAvailableObjects();
	do
	{
		std::shared_ptr<Object> object;
		auto typeName = parser["Type"].As<std::string>();
		for (auto& _object : objectList)
		{
			if (_object->GetTypeName() == typeName)
			{
				object = _object->Clone();
				break;
			}
		}
		AddObject(object);

		object->Initialize();
		m_root->AddChild(object);
		object->Deserialize(parser);
		object->PostInitialize();

		parser.NewDepth();
	} while (parser.GetValueMap().size() != parser.GetCurrentDepth());
}

std::shared_ptr<Object> Hierarchy::GetWithIndex(size_t index) const
{
	for (auto object : m_objects)
	{
		if (object->p_uuid == index)
			return object;
	}
	return nullptr;
}

std::weak_ptr<Object> Hierarchy::GetWithPtr(const Object* object)
{
	for (auto& sharedObject : m_objects)
	{
		if (sharedObject.get() == object)
			return sharedObject;
	}
	return {};
}
