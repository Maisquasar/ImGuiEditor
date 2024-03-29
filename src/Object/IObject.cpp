#include "pch.h"
#include "Object/IObject.h"

#include "Editor.h"
#include "Canvas.h"
#include "Inspector.h"
#include "Hierarchy.h"
#include "ObjectWindow.h"

#include <random>

Object::Object()
{
}

Object::~Object()
{
}

void Object::Destroy()
{
	const auto editor = Editor::Get();
	editor->GetHierarchy()->RemoveObject(this);

	if (p_parent)
	{
		p_parent->RemoveChild(this);
	}
}

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

void Object::InternalSerialize(std::string& content) const
{
	BeginSerializeStyle(content);
	Serialize(content);
	EndSerializeStyle(content);
}

void Object::SerializeChildren(std::string& content) const
{
	if (!p_enable)
		return;
	for (auto& child : p_children)
	{
		const auto object = child.lock();
		content += "//" + object->p_name + "\n";
		if (child.lock()->p_shouldPushID)
			content += "ImGui::PushID(" + std::to_string(object->p_uuid) + ");\n";

		if (object->p_disabled)
			content += "ImGui::BeginDisabled(true);\n";

		object->InternalSerialize(content);

		if (object->p_disabled)
			content += "ImGui::EndDisabled();\n";

		if (child.lock()->p_shouldPushID)
			content += "ImGui::PopID();\n";
	}
}

void Object::BeginSerializeStyle(std::string& content) const
{
	for (auto& style : p_styleVars)
	{
		style->Serialize(content);
	}
	for (auto& style : p_styleColors)
	{
		style.Serialize(content);
	}
	auto canvas = Editor::Get()->GetCanvas();

	if (!canvas->IsDynamic()) {

		content += "ImGui::SetCursorPos(ImVec2(";
		content += "ImGui::GetWindowContentRegionMin().x";
		if (p_anchorPosition.x != 0.f)
		{
			content += SerializeFloat(p_anchorPosition.x, "+") + R"( *
    (ImGui::GetWindowContentRegionMax().x)" + SerializeFloat(p_position.x, "+") + SerializeFloat(p_realSize.x, "-") + R"( - ImGui::GetWindowContentRegionMin().x))";
		}
		content += SerializeFloat(p_position.x, "+");
		content += "\n, ImGui::GetWindowContentRegionMin().y";
		if (p_anchorPosition.y != 0.0f)
		{
			content += SerializeFloat(p_anchorPosition.y, "+") + R"( *
    (ImGui::GetWindowContentRegionMax().y)" + SerializeFloat(p_position.y, "+") + SerializeFloat(p_realSize.y, "-") + R"( - ImGui::GetWindowContentRegionMin().y))";

		}
		content += SerializeFloat(p_position.y, "+");
		content += "));\n";
	}
	else
	{
		if (p_position.x != 0.f || p_position.y != 0.f || p_anchorPosition.x != 0.f || p_anchorPosition.y != 0.f) {
			content += "ImGui::SetCursorPos(ImVec2(";
			content += "ImGui::GetCursorPos().x";
			if (p_anchorPosition.x != 0.f)
			{
				content += SerializeFloat(p_anchorPosition.x, "+") + R"( *
    (ImGui::GetWindowContentRegionMax().x)" + SerializeFloat(p_position.x, "+") + SerializeFloat(p_realSize.x, "-") + R"( - ImGui::GetCursorPos().x))";
			}
			content += SerializeFloat(p_position.x, "+");
			content += "\n, ImGui::GetCursorPos().y";
			if (p_anchorPosition.y != 0.0f)
			{
				content += SerializeFloat(p_anchorPosition.y, "+") + R"( *
    (ImGui::GetWindowContentRegionMax().y)" + SerializeFloat(p_position.y, "+") + SerializeFloat(p_realSize.y, "-") + R"( - ImGui::GetCursorPos().y))";

			}
			content += SerializeFloat(p_position.y, "+");
			content += "));\n";
		}
	}
}

void Object::EndSerializeStyle(std::string& content) const
{
	int styleVarCount = 0;
	for (auto& style : p_styleVars)
	{
		if (!style->inherit)
			styleVarCount++;
	}
	if (styleVarCount > 0)
		content += "ImGui::PopStyleVar(" + std::to_string(styleVarCount) + ");\n";

	int styleColorCount = 0;
	for (auto& style : p_styleColors)
	{
		if (!style.inherit)
			styleColorCount++;
	}
	if (styleColorCount > 0)
		content += "ImGui::PopStyleColor(" + std::to_string(styleColorCount) + ");\n";
}

bool Object::IsAParentOfThis(Object* object) const
{
	if (!p_parent)
		return false;
	if (p_parent == object || object == this)
		return true;
	else
		return p_parent->IsAParentOfThis(object);
}

