#include "Object/Item/Slider.h"
#include <array>

void Slider::Initialize()
{
	AddStyleColor("Text Color", ImGuiCol_Text);
	AddStyleColor("Border Color", ImGuiCol_Border);
	AddStyleColor("Border Shadow", ImGuiCol_BorderShadow);
	AddStyleColor("Slider Grab", ImGuiCol_SliderGrab);
	AddStyleColor("Slider Grab Active", ImGuiCol_SliderGrabActive);

	AddStyleVar("Frame Rounding", ImGui::GetStyle().FrameRounding, ImGuiStyleVar_FrameRounding);
	AddStyleVar("Frame Padding", ImGui::GetStyle().FramePadding, ImGuiStyleVar_FramePadding);
	AddStyleVar("Frame Border Size", ImGui::GetStyle().FrameBorderSize, ImGuiStyleVar_FrameBorderSize);
	AddStyleVar("Grab Rounding", ImGui::GetStyle().GrabRounding, ImGuiStyleVar_GrabRounding);
	AddStyleVar("Grab Min Size", ImGui::GetStyle().GrabMinSize, ImGuiStyleVar_GrabMinSize);
}

void Slider::Draw()
{
	if (p_size.x != 0.f)
		ImGui::SetNextItemWidth(p_size.x);
	switch (m_sliderType)
	{
	case SliderType::Int: {
		auto valueInt = std::any_cast<int>(m_value);
		ImGui::SliderInt(p_name.c_str(), &valueInt, std::any_cast<int>(m_min), std::any_cast<int>(m_max), "%d", m_flags);
		m_value = valueInt;
		break;
	}
	case SliderType::Int2: {
		auto valueInt = std::any_cast<std::array<int, 2>>(m_value);
		ImGui::SliderInt2(p_name.c_str(), valueInt.data(), std::any_cast<int>(m_min), std::any_cast<int>(m_max), "%d", m_flags);
		m_value = valueInt;
		break;
	}
	case SliderType::Int3: {
		auto valueInt = std::any_cast<std::array<int, 3>>(m_value);
		ImGui::SliderInt3(p_name.c_str(), valueInt.data(), std::any_cast<int>(m_min), std::any_cast<int>(m_max), "%d", m_flags);
		m_value = valueInt;
		break;
	}
	case SliderType::Int4: {
		auto valueInt = std::any_cast<std::array<int, 4>>(m_value);
		ImGui::SliderInt4(p_name.c_str(), valueInt.data(), std::any_cast<int>(m_min), std::any_cast<int>(m_max), "%d", m_flags);
		m_value = valueInt;
		break;
	}
	case SliderType::Float: {
		auto valueFloat = std::any_cast<float>(m_value);
		ImGui::SliderFloat(p_name.c_str(), &valueFloat, std::any_cast<float>(m_min), std::any_cast<float>(m_max), "%.3f", m_flags);
		m_value = valueFloat;
		break;
	}
	case SliderType::Float2: {
		auto valueFloat = std::any_cast<std::array<float, 2>>(m_value);
		ImGui::SliderFloat2(p_name.c_str(), valueFloat.data(), std::any_cast<float>(m_min), std::any_cast<float>(m_max), "%.3f", m_flags);
		m_value = valueFloat;
		break;
	}
	case SliderType::Float3: {
		auto valueFloat = std::any_cast<std::array<float, 3>>(m_value);
		ImGui::SliderFloat3(p_name.c_str(), valueFloat.data(), std::any_cast<float>(m_min), std::any_cast<float>(m_max), "%.3f", m_flags);
		m_value = valueFloat;
		break;
	}
	case SliderType::Float4: {
		auto valueFloat = std::any_cast<std::array<float, 4>>(m_value);
		ImGui::SliderFloat4(p_name.c_str(), valueFloat.data(), std::any_cast<float>(m_min), std::any_cast<float>(m_max), "%.3f", m_flags);
		m_value = valueFloat;
		break;
	}
	default:
		break;
	}
}

