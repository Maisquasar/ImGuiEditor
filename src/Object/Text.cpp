
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
	//auto textWidth = ImGui::CalcTextSize(m_text.c_str()).x;

	//ImGui::SetCursorPosX((ImGui::GetWindowWidth() - textWidth) * 0.5f);
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
	if (m_wrap) {
		if (m_autoWrap) {
			content += "ImGui::TextWrapped(\"" + m_text + "\");\n";
		}
		else
		{
			content += "ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + m_wrapWidth);\n";
			content += "ImGui::TextUnformatted(\"" + m_text + "\");\n";
			content += "ImGui::PopTextWrapPos();\n";
		}
	}
	else
		content += "ImGui::TextUnformatted(\"" + m_text + "\");\n";
	SerializeChildren(content);
}

void Text::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::KEY << "Text" << Pair::VALUE << m_text;
	serializer << Pair::KEY << "Wrap" << Pair::VALUE << m_wrap;
	serializer << Pair::KEY << "AutoWrap" << Pair::VALUE << m_autoWrap;
	serializer << Pair::KEY << "WrapWidth" << Pair::VALUE << m_wrapWidth;
}

void Text::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_text = parser["Text"];
	m_wrap = parser["Wrap"].As<bool>();
	m_autoWrap = parser["AutoWrap"].As<bool>();
	m_wrapWidth = parser["WrapWidth"].As<float>();
}