void Object::AddChild(const std::shared_ptr<Object>& child)
{
	if (!child)
	{
		std::cout << "Object::AddChild - child is nullptr" << std::endl;
		return;
	}
	if (IsAParentOfThis(child.get()))
		return;

	// Remove the child from its previous parent's children list, if it has one
	if (child->p_parent)
		child->p_parent->RemoveChild(child.get());
	p_children.push_back(child);
	child->p_parent = this;
}

void Object::RemoveChild(Object* child)
{
	for (auto it = p_children.begin(); it != p_children.end(); ++it)
	{
		if (it->lock().get() == child)
		{
			p_children.erase(it);
			child->p_parent = nullptr;
			return;
		}
	}
}

void Object::SelectUpdate(bool clicked, bool hovered)
{
	static Canvas* canvas = Editor::Get()->GetCanvas();
	static Inspector* inspector = Editor::Get()->GetInspector();

	if (clicked && !p_selected)
		inspector->SetSelected(this);
	else if (hovered && p_selected)
		canvas->SetHoveredObject(this);
	else if (canvas->GetHoveredObject() == this && !ImGui::IsMouseDown(ImGuiMouseButton_Left))
		canvas->SetHoveredObject(nullptr);
}

std::string Object::SerializeFloat(float value, const std::string& operatorSTR)
{
	if (value == 0.0f && operatorSTR != "*")
		return "";
	return " " + operatorSTR + " " + std::to_string(value);
}

void Object::Serialize(Serializer& serializer) const
{
	serializer << Pair::Key << "Type" << Pair::Value << GetTypeName();
	serializer << Pair::Key << "Name" << Pair::Value << p_name;
	serializer << Pair::Key << "Position" << Pair::Value << p_position;
	serializer << Pair::Key << "Size" << Pair::Value << p_size;
	serializer << Pair::Key << "SameLine" << Pair::Value << p_sameLine;
	serializer << Pair::Key << "Disabled" << Pair::Value << p_disabled;
	serializer << Pair::Key << "Child Number" << Pair::Value << p_children.size();

	for (auto& style : p_styleVars)
	{
		if (style->inherit)
			continue;
		style->Serialize(serializer);
	}

	for (auto& style : p_styleColors)
	{
		if (style.inherit)
			continue;
		serializer << Pair::Key << style.name << Pair::Value << style.color;
	}

	for (auto& child : p_children)
	{
		const auto object = child.lock();
		if (!object)
			continue;
		serializer << Pair::BeginMap << object->GetTypeName();
		serializer << Pair::BeginTab;
		object->Serialize(serializer);
		serializer << Pair::EndTab;
		serializer << Pair::EndMap << object->GetTypeName();
	}
}

void Object::Deserialize(Parser& parser)
{
	const auto objectList = Editor::Get()->GetObjectWindow()->GetAvailableObjects();
	const auto hierarchy = Editor::Get()->GetHierarchy();

	p_name = parser["Name"].As<std::string>();
	p_position = Vec2f(parser["Position"]);
	p_size = Vec2f(parser["Size"]);
	p_sameLine = parser["SameLine"].As<bool>();
	p_disabled = parser["Disabled"].As<bool>();
	const size_t childNumber = parser["Child Number"].As<size_t>();

	for (auto& style : p_styleVars)
	{
		style->Deserialize(parser);
	}

	for (auto& style : p_styleColors)
	{
		const std::unordered_map<std::string, StringSerializer> valueMap = parser.GetValueMap()[parser.GetCurrentDepth()];
		if (valueMap.contains(style.name))
		{
			style.color = Vec4f(parser[style.name]);
			style.inherit = false;
		}
	}

	for (size_t i = 0; i < childNumber; i++)
	{
		std::shared_ptr<Object> object;
		parser.PushDepth();
		auto typeName = parser["Type"].As<std::string>();
		for (auto& _object : objectList)
		{
			if (_object->GetTypeName() == typeName)
			{
				object = _object->Clone();
				break;
			}
		}
		if (!object)
			continue;

		hierarchy->AddObject(object);

		object->Initialize();
		this->AddChild(object);
		object->Deserialize(parser);
		object->PostInitialize();
	}
}

