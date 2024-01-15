#include "Object/Input.h"
#include <array>
#include <random>

void Input::Initialize()
{

}

void Input::Draw()
{
	if (p_size.x != 0.f)
		ImGui::SetNextItemWidth(p_size.x);
	switch (m_inputType)
	{
	case InputType::Text: {
		auto valueString = std::any_cast<std::string>(m_value);
		if (!m_textMultiline)
			ImGui::InputText(p_name.c_str(), &valueString);
		else
			ImGui::InputTextMultiline(p_name.c_str(), &valueString, p_size);
		m_value = valueString;
		break;
	}
	case InputType::Double: {
		auto valueDouble = std::any_cast<double>(m_value);
		ImGui::InputDouble(p_name.c_str(), &valueDouble);
		m_value = valueDouble;
		break;
	}
	case InputType::Int: {
		auto valueInt = std::any_cast<int>(m_value);
		ImGui::InputInt(p_name.c_str(), &valueInt);
		m_value = valueInt;
		break;
	}
	case InputType::Int2: {
		auto valueInt = std::any_cast<std::array<int, 2>>(m_value);
		ImGui::InputInt2(p_name.c_str(), valueInt.data());
		m_value = valueInt;
		break;
	}
	case InputType::Int3: {
		auto valueInt = std::any_cast<std::array<int, 3>>(m_value);
		ImGui::InputInt3(p_name.c_str(), valueInt.data());
		m_value = valueInt;
		break;
	}
	case InputType::Int4: {
		auto valueInt = std::any_cast<std::array<int, 4>>(m_value);
		ImGui::InputInt4(p_name.c_str(), valueInt.data());
		m_value = valueInt;
		break;
	}
	case InputType::Float: {
		auto valueFloat = std::any_cast<float>(m_value);
		ImGui::InputFloat(p_name.c_str(), &valueFloat);
		m_value = valueFloat;
		break;
	}
	case InputType::Float2: {
		auto valueFloat = std::any_cast<std::array<float, 2>>(m_value);
		ImGui::InputFloat2(p_name.c_str(), valueFloat.data());
		m_value = valueFloat;
		break;
	}
	case InputType::Float3: {
		auto valueFloat = std::any_cast<std::array<float, 3>>(m_value);
		ImGui::InputFloat3(p_name.c_str(), valueFloat.data());
		m_value = valueFloat;
		break;
	}
	case InputType::Float4: {
		auto valueFloat = std::any_cast<std::array<float, 4>>(m_value);
		ImGui::InputFloat4(p_name.c_str(), valueFloat.data());
		m_value = valueFloat;
		break;
	}
	default:
		break;
	}
}

void Input::DisplayOnInspector()
{
	int inputType = (int)m_inputType;
	if (ImGui::Combo("Input Type", &inputType, InputTypeEnumToString()))
	{
		m_inputType = (InputType)inputType;
		switch (m_inputType)
		{
		case InputType::Text:
			m_value = std::string("");
			break;
		case InputType::Double:
			m_value = 0.0;
			break;
		case InputType::Int:
			m_value = 0;
			break;
		case InputType::Int2:
			m_value = std::array<int, 2>();
			break;
		case InputType::Int3:
			m_value = std::array<int, 3>();
			break;
		case InputType::Int4:
			m_value = std::array<int, 4>();
			break;
		case InputType::Float:
			m_value = 0.0f;
			break;
		case InputType::Float2:
			m_value = std::array<float, 2>();
			break;
		case InputType::Float3:
			m_value = std::array<float, 3>();
			break;
		case InputType::Float4:
			m_value = std::array<float, 4>();
			break;
		default:
			break;
		}
	}
	switch (m_inputType)
	{
	case InputType::Text:
		ImGui::Checkbox("Multiline", &m_textMultiline);
		break;
	}
	Object::DisplayOnInspector();
}

void Input::Serialize(std::string& content) const
{
	std::random_device rd;
	std::mt19937_64 gen(rd());

	std::uniform_int_distribution<uint64_t> distrib;
	uint64_t m_randomValue = distrib(gen);
	std::string variableName = "variable" + std::to_string(m_randomValue);

	if (p_size.x != 0.f)
		content += "ImGui::SetNextItemWidth(" + std::to_string(p_size.x) + ");\n";

	switch (m_inputType)
	{
	case InputType::Text:
		content += "std::string " + variableName + " = \"" + std::any_cast<std::string>(m_value) + "\";\n";
		if (m_textMultiline) {
			content += "ImGui::InputTextMultiline(\"" + p_name + "\", &" + variableName +
				", ImVec2(" + std::to_string(p_size.x) + ", " + std::to_string(p_size.y) + ");\n";
		}
		else {
			content += "ImGui::InputText(\"" + p_name + "\", &" + variableName + ")\n";
		}
		break;
	case InputType::Double:
		content += "double " + variableName + " = " + std::to_string(std::any_cast<double>(m_value)) + ";\n";
		content += "ImGui::InputDouble(\"" + p_name + "\", &" + variableName + ")\n";
		break;
	case InputType::Int:
		content += "int " + variableName + " = " + std::to_string(std::any_cast<int>(m_value)) + ";\n";
		content += "ImGui::InputInt(\"" + p_name + "\", &" + variableName + ")\n";
		break;
	case InputType::Int2:
	{
		std::array<int, 2> valueArray = std::any_cast<std::array<int, 2>>(m_value);
		content += "int " + variableName + "[2] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + "};\n";
		content += "ImGui::InputInt2(\"" + p_name + "\", &" + variableName + ")\n";
	}
	break;
	case InputType::Int3:
	{
		std::array<int, 3> valueArray = std::any_cast<std::array<int, 3>>(m_value);
		content += "int " + variableName + "[3] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + "};\n";
		content += "ImGui::InputInt3(\"" + p_name + "\", &" + variableName + ")\n";
	}
	break;
	case InputType::Int4:
	{
		std::array<int, 4> valueArray = std::any_cast<std::array<int, 4>>(m_value);
		content += "int " + variableName + "[4] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + ", " + std::to_string(valueArray[3]) + "};\n";
		content += "ImGui::InputInt4(\"" + p_name + "\", &" + variableName + ")\n";
	}
	break;
	case InputType::Float:
	{
		content += "float " + variableName + " = " + std::to_string(std::any_cast<float>(m_value)) + ";\n";
		content += "ImGui::InputFloat(\"" + p_name + "\", &" + variableName + ")\n";
	}
	break;
	case InputType::Float2:
	{
		std::array<float, 2> valueArray = std::any_cast<std::array<float, 2>>(m_value);
		content += "float " + variableName + "[2] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + "};\n";
		content += "ImGui::InputFloat2(\"" + p_name + "\", &" + variableName + ")\n";
	}
	break;
	case InputType::Float3:
	{
		std::array<float, 3> valueArray = std::any_cast<std::array<float, 3>>(m_value);
		content += "float " + variableName + "[3] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + "};\n";
		content += "ImGui::InputFloat3(\"" + p_name + "\", &" + variableName + ")\n";
	}
	break;
	case InputType::Float4:
	{
		std::array<float, 4> valueArray = std::any_cast<std::array<float, 4>>(m_value);
		content += "float " + variableName + "[4] = { " + std::to_string(valueArray[0]) + ", " + std::to_string(valueArray[1]) + ", " + std::to_string(valueArray[2]) + ", " + std::to_string(valueArray[3]) + "};\n";
		content += "ImGui::InputFloat4(\"" + p_name + "\", &" + variableName + ")\n";
	}
	break;
	default:
		break;
	}
	SerializeChildren(content);
}