void Slider::DisplayOnInspector()
{
	ImGui::BeginDisabled(m_sliderType != SliderType::Float && m_sliderType != SliderType::Int);
	ImGui::EndDisabled();
	ImGui::SetItemTooltip("Only work with Int and Float type");
	int inputType = (int)m_sliderType;
	if (ImGui::Combo("Slider Type", &inputType, SliderTypeEnumToString()))
	{
		m_sliderType = (SliderType)inputType;
		switch (m_sliderType)
		{
		case SliderType::Int:
			m_value = 0;
			m_min = 0;
			m_max = 100;
			break;
		case SliderType::Int2:
			m_value = std::array<int, 2>();
			m_min = 0;
			m_max = 100;
			break;
		case SliderType::Int3:
			m_value = std::array<int, 3>();
			m_min = 0;
			m_max = 100;
			break;
		case SliderType::Int4:
			m_value = std::array<int, 4>();
			m_min = 0;
			m_max = 100;
			break;
		case SliderType::Float:
			m_value = 0.0f;
			m_min = 0.f;
			m_max = 100.f;
			break;
		case SliderType::Float2:
			m_value = std::array<float, 2>();
			m_min = 0.f;
			m_max = 100.f;
			break;
		case SliderType::Float3:
			m_value = std::array<float, 3>();
			m_min = 0.f;
			m_max = 100.f;
			break;
		case SliderType::Float4:
			m_value = std::array<float, 4>();
			m_min = 0.f;
			m_max = 100.f;
			break;
		default:
			break;
		}
	}

	switch (m_sliderType)
	{
	case SliderType::Int:
	case SliderType::Int2:
	case SliderType::Int3:
	case SliderType::Int4:
	{
		int min = std::any_cast<int>(m_min);
		ImGui::InputInt("Min", &min);
		int max = std::any_cast<int>(m_max);
		ImGui::InputInt("Max", &max);

		m_min = min;
		m_max = max;
	}
	break;
	case SliderType::Float:
	case SliderType::Float2:
	case SliderType::Float3:
	case SliderType::Float4:
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

void Slider::Serialize(std::string& content) const
{
	std::string variableName = "variable" + std::to_string(p_uuid);

	if (p_size.x != 0.f)
		content += "ImGui::SetNextItemWidth(" + std::to_string(p_size.x) + ");\n";

	switch (m_sliderType)
	{
	case SliderType::Int: {

		content += "int " + variableName + " = " + std::to_string(std::any_cast<int>(m_value)) + ";\n";
		content += "ImGui::SliderInt(\"" + p_name + "\", &" + variableName
			+ ", " + std::to_string(std::any_cast<int>(m_min))
			+ ", " + std::to_string(std::any_cast<int>(m_max))
			+ ", \"%d\", " + std::to_string(m_flags) + ");\n";
	}
			break;
	case SliderType::Int2:
	{
		std::array<int, 2> valueArray = std::any_cast<std::array<int, 2>>(m_value);
		content += "int " + variableName + "[2] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + "};\n";
		content += "ImGui::SliderInt2(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(std::any_cast<int>(m_min))
			+ ", " + std::to_string(std::any_cast<int>(m_max))
			+ ", \"%d\", " + std::to_string(m_flags) + ");\n";
	}
	break;
	case SliderType::Int3:
	{
		std::array<int, 3> valueArray = std::any_cast<std::array<int, 3>>(m_value);
		content += "int " + variableName + "[3] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + "};\n";
		content += "ImGui::SliderInt3(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(std::any_cast<int>(m_min))
			+ ", " + std::to_string(std::any_cast<int>(m_max))
			+ ", \"%d\", " + std::to_string(m_flags) + ");\n";
	}
	break;
	case SliderType::Int4:
	{
		std::array<int, 4> valueArray = std::any_cast<std::array<int, 4>>(m_value);
		content += "int " + variableName + "[4] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + ", " + std::to_string(valueArray[3]) + "};\n";
		content += "ImGui::SliderInt4(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(std::any_cast<int>(m_min))
			+ ", " + std::to_string(std::any_cast<int>(m_max))
			+ ", \"%d\", " + std::to_string(m_flags) + ");\n";
	}
	break;
	case SliderType::Float:
	{
		content += "float " + variableName + " = " + std::to_string(std::any_cast<float>(m_value)) + ";\n";
		content += "ImGui::SliderFloat(\"" + p_name + "\", &" + variableName
			+ ", " + std::to_string(std::any_cast<float>(m_min))
			+ ", " + std::to_string(std::any_cast<float>(m_max))
			+ ", \"%.3f\", " + std::to_string(m_flags) + ");\n";
	}
	break;
	case SliderType::Float2:
	{
		std::array<float, 2> valueArray = std::any_cast<std::array<float, 2>>(m_value);
		content += "float " + variableName + "[2] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + "};\n";
		content += "ImGui::SliderFloat2(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(std::any_cast<float>(m_min))
			+ ", " + std::to_string(std::any_cast<float>(m_max))
			+ ", \"%.3f\", " + std::to_string(m_flags) + ");\n";
	}
	break;
	case SliderType::Float3:
	{
		std::array<float, 3> valueArray = std::any_cast<std::array<float, 3>>(m_value);
		content += "float " + variableName + "[3] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + "};\n";
		content += "ImGui::SliderFloat3(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(std::any_cast<float>(m_min))
			+ ", " + std::to_string(std::any_cast<float>(m_max))
			+ ", \"%.3f\", " + std::to_string(m_flags) + ");\n";
	}
	break;
	case SliderType::Float4:
	{
		std::array<float, 4> valueArray = std::any_cast<std::array<float, 4>>(m_value);
		content += "float " + variableName + "[4] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + ", " + std::to_string(valueArray[3]) + "};\n";
		content += "ImGui::SliderFloat4(\"" + p_name + "\", " + variableName
			+ ", " + std::to_string(std::any_cast<float>(m_min))
			+ ", " + std::to_string(std::any_cast<float>(m_max))
			+ ", \"%.3f\", " + std::to_string(m_flags) + ");\n";
	}
	break;
	default:
		break;
	}
	SerializeChildren(content);
}