std::string ImGuiColToString(ImGuiCol_ enumValue)
{
	std::string enumValueStr = "";
	switch (enumValue)
	{
	case ImGuiCol_Text: enumValueStr = "ImGuiCol_Text"; break;
	case ImGuiCol_TextDisabled: enumValueStr = "ImGuiCol_TextDisabled"; break;
	case ImGuiCol_WindowBg: enumValueStr = "ImGuiCol_WindowBg"; break;
	case ImGuiCol_ChildBg: enumValueStr = "ImGuiCol_ChildBg"; break;
	case ImGuiCol_PopupBg: enumValueStr = "ImGuiCol_PopupBg"; break;
	case ImGuiCol_Border: enumValueStr = "ImGuiCol_Border"; break;
	case ImGuiCol_BorderShadow: enumValueStr = "ImGuiCol_BorderShadow"; break;
	case ImGuiCol_FrameBg: enumValueStr = "ImGuiCol_FrameBg"; break;
	case ImGuiCol_FrameBgHovered: enumValueStr = "ImGuiCol_FrameBgHovered"; break;
	case ImGuiCol_FrameBgActive: enumValueStr = "ImGuiCol_FrameBgActive"; break;
	case ImGuiCol_TitleBg: enumValueStr = "ImGuiCol_TitleBg"; break;
	case ImGuiCol_TitleBgActive: enumValueStr = "ImGuiCol_TitleBgActive"; break;
	case ImGuiCol_TitleBgCollapsed: enumValueStr = "ImGuiCol_TitleBgCollapsed"; break;
	case ImGuiCol_MenuBarBg: enumValueStr = "ImGuiCol_MenuBarBg"; break;
	case ImGuiCol_ScrollbarBg: enumValueStr = "ImGuiCol_ScrollbarBg"; break;
	case ImGuiCol_ScrollbarGrab: enumValueStr = "ImGuiCol_ScrollbarGrab"; break;
	case ImGuiCol_ScrollbarGrabHovered: enumValueStr = "ImGuiCol_ScrollbarGrabHovered"; break;
	case ImGuiCol_ScrollbarGrabActive: enumValueStr = "ImGuiCol_ScrollbarGrabActive"; break;
	case ImGuiCol_CheckMark: enumValueStr = "ImGuiCol_CheckMark"; break;
	case ImGuiCol_SliderGrab: enumValueStr = "ImGuiCol_SliderGrab"; break;
	case ImGuiCol_SliderGrabActive: enumValueStr = "ImGuiCol_SliderGrabActive"; break;
	case ImGuiCol_Button: enumValueStr = "ImGuiCol_Button"; break;
	case ImGuiCol_ButtonHovered: enumValueStr = "ImGuiCol_ButtonHovered"; break;
	case ImGuiCol_ButtonActive: enumValueStr = "ImGuiCol_ButtonActive"; break;
	case ImGuiCol_Header: enumValueStr = "ImGuiCol_Header"; break;
	case ImGuiCol_HeaderHovered: enumValueStr = "ImGuiCol_HeaderHovered"; break;
	case ImGuiCol_HeaderActive: enumValueStr = "ImGuiCol_HeaderActive"; break;
	case ImGuiCol_Separator: enumValueStr = "ImGuiCol_Separator"; break;
	case ImGuiCol_SeparatorHovered: enumValueStr = "ImGuiCol_SeparatorHovered"; break;
	case ImGuiCol_SeparatorActive: enumValueStr = "ImGuiCol_SeparatorActive"; break;
	case ImGuiCol_ResizeGrip: enumValueStr = "ImGuiCol_ResizeGrip"; break;
	case ImGuiCol_ResizeGripHovered: enumValueStr = "ImGuiCol_ResizeGripHovered"; break;
	case ImGuiCol_ResizeGripActive: enumValueStr = "ImGuiCol_ResizeGripActive"; break;
	case ImGuiCol_Tab: enumValueStr = "ImGuiCol_Tab"; break;
	case ImGuiCol_TabHovered: enumValueStr = "ImGuiCol_TabHovered"; break;
	case ImGuiCol_TabActive: enumValueStr = "ImGuiCol_TabActive"; break;
	case ImGuiCol_TabUnfocused: enumValueStr = "ImGuiCol_TabUnfocused"; break;
	case ImGuiCol_TabUnfocusedActive: enumValueStr = "ImGuiCol_TabUnfocusedActive"; break;
	case ImGuiCol_DockingPreview: enumValueStr = "ImGuiCol_DockingPreview"; break;
	case ImGuiCol_DockingEmptyBg: enumValueStr = "ImGuiCol_DockingEmptyBg"; break;
	case ImGuiCol_PlotLines: enumValueStr = "ImGuiCol_PlotLines"; break;
	case ImGuiCol_PlotLinesHovered: enumValueStr = "ImGuiCol_PlotLinesHovered"; break;
	case ImGuiCol_PlotHistogram: enumValueStr = "ImGuiCol_PlotHistogram"; break;
	case ImGuiCol_PlotHistogramHovered: enumValueStr = "ImGuiCol_PlotHistogramHovered"; break;
	case ImGuiCol_TextSelectedBg: enumValueStr = "ImGuiCol_TextSelectedBg"; break;
	case ImGuiCol_DragDropTarget: enumValueStr = "ImGuiCol_DragDropTarget"; break;
	case ImGuiCol_NavHighlight: enumValueStr = "ImGuiCol_NavHighlight"; break;
	case ImGuiCol_NavWindowingHighlight: enumValueStr = "ImGuiCol_NavWindowingHighlight"; break;
	case ImGuiCol_NavWindowingDimBg: enumValueStr = "ImGuiCol_NavWindowingDimBg"; break;
	case ImGuiCol_ModalWindowDimBg: enumValueStr = "ImGuiCol_ModalWindowDimBg"; break;
	default: assert(false); enumValueStr = "Unknown"; break;
	}
	return enumValueStr;
}

