#include "Object/Item/Drag.h"
#include <array>

void Drag::Initialize()
{
	AddStyleColor("Button Color", ImGuiCol_Button);
	AddStyleColor("Button Hovered Color", ImGuiCol_ButtonHovered);
	AddStyleColor("Button Active Color", ImGuiCol_ButtonActive);
	AddStyleColor("Text Color", ImGuiCol_Text);
	AddStyleColor("Border Color", ImGuiCol_Border);
	AddStyleColor("Border Shadow", ImGuiCol_BorderShadow);

	AddStyleVar("Frame Rounding", ImGui::GetStyle().FrameRounding, ImGuiStyleVar_FrameRounding);
	AddStyleVar("Frame Padding", ImGui::GetStyle().FramePadding, ImGuiStyleVar_FramePadding);
	AddStyleVar("Frame Border Size", ImGui::GetStyle().FrameBorderSize, ImGuiStyleVar_FrameBorderSize);
	AddStyleVar("Button Text Align", ImGui::GetStyle().ButtonTextAlign, ImGuiStyleVar_ButtonTextAlign);
}

void Drag::Draw() {
	if (p_size.x != 0.f)
		ImGui::SetNextItemWidth(p_size.x);

	switch (m_dragType) {
	case DragType::Int: {
		auto valueInt = std::any_cast<int>(m_value);
		ImGui::DragInt(p_name.c_str(), &valueInt, m_speed, std::any_cast<int>(m_min), std::any_cast<int>(m_max), "%d", m_flags);
		m_value = valueInt;
		break;
	}
	case DragType::Int2: {
		auto valueInt = std::any_cast<std::array<int, 2>>(m_value);
		ImGui::DragInt2(p_name.c_str(), valueInt.data(), m_speed, std::any_cast<int>(m_min), std::any_cast<int>(m_max), "%d", m_flags);
		m_value = valueInt;
		break;
	}
	case DragType::Int3: {
		auto valueInt = std::any_cast<std::array<int, 3>>(m_value);
		ImGui::DragInt3(p_name.c_str(), valueInt.data(), m_speed, std::any_cast<int>(m_min), std::any_cast<int>(m_max), "%d", m_flags);
		m_value = valueInt;
		break;
	}
	case DragType::Int4: {
		auto valueInt = std::any_cast<std::array<int, 4>>(m_value);
		ImGui::DragInt4(p_name.c_str(), valueInt.data(), m_speed, std::any_cast<int>(m_min), std::any_cast<int>(m_max), "%d", m_flags);
		m_value = valueInt;
		break;
	}
	case DragType::Float: {
		auto valueFloat = std::any_cast<float>(m_value);
		ImGui::DragFloat(p_name.c_str(), &valueFloat, m_speed, std::any_cast<float>(m_min), std::any_cast<float>(m_max), "%.3f", m_flags);
		m_value = valueFloat;
		break;
	}
	case DragType::Float2: {
		auto valueFloat = std::any_cast<std::array<float, 2>>(m_value);
		ImGui::DragFloat2(p_name.c_str(), valueFloat.data(), m_speed, std::any_cast<float>(m_min), std::any_cast<float>(m_max), "%.3f", m_flags);
		m_value = valueFloat;
		break;
	}
	case DragType::Float3: {
		auto valueFloat = std::any_cast<std::array<float, 3>>(m_value);
		ImGui::DragFloat3(p_name.c_str(), valueFloat.data(), m_speed, std::any_cast<float>(m_min), std::any_cast<float>(m_max), "%.3f", m_flags);
		m_value = valueFloat;
		break;
	}
	case DragType::Float4: {
		auto valueFloat = std::any_cast<std::array<float, 4>>(m_value);
		ImGui::DragFloat4(p_name.c_str(), valueFloat.data(), m_speed, std::any_cast<float>(m_min), std::any_cast<float>(m_max), "%.3f", m_flags);
		m_value = valueFloat;
		break;
	}
	default:
		break;
	}
}