void Slider::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::Key << "InputType" << Pair::Value << (int)m_sliderType;
	serializer << Pair::Key << "Flags" << Pair::Value << (int)m_flags;
	switch (m_sliderType)
	{
	case SliderType::Int:
		serializer << Pair::Key << "Value" << Pair::Value << std::any_cast<int>(m_value);
		break;
	case SliderType::Int2:
	{
		auto valueInt = std::any_cast<std::array<int, 2>>(m_value);
		serializer << Pair::Key << "Value" << Pair::Value << Vec2f(valueInt[0], valueInt[1]);
	}
	break;
	case SliderType::Int3:
	{
		auto valueInt = std::any_cast<std::array<int, 3>>(m_value);
		serializer << Pair::Key << "Value" << Pair::Value << Vec3f(valueInt[0], valueInt[1], valueInt[2]);
	}
	break;
	case SliderType::Int4:
	{
		auto valueInt = std::any_cast<std::array<int, 4>>(m_value);
		serializer << Pair::Key << "Value" << Pair::Value << Vec4f(valueInt[0], valueInt[1], valueInt[2], valueInt[3]);
	}
	break;
	case SliderType::Float:
		serializer << Pair::Key << "Value" << Pair::Value << std::any_cast<float>(m_value);
		break;
	case SliderType::Float2:
	{
		auto valueFloat = std::any_cast<std::array<float, 2>>(m_value);
		serializer << Pair::Key << "Value" << Pair::Value << Vec2f(valueFloat[0], valueFloat[1]);
	}
	break;
	case SliderType::Float3:
	{
		auto valueFloat = std::any_cast<std::array<float, 3>>(m_value);
		serializer << Pair::Key << "Value" << Pair::Value << Vec3f(valueFloat[0], valueFloat[1], valueFloat[2]);
	}
	break;
	case SliderType::Float4:
	{
		auto valueFloat = std::any_cast<std::array<float, 4>>(m_value);
		serializer << Pair::Key << "Value" << Pair::Value << Vec4f(valueFloat[0], valueFloat[1], valueFloat[2], valueFloat[3]);
	}
	break;
	default:
		break;
	}
	switch (m_sliderType)
	{
	case SliderType::Int:
	case SliderType::Int2:
	case SliderType::Int3:
	case SliderType::Int4:
		serializer << Pair::Key << "Min" << Pair::Value << std::any_cast<int>(m_min);
		serializer << Pair::Key << "Max" << Pair::Value << std::any_cast<int>(m_max);
		break;
	case SliderType::Float:
	case SliderType::Float2:
	case SliderType::Float3:
	case SliderType::Float4:
		serializer << Pair::Key << "Min" << Pair::Value << std::any_cast<float>(m_min);
		serializer << Pair::Key << "Max" << Pair::Value << std::any_cast<float>(m_max);
		break;
	default:
		break;
	}
}

void Slider::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_sliderType = (SliderType)parser["SliderType"].As<int>();
	m_flags = parser["Flags"].As<int>();
	switch (m_sliderType)
	{
	case SliderType::Int:
		m_value = parser["Value"].As<int>();
		break;
	case SliderType::Int2:
	{
		auto vecValue = Vec2f(parser["Value"]);
		m_value = std::array<int, 2>({ (int)vecValue.x, (int)vecValue.y });
	}
	break;
	case SliderType::Int3:
	{
		auto vecValue = Vec3f(parser["Value"]);
		m_value = std::array<int, 3>({ (int)vecValue.x, (int)vecValue.y, (int)vecValue.z });
	}
	break;
	case SliderType::Int4:
	{
		auto vecValue = Vec4f(parser["Value"]);
		m_value = std::array<int, 4>({ (int)vecValue.x, (int)vecValue.y, (int)vecValue.z, (int)vecValue.w });
	}
	break;
	case SliderType::Float:
		m_value = parser["Value"].As<float>();
		break;
	case SliderType::Float2:
	{
		auto vecValue = Vec2f(parser["Value"]);
		m_value = std::array<float, 2>({ (float)vecValue.x, (float)vecValue.y });
	}
	break;
	case SliderType::Float3:
	{
		auto vecValue = Vec3f(parser["Value"]);
		m_value = std::array<float, 3>({ (float)vecValue.x, (float)vecValue.y, (float)vecValue.z });
	}
	break;
	case SliderType::Float4:
	{
		auto vecValue = Vec4f(parser["Value"]);
		m_value = std::array<float, 4>({ (float)vecValue.x, (float)vecValue.y, (float)vecValue.z, (float)vecValue.w });
	}
	break;
	default:
		break;
	}
	switch (m_sliderType)
	{
	case SliderType::Int:
	case SliderType::Int2:
	case SliderType::Int3:
	case SliderType::Int4:
		m_min = parser["Min"].As<int>();
		m_max = parser["Max"].As<int>();
		break;
	case SliderType::Float:
	case SliderType::Float2:
	case SliderType::Float3:
	case SliderType::Float4:
		m_min = parser["Min"].As<float>();
		m_max = parser["Max"].As<float>();
		break;
	default:
		break;
	}
}