std::string ImGuiStyleVarToString(ImGuiStyleVar_ enumValue)
{
	std::string enumValueStr;
	switch (enumValue)
	{
	case ImGuiStyleVar_Alpha: enumValueStr = "ImGuiStyleVar_Alpha"; break;
	case ImGuiStyleVar_WindowPadding: enumValueStr = "ImGuiStyleVar_WindowPadding"; break;
	case ImGuiStyleVar_WindowRounding: enumValueStr = "ImGuiStyleVar_WindowRounding"; break;
	case ImGuiStyleVar_WindowBorderSize: enumValueStr = "ImGuiStyleVar_WindowBorderSize"; break;
	case ImGuiStyleVar_WindowMinSize: enumValueStr = "ImGuiStyleVar_WindowMinSize"; break;
	case ImGuiStyleVar_WindowTitleAlign: enumValueStr = "ImGuiStyleVar_WindowTitleAlign"; break;
	case ImGuiStyleVar_ChildRounding: enumValueStr = "ImGuiStyleVar_ChildRounding"; break;
	case ImGuiStyleVar_ChildBorderSize: enumValueStr = "ImGuiStyleVar_ChildBorderSize"; break;
	case ImGuiStyleVar_PopupRounding: enumValueStr = "ImGuiStyleVar_PopupRounding"; break;
	case ImGuiStyleVar_PopupBorderSize: enumValueStr = "ImGuiStyleVar_PopupBorderSize"; break;
	case ImGuiStyleVar_FramePadding: enumValueStr = "ImGuiStyleVar_FramePadding"; break;
	case ImGuiStyleVar_FrameRounding: enumValueStr = "ImGuiStyleVar_FrameRounding"; break;
	case ImGuiStyleVar_FrameBorderSize: enumValueStr = "ImGuiStyleVar_FrameBorderSize"; break;
	case ImGuiStyleVar_ItemSpacing: enumValueStr = "ImGuiStyleVar_ItemSpacing"; break;
	case ImGuiStyleVar_ItemInnerSpacing: enumValueStr = "ImGuiStyleVar_ItemInnerSpacing"; break;
	case ImGuiStyleVar_IndentSpacing: enumValueStr = "ImGuiStyleVar_IndentSpacing"; break;
	case ImGuiStyleVar_CellPadding: enumValueStr = "ImGuiStyleVar_CellPadding"; break;
	case ImGuiStyleVar_ScrollbarSize: enumValueStr = "ImGuiStyleVar_ScrollbarSize"; break;
	case ImGuiStyleVar_ScrollbarRounding: enumValueStr = "ImGuiStyleVar_ScrollbarRounding"; break;
	case ImGuiStyleVar_GrabMinSize: enumValueStr = "ImGuiStyleVar_GrabMinSize"; break;
	case ImGuiStyleVar_GrabRounding: enumValueStr = "ImGuiStyleVar_GrabRounding"; break;
	case ImGuiStyleVar_TabRounding: enumValueStr = "ImGuiStyleVar_TabRounding"; break;
	case ImGuiStyleVar_ButtonTextAlign: enumValueStr = "ImGuiStyleVar_ButtonTextAlign"; break;
	case ImGuiStyleVar_SelectableTextAlign: enumValueStr = "ImGuiStyleVar_SelectableTextAlign"; break;
	default: assert(false); enumValueStr = "Unknown"; break;
	}
	return enumValueStr;
}

void StyleColor::Serialize(std::string& content) const
{
	if (inherit)
		return;
	//ImGui::PushStyleColor(enumValue, color);
	const std::string enumValueStr = ImGuiColToString(enumValue);
	content += "ImGui::PushStyleColor(" + enumValueStr + "," + "ImVec4(" + color.ToString() + "));\n";
}

void BaseStyleVar::Serialize(std::string& content) const
{
	if (inherit)
		return;
	//ImGui::PushStyleVar(enumValue,
	const std::string enumValueStr = ImGuiStyleVarToString(enumValue);
	content += "ImGui::PushStyleVar(" + enumValueStr + ",";
}