void Drag::DisplayOnInspector()
{
	int inputType = (int)m_dragType;
	if (ImGui::Combo("Drag Type", &inputType, DragTypeEnumToString()))
	{
		m_dragType = (DragType)inputType;
		switch (m_dragType)
		{
		case DragType::Int:
			m_value = 0;
			m_min = 0;
			m_max = 0;
			break;
		case DragType::Int2:
			m_value = std::array<int, 2>();
			m_min = 0;
			m_max = 0;
			break;
		case DragType::Int3:
			m_value = std::array<int, 3>();
			m_min = 0;
			m_max = 0;
			break;
		case DragType::Int4:
			m_value = std::array<int, 4>();
			m_min = 0;
			m_max = 0;
			break;
		case DragType::Float:
			m_value = 0.0f;
			m_min = 0.f;
			m_max = 0.f;
			break;
		case DragType::Float2:
			m_value = std::array<float, 2>();
			m_min = 0.f;
			m_max = 0.f;
			break;
		case DragType::Float3:
			m_value = std::array<float, 3>();
			m_min = 0.f;
			m_max = 0.f;
			break;
		case DragType::Float4:
			m_value = std::array<float, 4>();
			m_min = 0.f;
			m_max = 0.f;
			break;
		default:
			break;
		}
	}
	switch (m_dragType)
	{
	case DragType::Int:
	case DragType::Int2:
	case DragType::Int3:
	case DragType::Int4: 
	{
		int min = std::any_cast<int>(m_min);
		ImGui::InputInt("Min", &min);
		int max = std::any_cast<int>(m_max);
		ImGui::InputInt("Max", &max);

		m_min = min;
		m_max = max;
	}
		break;
	case DragType::Float:
	case DragType::Float2:
	case DragType::Float3:
	case DragType::Float4: 
	{
		float min = std::any_cast<float>(m_min);
		ImGui::InputFloat("Min", &min);
		float max = std::any_cast<float>(m_max);
		ImGui::InputFloat("Max", &max);

		m_min = min;
		m_max = max;
	}
		break;
	default:
		break;
	}

	ImGui::SeparatorText("Flags");
	ImGui::CheckboxFlags("Vertical", &m_flags, ImGuiSliderFlags_Vertical);
	ImGui::CheckboxFlags("Read only", &m_flags, ImGuiSliderFlags_ReadOnly);
	ImGui::CheckboxFlags("No Input", &m_flags, ImGuiSliderFlags_NoInput);
	ImGui::CheckboxFlags("Always Clamp", &m_flags, ImGuiSliderFlags_AlwaysClamp);
	ImGui::CheckboxFlags("Logarithmic", &m_flags, ImGuiSliderFlags_Logarithmic);
	ImGui::CheckboxFlags("No Round To Format", &m_flags, ImGuiSliderFlags_NoRoundToFormat);

	Object::DisplayOnInspector();
}

