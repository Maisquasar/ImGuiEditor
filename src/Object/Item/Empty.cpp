#include "Object/Item/Empty.h"

void Empty::Initialize()
{
	AddStyleColor("Text Color", ImGuiCol_Text);
	AddStyleColor("Text Disabled Color", ImGuiCol_TextDisabled);
	AddStyleColor("Window Background Color", ImGuiCol_WindowBg);
	AddStyleColor("Child Background Color", ImGuiCol_ChildBg);
	AddStyleColor("Popup Background Color", ImGuiCol_PopupBg);
	AddStyleColor("Border Color", ImGuiCol_Border);
	AddStyleColor("Border Shadow Color", ImGuiCol_BorderShadow);
	AddStyleColor("Frame Background Color", ImGuiCol_FrameBg);
	AddStyleColor("Frame Background Hovered Color", ImGuiCol_FrameBgHovered);
	AddStyleColor("Frame Background Active Color", ImGuiCol_FrameBgActive);
	AddStyleColor("Title Background Color", ImGuiCol_TitleBg);
	AddStyleColor("Title Background Active Color", ImGuiCol_TitleBgActive);
	AddStyleColor("Title Background Collapsed Color", ImGuiCol_TitleBgCollapsed);
	AddStyleColor("Menu Bar Background Color", ImGuiCol_MenuBarBg);
	AddStyleColor("Scrollbar Background Color", ImGuiCol_ScrollbarBg);
	AddStyleColor("Scrollbar Grab Color", ImGuiCol_ScrollbarGrab);
	AddStyleColor("Scrollbar Grab Hovered Color", ImGuiCol_ScrollbarGrabHovered);
	AddStyleColor("Scrollbar Grab Active Color", ImGuiCol_ScrollbarGrabActive);
	AddStyleColor("Check Mark Color", ImGuiCol_CheckMark);
	AddStyleColor("Slider Grab Color", ImGuiCol_SliderGrab);
	AddStyleColor("Slider Grab Active Color", ImGuiCol_SliderGrabActive);
	AddStyleColor("Header Color", ImGuiCol_Header);
	AddStyleColor("Header Hovered Color", ImGuiCol_HeaderHovered);
	AddStyleColor("Header Active Color", ImGuiCol_HeaderActive);
	AddStyleColor("Separator Color", ImGuiCol_Separator);
	AddStyleColor("Separator Hovered Color", ImGuiCol_SeparatorHovered);
	AddStyleColor("Separator Active Color", ImGuiCol_SeparatorActive);
	AddStyleColor("Resize Grip Color", ImGuiCol_ResizeGrip);
	AddStyleColor("Resize Grip Hovered Color", ImGuiCol_ResizeGripHovered);
	AddStyleColor("Resize Grip Active Color", ImGuiCol_ResizeGripActive);
	AddStyleColor("Tab Color", ImGuiCol_Tab);
	AddStyleColor("Tab Hovered Color", ImGuiCol_TabHovered);
	AddStyleColor("Tab Active Color", ImGuiCol_TabActive);
	AddStyleColor("Tab Unfocused Color", ImGuiCol_TabUnfocused);
	AddStyleColor("Tab Unfocused Active Color", ImGuiCol_TabUnfocusedActive);
	AddStyleColor("Docking Preview Color", ImGuiCol_DockingPreview);
	AddStyleColor("Docking Empty Background Color", ImGuiCol_DockingEmptyBg);
	AddStyleColor("Plot Lines Color", ImGuiCol_PlotLines);
	AddStyleColor("Plot Lines Hovered Color", ImGuiCol_PlotLinesHovered);
	AddStyleColor("Plot Histogram Color", ImGuiCol_PlotHistogram);
	AddStyleColor("Plot Histogram Hovered Color", ImGuiCol_PlotHistogramHovered);
	AddStyleColor("Table Header Background Color", ImGuiCol_TableHeaderBg);
	AddStyleColor("Table Border Strong Color", ImGuiCol_TableBorderStrong);
	AddStyleColor("Table Border Light Color", ImGuiCol_TableBorderLight);
	AddStyleColor("Table Row Background Color", ImGuiCol_TableRowBg);
	AddStyleColor("Table Row Background Alt Color", ImGuiCol_TableRowBgAlt);
	AddStyleColor("Text Selected Background Color", ImGuiCol_TextSelectedBg);
	AddStyleColor("Drag Drop Target Color", ImGuiCol_DragDropTarget);
	AddStyleColor("Nav Highlight Color", ImGuiCol_NavHighlight);
	AddStyleColor("Nav Windowing Highlight Color", ImGuiCol_NavWindowingHighlight);
	AddStyleColor("Nav Windowing Dim Background Color", ImGuiCol_NavWindowingDimBg);
	AddStyleColor("Modal Window Dim Background Color", ImGuiCol_ModalWindowDimBg);

	AddStyleVar("Alpha", ImGui::GetStyle().Alpha, ImGuiStyleVar_Alpha);
	AddStyleVar("Disabled Alpha", ImGui::GetStyle().DisabledAlpha, ImGuiStyleVar_DisabledAlpha);
	AddStyleVar("Window Padding", ImGui::GetStyle().WindowPadding, ImGuiStyleVar_WindowPadding);
	AddStyleVar("Window Rounding", ImGui::GetStyle().WindowRounding, ImGuiStyleVar_WindowRounding);
	AddStyleVar("Window Border Size", ImGui::GetStyle().WindowBorderSize, ImGuiStyleVar_WindowBorderSize);
	AddStyleVar("Window Min Size", ImGui::GetStyle().WindowMinSize, ImGuiStyleVar_WindowMinSize);
	AddStyleVar("Window Title Align", ImGui::GetStyle().WindowTitleAlign, ImGuiStyleVar_WindowTitleAlign);
	AddStyleVar("Child Rounding", ImGui::GetStyle().ChildRounding, ImGuiStyleVar_ChildRounding);
	AddStyleVar("Child Border Size", ImGui::GetStyle().ChildBorderSize, ImGuiStyleVar_ChildBorderSize);
	AddStyleVar("Popup Rounding", ImGui::GetStyle().PopupRounding, ImGuiStyleVar_PopupRounding);
	AddStyleVar("Popup Border Size", ImGui::GetStyle().PopupBorderSize, ImGuiStyleVar_PopupBorderSize);
	AddStyleVar("Frame Padding", ImGui::GetStyle().FramePadding, ImGuiStyleVar_FramePadding);
	AddStyleVar("Frame Rounding", ImGui::GetStyle().FrameRounding, ImGuiStyleVar_FrameRounding);
	AddStyleVar("Frame Border Size", ImGui::GetStyle().FrameBorderSize, ImGuiStyleVar_FrameBorderSize);
	AddStyleVar("Item Spacing", ImGui::GetStyle().ItemSpacing, ImGuiStyleVar_ItemSpacing);
	AddStyleVar("Item Inner Spacing", ImGui::GetStyle().ItemInnerSpacing, ImGuiStyleVar_ItemInnerSpacing);
	AddStyleVar("Indent Spacing", ImGui::GetStyle().IndentSpacing, ImGuiStyleVar_IndentSpacing);
	AddStyleVar("Cell Padding", ImGui::GetStyle().CellPadding, ImGuiStyleVar_CellPadding);
	AddStyleVar("Scrollbar Size", ImGui::GetStyle().ScrollbarSize, ImGuiStyleVar_ScrollbarSize);
	AddStyleVar("Scrollbar Rounding", ImGui::GetStyle().ScrollbarRounding, ImGuiStyleVar_ScrollbarRounding);
	AddStyleVar("Grab Min Size", ImGui::GetStyle().GrabMinSize, ImGuiStyleVar_GrabMinSize);
	AddStyleVar("Grab Rounding", ImGui::GetStyle().GrabRounding, ImGuiStyleVar_GrabRounding);
	AddStyleVar("Tab Rounding", ImGui::GetStyle().TabRounding, ImGuiStyleVar_TabRounding);
	AddStyleVar("Button Text Align", ImGui::GetStyle().ButtonTextAlign, ImGuiStyleVar_ButtonTextAlign);
	AddStyleVar("Selectable Text Align", ImGui::GetStyle().SelectableTextAlign, ImGuiStyleVar_SelectableTextAlign);
	AddStyleVar("Separator Text Border Size", ImGui::GetStyle().SeparatorTextBorderSize, ImGuiStyleVar_SeparatorTextBorderSize);
	AddStyleVar("Separator Text Align", ImGui::GetStyle().SeparatorTextAlign, ImGuiStyleVar_SeparatorTextAlign);
	AddStyleVar("Separator Text Padding", ImGui::GetStyle().SeparatorTextPadding, ImGuiStyleVar_SeparatorTextPadding);
	AddStyleVar("Docking Separator Size", ImGui::GetStyle().DockingSeparatorSize, ImGuiStyleVar_DockingSeparatorSize);

	p_shouldPushID = false;

}

void Empty::Serialize(std::string& content) const
{
	SerializeChildren(content);
}
