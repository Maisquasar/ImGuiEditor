#include "Object/IObject.h"

#include "Editor.h"
#include "Canvas.h"
#include "Inspector.h"

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
