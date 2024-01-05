#include "pch.h"
#include "Object/IObject.h"

#include "Editor.h"
#include "Canvas.h"
#include "Inspector.h"

void Object::DisplayOnInspector()
{
	ImGui::SeparatorText("Style Color");
	for (auto& style : p_styleColors)
	{
		style.Display();
	}
	ImGui::SeparatorText("Style Var");
	for (auto& style : p_styleVars)
	{
		style->Display();
	}
}

void Object::PostDraw()
{
	static Canvas* canvas = Editor::Get()->GetCanvas();
	p_size = ImGui::GetItemRectSize();

	// MB TODO : add for all object a invisible button or selectable to check if the object is selected or hovered
	if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		Editor::Get()->GetInspector()->SetSelected(this);
	if (ImGui::IsItemHovered(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(this);
	else if (canvas->GetHoveredObject() == this)
		canvas->SetHoveredObject(nullptr);
}

bool Object::IsAParent(Object* object)
{
	if (!p_parent)
		return false;
	if (p_parent == object || object == this)
		return true;
	else
		return p_parent->IsAParent(object);
}

void Object::AddChild(std::shared_ptr<Object> child)
{
	if (IsAParent(child.get()))
		return;

	// Remove the child from its previous parent's children list, if it has one
	if (auto prevParent = child->p_parent) {
		prevParent->p_children.erase(
			std::remove_if(prevParent->p_children.begin(), prevParent->p_children.end(),
				[&child](const std::weak_ptr<Object>& o) {
					return o.lock() == child;
				}),
			prevParent->p_children.end());
	}

	p_children.push_back(child);
	child->p_parent = this;
}
