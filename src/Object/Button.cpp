#include "Object/Button.h"

#include "Editor.h"
#include "Inspector.h"
#include "Canvas.h"

void Button::Initialize()
{
	StyleColor normalColor;
	normalColor.enumValue = ImGuiCol_Button;
	normalColor.name = "Button Color";
	AddStyleColor(normalColor);

	StyleColor hoveredColor;
	hoveredColor.enumValue = ImGuiCol_ButtonHovered;
	hoveredColor.name = "Button Hovered Color";
	AddStyleColor(hoveredColor);

	StyleColor activeColor;
	activeColor.enumValue = ImGuiCol_ButtonActive;
	activeColor.name = "Button Active Color";
	AddStyleColor(activeColor);

	StyleColor textColor;
	textColor.enumValue = ImGuiCol_Text;
	textColor.name = "Text Color";
	AddStyleColor(textColor);

	StyleColor borderColor;
	borderColor.enumValue = ImGuiCol_Border;
	borderColor.name = "Border Color";
	AddStyleColor(borderColor);

	StyleColor borderShadow;
	borderShadow.enumValue = ImGuiCol_BorderShadow;
	borderShadow.name = "Border Shadow";
	AddStyleColor(borderShadow);

	AddStyleVar("Frame Rounding", ImGui::GetStyle().FrameRounding, ImGuiStyleVar_FrameRounding);
	AddStyleVar("Frame Padding", ImGui::GetStyle().FramePadding, ImGuiStyleVar_FramePadding);
	AddStyleVar("Frame Border Size", ImGui::GetStyle().FrameBorderSize, ImGuiStyleVar_FrameBorderSize);
	AddStyleVar("Button Text Align", ImGui::GetStyle().ButtonTextAlign, ImGuiStyleVar_ButtonTextAlign);
}

void Button::Draw()
{
	ImGui::Button(p_name.c_str(), p_size);
}