void Drag::Serialize(std::string& content) const
{
	std::string variableName = "variable" + std::to_string(p_uuid);

	if (p_size.x != 0.f)
		content += "ImGui::SetNextItemWidth(" + std::to_string(p_size.x) + ");\n";

	switch (m_dragType)
	{
	case DragType::Int:
		content += "int " + variableName + " = " + std::to_string(std::any_cast<int>(m_value)) + ";\n";
		content += "ImGui::DragInt(\"" + p_name + "\", &" + variableName 
			+ ", " + std::to_string(m_speed) 
			+ ", " + std::to_string(std::any_cast<int>(m_min)) 
			+ ", " + std::to_string(std::any_cast<int>(m_max)) + ");\n";
		break;
	case DragType::Int2:
	{
		std::array<int, 2> valueArray = std::any_cast<std::array<int, 2>>(m_value);
		content += "int " + variableName + "[2] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + "};\n";
		content += "ImGui::DragInt2(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(m_speed)
			+ ", " + std::to_string(std::any_cast<int>(m_min))
			+ ", " + std::to_string(std::any_cast<int>(m_max)) + ");\n";
	}
	break;
	case DragType::Int3:
	{
		std::array<int, 3> valueArray = std::any_cast<std::array<int, 3>>(m_value);
		content += "int " + variableName + "[3] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + "};\n";
		content += "ImGui::DragInt3(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(m_speed)
			+ ", " + std::to_string(std::any_cast<int>(m_min))
			+ ", " + std::to_string(std::any_cast<int>(m_max)) + ");\n";
	}
	break;
	case DragType::Int4:
	{
		std::array<int, 4> valueArray = std::any_cast<std::array<int, 4>>(m_value);
		content += "int " + variableName + "[4] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + ", " + std::to_string(valueArray[3]) + "};\n";
		content += "ImGui::DragInt4(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(m_speed)
			+ ", " + std::to_string(std::any_cast<int>(m_min))
			+ ", " + std::to_string(std::any_cast<int>(m_max)) + ");\n";
	}
	break;
	case DragType::Float:
	{
		content += "float " + variableName + " = " + std::to_string(std::any_cast<float>(m_value)) + ";\n";
		content += "ImGui::DragFloat(\"" + p_name + "\", &" + variableName
			+ ", " + std::to_string(m_speed)
			+ ", " + std::to_string(std::any_cast<float>(m_min))
			+ ", " + std::to_string(std::any_cast<float>(m_max)) + ");\n";
	}
	break;
	case DragType::Float2:
	{
		std::array<float, 2> valueArray = std::any_cast<std::array<float, 2>>(m_value);
		content += "float " + variableName + "[2] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + "};\n";
		content += "ImGui::DragFloat2(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(m_speed)
			+ ", " + std::to_string(std::any_cast<float>(m_min))
			+ ", " + std::to_string(std::any_cast<float>(m_max)) + ");\n";
	}
	break;
	case DragType::Float3:
	{
		std::array<float, 3> valueArray = std::any_cast<std::array<float, 3>>(m_value);
		content += "float " + variableName + "[3] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + "};\n";
		content += "ImGui::DragFloat3(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(m_speed)
			+ ", " + std::to_string(std::any_cast<float>(m_min))
			+ ", " + std::to_string(std::any_cast<float>(m_max)) + ");\n";
	}
	break;
	case DragType::Float4:
	{
		std::array<float, 4> valueArray = std::any_cast<std::array<float, 4>>(m_value);
		content += "float " + variableName + "[4] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + ", " + std::to_string(valueArray[3]) + "};\n";
		content += "ImGui::DragFloat4(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(m_speed)
			+ ", " + std::to_string(std::any_cast<float>(m_min))
			+ ", " + std::to_string(std::any_cast<float>(m_max)) + ");\n";
	}
	break;
	default:
		break;
	}
	SerializeChildren(content);
}

