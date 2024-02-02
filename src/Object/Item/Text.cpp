
#include "Object/Item/Text.h"

void Text::Initialize()
{
	AddStyleColor("Text Color", ImGuiCol_Text);
	AddStyleColor("Text Disabled Color", ImGuiCol_TextDisabled);
}

void Text::Draw()
{
	Vec2f realPos = ImGui::GetCursorPos();
	auto textSize = ImGui::CalcTextSize(m_text.c_str());
	auto windowSize = ImGui::GetWindowSize() - realPos * 2;

	Vec2f pos = (windowSize - textSize) * m_textAlign;

	ImGui::SetCursorPos(realPos + pos);
	if (m_wrap) {
		if (m_autoWrap)
		{
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
	ImGui::SliderFloat2("Text Align", &m_textAlign.x, 0.f, 1.f);

	{
		ImGui::Checkbox("Wrap", &m_wrap);
		ImGui::BeginDisabled(!m_wrap);
		ImGui::Checkbox("Auto-Wrap", &m_autoWrap);

		ImGui::BeginDisabled(m_autoWrap);
		ImGui::DragFloat("Wrap Width", &m_wrapWidth);

		ImGui::EndDisabled();
		ImGui::EndDisabled();
	}

	Object::DisplayOnInspector();
}

void Text::Serialize(std::string& content) const
{
	if (m_textAlign.x != 0.f || m_textAlign.y != 0.f) {
		// Set the cursor position based on the calculated position
		content += "ImVec2 realPos = ImGui::GetCursorPos();\n";
		content += "ImVec2 textSize = ImGui::CalcTextSize(\"" + m_text + "\");\n";
		content += "ImVec2 windowSize = ImVec2(ImGui::GetWindowSize().x - realPos.x * 2, ImGui::GetWindowSize().y - realPos.y * 2);\n";
		content += "ImVec2 pos = ImVec2((windowSize.x - textSize.x) * " + std::to_string(m_textAlign.x) + ", (windowSize.y - textSize.y) * " + std::to_string(m_textAlign.y) + ");\n";
		content += "ImGui::SetCursorPos(ImVec2(realPos.x + pos.x, realPos.y + pos.y));\n";
	}
	// Output text with wrapping if necessary
	if (m_wrap) {
		if (m_autoWrap) {
			content += "ImGui::TextWrapped(\"" + m_text + "\");\n";
		}
		else {
			content += "ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + m_wrapWidth);\n";
			content += "ImGui::TextUnformatted(\"" + m_text + "\");\n";
			content += "ImGui::PopTextWrapPos();\n";
		}
	}
	else {
		content += "ImGui::TextUnformatted(\"" + m_text + "\");\n";
	}
	SerializeChildren(content);
}

void Text::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::Key << "Text" << Pair::Value << m_text;
	serializer << Pair::Key << "Text Align" << Pair::Value << m_textAlign;
	serializer << Pair::Key << "Wrap" << Pair::Value << m_wrap;
	serializer << Pair::Key << "AutoWrap" << Pair::Value << m_autoWrap;
	serializer << Pair::Key << "WrapWidth" << Pair::Value << m_wrapWidth;
}

void Text::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_text = parser["Text"];
	m_textAlign = parser["Text Align"].As<Vec2f>();
	m_wrap = parser["Wrap"].As<bool>();
	m_autoWrap = parser["AutoWrap"].As<bool>();
	m_wrapWidth = parser["WrapWidth"].As<float>();
}
