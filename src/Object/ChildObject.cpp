#include "pch.h"
#include "Object/ChildObject.h"

#include "Editor.h"
#include "Inspector.h"
#include "Canvas.h"

void ChildObject::Initialize()
{
	const auto style = ImGui::GetStyle();
	AddStyleVar("Window Padding", style.WindowPadding, ImGuiStyleVar_WindowPadding);
	AddStyleVar("Child Border Size", style.ChildBorderSize, ImGuiStyleVar_ChildBorderSize);
	AddStyleVar("Child Rounding", style.ChildRounding, ImGuiStyleVar_ChildRounding);
	AddStyleVar("Scrollbar Rounding", style.ScrollbarRounding, ImGuiStyleVar_ScrollbarRounding);
	AddStyleVar("Frame padding", style.FramePadding, ImGuiStyleVar_FramePadding);
	AddStyleVar("Frame rounding", style.FrameRounding, ImGuiStyleVar_FrameRounding);
	AddStyleVar("Frame border size", style.FrameBorderSize, ImGuiStyleVar_FrameBorderSize);
	AddStyleVar("Window rounding", style.WindowRounding, ImGuiStyleVar_WindowRounding);
	AddStyleVar("Window Border Size", style.WindowBorderSize, ImGuiStyleVar_WindowBorderSize);


	AddStyleColor("Border", ImGuiCol_Border);
	AddStyleColor("Border Shadow", ImGuiCol_BorderShadow);
	AddStyleColor("Text", ImGuiCol_Text);
	AddStyleColor("Text Disabled", ImGuiCol_TextDisabled);
	AddStyleColor("Window Background", ImGuiCol_WindowBg);
	AddStyleColor("Scrollbar background", ImGuiCol_ScrollbarBg);
	AddStyleColor("Scrollbar grab", ImGuiCol_ScrollbarGrab);
	AddStyleColor("Scrollbar grab hover", ImGuiCol_ScrollbarGrabHovered);
	AddStyleColor("Scrollbar grab active", ImGuiCol_ScrollbarGrabActive);
	AddStyleColor("Button", ImGuiCol_Button);
	AddStyleColor("Button Hovered", ImGuiCol_ButtonHovered);
	AddStyleColor("Button Active", ImGuiCol_ButtonActive);
	AddStyleColor("Header", ImGuiCol_Header);
	AddStyleColor("Header Hovered", ImGuiCol_HeaderHovered);
	AddStyleColor("Header Active", ImGuiCol_HeaderActive);
	AddStyleColor("Resize Gutter", ImGuiCol_ResizeGrip);
	AddStyleColor("Resize Gutter Hovered", ImGuiCol_ResizeGripHovered);
	AddStyleColor("Resize Gutter Active", ImGuiCol_ResizeGripActive);
	AddStyleColor("Plot Lines", ImGuiCol_PlotLines);
	AddStyleColor("Plot Lines Hovered", ImGuiCol_PlotLinesHovered);
	AddStyleColor("Plot Histogram", ImGuiCol_PlotHistogram);
	AddStyleColor("Plot Histogram Hovered", ImGuiCol_PlotHistogramHovered);
	AddStyleColor("Table Header", ImGuiCol_TableHeaderBg);
	AddStyleColor("Table Border", ImGuiCol_TableBorderStrong);
	AddStyleColor("Table Border Light", ImGuiCol_TableBorderLight);
	AddStyleColor("Table Row", ImGuiCol_TableRowBg);
	AddStyleColor("Table Row Selected", ImGuiCol_TableRowBg);
	AddStyleColor("Drag Drop Target", ImGuiCol_DragDropTarget);
	AddStyleColor("Nav Highlight", ImGuiCol_NavHighlight);
	AddStyleColor("Nav Windowing Highlight", ImGuiCol_NavWindowingHighlight);
	AddStyleColor("Nav Windowing DimBg", ImGuiCol_NavWindowingDimBg);
	AddStyleColor("Modal Window DimBg", ImGuiCol_ModalWindowDimBg);
	AddStyleColor("Popup Background", ImGuiCol_PopupBg);
	AddStyleColor("Check Mark", ImGuiCol_CheckMark);
	AddStyleColor("Slider Grab", ImGuiCol_SliderGrab);
	AddStyleColor("Slider Grab Active", ImGuiCol_SliderGrabActive);
	AddStyleColor("Frame Background", ImGuiCol_FrameBg);
	AddStyleColor("Frame Background Hovered", ImGuiCol_FrameBgHovered);
	AddStyleColor("Frame Background Active", ImGuiCol_FrameBgActive);
	AddStyleColor("Title Background", ImGuiCol_TitleBg);
	AddStyleColor("Title Background Active", ImGuiCol_TitleBgActive);
}

bool ChildObject::Begin()
{
	bool value = false;

	if (m_frame)
		value = ImGui::BeginChildFrame(reinterpret_cast<ImGuiID>(p_name.c_str()), p_size);
	else
		value = ImGui::BeginChild(p_name.c_str(), p_size, m_hasBorder);

	if (!Editor::IsUserMode())
		SelectUpdate(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left), ImGui::IsWindowHovered(ImGuiMouseButton_Left));

	return value;
}


void ChildObject::End()
{
	if (m_frame)
		ImGui::EndChildFrame();
	else
		ImGui::EndChild();
}

void ChildObject::PostEnd()
{
	if (p_sameLine)
		ImGui::SameLine();
}

void ChildObject::DisplayOnInspector()
{
	ImGui::Checkbox("Has border", &m_hasBorder);
	ImGui::Checkbox("Is Frame", &m_frame);
	Object::DisplayOnInspector();
}

std::string ChildObject::GetTypeName() const
{
	return "ChildObject";
}

void ChildObject::Serialize(std::string& content) const
{
	const auto size = p_size.ToVec2i();
	content += "if (";
	if (m_frame)
		content += "ImGui::BeginChildFrame(ImGuiID(\"" + p_name + "\"), ImVec2(" + std::to_string(size.x) + ", " + std::to_string(size.y) + "))";
	else
		content += "ImGui::BeginChild(\"" + p_name + "\", ImVec2(" + std::to_string(size.x) + ", " + std::to_string(size.y) + "), " + std::to_string(m_hasBorder) + ")";
	content += ")\n{\n";
	SerializeChildren(content);

	content += "}\n";
	if (m_frame)
		content += "ImGui::EndChildFrame();\n";
	else
		content += "ImGui::EndChild();\n";
}

void ChildObject::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::KEY << "HasBorder" << Pair::VALUE << m_hasBorder;
	serializer << Pair::KEY << "Frame" << Pair::VALUE << m_frame;
}

void ChildObject::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_hasBorder = parser["HasBorder"].As<bool>();
	m_frame = parser["Frame"].As<bool>();
}