void Input::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);
	serializer << Pair::KEY << "InputType" << Pair::VALUE << (int)m_inputType;
	switch (m_inputType)
	{
	case InputType::Text:
		serializer << Pair::KEY << "Value" << Pair::VALUE << std::any_cast<std::string>(m_value);
		break;
	case InputType::Double:
		serializer << Pair::KEY << "Value" << Pair::VALUE << std::any_cast<double>(m_value);
		break;
	case InputType::Int:
		serializer << Pair::KEY << "Value" << Pair::VALUE << std::any_cast<int>(m_value);
		break;
	case InputType::Int2:
	{
		auto valueInt = std::any_cast<std::array<int, 2>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec2f(valueInt[0], valueInt[1]);
	}
	break;
	case InputType::Int3:
	{
		auto valueInt = std::any_cast<std::array<int, 3>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec3f(valueInt[0], valueInt[1], valueInt[2]);
	}
	break;
	case InputType::Int4:
	{
		auto valueInt = std::any_cast<std::array<int, 4>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec4f(valueInt[0], valueInt[1], valueInt[2], valueInt[3]);
	}
	break;
	case InputType::Float:
		serializer << Pair::KEY << "Value" << Pair::VALUE << std::any_cast<float>(m_value);
		break;
	case InputType::Float2:
	{
		auto valueFloat = std::any_cast<std::array<float, 2>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec2f(valueFloat[0], valueFloat[1]);
	}
	break;
	case InputType::Float3:
	{
		auto valueFloat = std::any_cast<std::array<float, 3>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec3f(valueFloat[0], valueFloat[1], valueFloat[2]);
	}
	break;
	case InputType::Float4:
	{
		auto valueFloat = std::any_cast<std::array<float, 4>>(m_value);
		serializer << Pair::KEY << "Value" << Pair::VALUE << Vec4f(valueFloat[0], valueFloat[1], valueFloat[2], valueFloat[3]);
	}
	break;
	default:
		break;
	}
}

void Input::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);
	m_inputType = (InputType)parser["InputType"].As<int>();

	switch (m_inputType)
	{
	case InputType::Text:
		m_value = parser["Value"].As<std::string>();
		break;
	case InputType::Double:
		m_value = parser["Value"].As<double>();
		break;
	case InputType::Int:
		m_value = parser["Value"].As<int>();
		break;
	case InputType::Int2:
	{
		auto vecValue = parser["Value"].As<Vec2f>();
		m_value = std::array<int, 2>({ (int)vecValue.x, (int)vecValue.y });
	}
	break;
	case InputType::Int3:
	{
		auto vecValue = parser["Value"].As<Vec3f>();
		m_value = std::array<int, 3>({ (int)vecValue.x, (int)vecValue.y, (int)vecValue.z });
	}
	break;
	case InputType::Int4:
	{
		auto vecValue = parser["Value"].As<Vec4f>();
		m_value = std::array<int, 4>({ (int)vecValue.x, (int)vecValue.y, (int)vecValue.z, (int)vecValue.w });
	}
	break;
	case InputType::Float:
		m_value = parser["Value"].As<float>();
		break;
	case InputType::Float2:
	{
		auto vecValue = parser["Value"].As<Vec2f>();
		m_value = std::array<float, 2>({ (float)vecValue.x, (float)vecValue.y });
	}
	break;
	case InputType::Float3:
	{
		auto vecValue = parser["Value"].As<Vec3f>();
		m_value = std::array<float, 3>({ (float)vecValue.x, (float)vecValue.y, (float)vecValue.z });
	}
	break;
	case InputType::Float4:
	{
		auto vecValue = parser["Value"].As<Vec4f>();
		m_value = std::array<float, 4>({ (float)vecValue.x, (float)vecValue.y, (float)vecValue.z, (float)vecValue.w });
	}
	break;
	default:
		break;
	}
}