void Drag::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::KEY << "InputType" << Pair::VALUE << (int)m_dragType;
	serializer << Pair::KEY << "Flags" << Pair::VALUE << (int)m_flags;
	serializer << Pair::KEY << "Speed" << Pair::VALUE << m_speed;
	switch (m_dragType)
	{
	case DragType::Int:
		serializer << Pair::KEY << "Value" << Pair::VALUE << std::any_cast<int>(m_value);
		break;
	case DragType::Int2:
	{
		auto valueInt = std::any_cast<std::array<int, 2>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec2f(valueInt[0], valueInt[1]);
	}
	break;
	case DragType::Int3:
	{
		auto valueInt = std::any_cast<std::array<int, 3>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec3f(valueInt[0], valueInt[1], valueInt[2]);
	}
	break;
	case DragType::Int4:
	{
		auto valueInt = std::any_cast<std::array<int, 4>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec4f(valueInt[0], valueInt[1], valueInt[2], valueInt[3]);
	}
	break;
	case DragType::Float:
		serializer << Pair::KEY << "Value" << Pair::VALUE << std::any_cast<float>(m_value);
		break;
	case DragType::Float2:
	{
		auto valueFloat = std::any_cast<std::array<float, 2>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec2f(valueFloat[0], valueFloat[1]);
	}
	break;
	case DragType::Float3:
	{
		auto valueFloat = std::any_cast<std::array<float, 3>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec3f(valueFloat[0], valueFloat[1], valueFloat[2]);
	}
	break;
	case DragType::Float4:
	{
		auto valueFloat = std::any_cast<std::array<float, 4>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec4f(valueFloat[0], valueFloat[1], valueFloat[2], valueFloat[3]);
	}
	break;
	default:
		break;
	}
	switch (m_dragType)
	{
	case DragType::Int:
	case DragType::Int2:
	case DragType::Int3:
	case DragType::Int4:
		serializer << Pair::KEY << "Min" << Pair::VALUE << std::any_cast<int>(m_min);
		serializer << Pair::KEY << "Max" << Pair::VALUE << std::any_cast<int>(m_max);
		break;
	case DragType::Float:
	case DragType::Float2:
	case DragType::Float3:
	case DragType::Float4:
		serializer << Pair::KEY << "Min" << Pair::VALUE << std::any_cast<float>(m_min);
		serializer << Pair::KEY << "Max" << Pair::VALUE << std::any_cast<float>(m_max);
		break;
	default:
		break;
	}
}

void Drag::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_dragType = (DragType)parser["DragType"].As<int>();
	m_flags = parser["Flags"].As<int>();
	m_speed = parser["Speed"].As<float>();
	switch (m_dragType)
	{
	case DragType::Int:
		m_value = parser["Value"].As<int>();
		break;
	case DragType::Int2:
	{
		auto vecValue = parser["Value"].As<Vec2f>();
		m_value = std::array<int, 2>({ (int)vecValue.x, (int)vecValue.y });
	}
	break;
	case DragType::Int3:
	{
		auto vecValue = parser["Value"].As<Vec3f>();
		m_value = std::array<int, 3>({ (int)vecValue.x, (int)vecValue.y, (int)vecValue.z });
	}
	break;
	case DragType::Int4:
	{
		auto vecValue = parser["Value"].As<Vec4f>();
		m_value = std::array<int, 4>({ (int)vecValue.x, (int)vecValue.y, (int)vecValue.z, (int)vecValue.w });
	}
	break;
	case DragType::Float:
		m_value = parser["Value"].As<float>();
		break;
	case DragType::Float2:
	{
		auto vecValue = parser["Value"].As<Vec2f>();
		m_value = std::array<float, 2>({ (float)vecValue.x, (float)vecValue.y });
	}
	break;
	case DragType::Float3:
	{
		auto vecValue = parser["Value"].As<Vec3f>();
		m_value = std::array<float, 3>({ (float)vecValue.x, (float)vecValue.y, (float)vecValue.z });
	}
	break;
	case DragType::Float4:
	{
		auto vecValue = parser["Value"].As<Vec4f>();
		m_value = std::array<float, 4>({ (float)vecValue.x, (float)vecValue.y, (float)vecValue.z, (float)vecValue.w });
	}
	break;
	default:
		break;
	}
	switch (m_dragType)
	{
	case DragType::Int:
	case DragType::Int2:
	case DragType::Int3:
	case DragType::Int4:
		m_min = parser["Min"].As<int>();
		m_max = parser["Max"].As<int>();
		break;
	case DragType::Float:
	case DragType::Float2:
	case DragType::Float3:
	case DragType::Float4:
		m_min = parser["Min"].As<float>();
		m_max = parser["Max"].As<float>();
		break;
	default:
		break;
	}
}

