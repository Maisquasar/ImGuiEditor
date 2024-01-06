#include "Object/Text.h"

void Text::Initialize()
{
	StyleColor textColor;
	textColor.enumValue = ImGuiCol_Text;
	textColor.name = "Text Color";
	AddStyleColor(textColor);
}


void Text::Draw()
{
	if (m_wrap) {
		if (m_autoWrap) {
			ImGui::TextWrapped(m_text.c_str());
		}
		else
		{
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + m_wrapWidth);
			ImGui::TextUnformatted(m_text.c_str());
			ImGui::PopTextWrapPos();
		}
	}
	else
		ImGui::TextUnformatted(m_text.c_str());
}

void Text::DisplayOnInspector()
{
	ImGui::InputText("Text", &m_text);
	ImGui::Checkbox("Wrap", &m_wrap);

	ImGui::BeginDisabled(!m_wrap);
	ImGui::Checkbox("Auto-Wrap", &m_autoWrap);

	ImGui::BeginDisabled(m_autoWrap);
	ImGui::DragFloat("Wrap Width", &m_wrapWidth);
	ImGui::EndDisabled();

	ImGui::EndDisabled();

	Object::DisplayOnInspector();
}

void Text::Serialize(std::string& content) const
{
	BeginSerializeStyle(content);
	//TODO: Add support for text wrapping
	content += "ImGui::Text(" + m_text + ");\n";
	SerializeChildren(content);
	EndSerializeStyle(content);
}
