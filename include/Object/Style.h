#pragma once
#include <unordered_map>

#include "pch.h"

namespace CppSer
{
	class Parser;
	class Serializer;
}

class BaseStyleVar
{
public:
	BaseStyleVar() = default;
	BaseStyleVar& operator=(const BaseStyleVar& other) = default;
	BaseStyleVar(const BaseStyleVar&) = default;
	BaseStyleVar(BaseStyleVar&&) noexcept = default;
	virtual ~BaseStyleVar() = default;

	virtual void ApplyStyle(int&) const = 0;
	virtual void DisplayVariable() = 0;

	virtual void Display()
	{
		ImGui::PushID(name.c_str());
		ImGui::Checkbox("##Inherit", &inherit);
		ImGui::SameLine();
		ImGui::BeginDisabled(inherit);
		DisplayVariable();
		ImGui::EndDisabled();
		ImGui::PopID();
	}

	virtual void Serialize(std::string& content) const;
	virtual void Serialize(CppSer::Serializer& serializer) const {}
	virtual void Deserialize(CppSer::Parser& parser) {}
public:
	std::string name;
	ImGuiStyleVar_ enumValue;
	bool inherit = true;

private:

};

template <typename T>
class StyleVar : public BaseStyleVar
{
public:
	StyleVar(const std::string& name, T value, ImGuiStyleVar_ enumValue)
	{
		this->name = name;
		this->value = value;
		this->enumValue = enumValue;
	}

	void ApplyStyle(int& count) const override {}

	void DisplayVariable() override {}

	void Serialize(std::string& content) const override {}
	void Serialize(Serializer& serializer) const override {}
	void Deserialize(Parser& parser) override {}
public:
	T value;

};

template <>
class StyleVar<ImVec2> : public BaseStyleVar
{
public:
	StyleVar(const std::string& name, ImVec2 value, ImGuiStyleVar_ enumValue)
	{
		this->name = name;
		this->value = value;
		this->enumValue = enumValue;
	}

	void ApplyStyle(int& count) const override
	{
		if (!inherit)
		{
			ImGui::PushStyleVar(enumValue, value);
			count++;
		}
	}

	void Serialize(std::string& content) const override
	{
		if (inherit)
			return;
		BaseStyleVar::Serialize(content);
		content += "ImVec2(" + std::to_string(value.x) + ", " + std::to_string(value.y) + "));\n";
	}

	void Serialize(Serializer& serializer) const override
	{
		if (inherit)
			return;
		serializer << Pair::Key << name << Pair::Value << static_cast<Vec2f>(value);
	}

	void Deserialize(Parser& parser) override
	{
		const std::unordered_map<std::string, StringSerializer> valueMap = parser.GetValueMap()[parser.GetCurrentDepth()];
		if (valueMap.contains(name))
		{
			value = Vec2f(parser[name]);
			inherit = false;
		}
	}

	void DisplayVariable() override
	{
		ImGui::DragFloat2(name.c_str(), &value.x, 1.f, 0.0f, 0.0f, "%.2f");
	}
public:
	ImVec2 value;
};

template <>
class StyleVar<float> : public BaseStyleVar
{
public:
	StyleVar(const std::string& name, float value, ImGuiStyleVar_ enumValue)
	{
		this->name = name;
		this->value = value;
		this->enumValue = enumValue;
	}

	void ApplyStyle(int& count) const override
	{
		if (!inherit)
		{
			ImGui::PushStyleVar(enumValue, value);
			count++;
		}
	}

	void Serialize(std::string& content) const override
	{
		if (inherit)
			return;
		BaseStyleVar::Serialize(content);
		content += std::to_string(value) + ");\n";
	}

	void Serialize(Serializer& serializer) const override
	{
		if (inherit)
			return;
		serializer << Pair::Key << name << Pair::Value << value;
	}

	void Deserialize(Parser& parser) override
	{
		const std::unordered_map<std::string, StringSerializer> valueMap = parser.GetValueMap()[parser.GetCurrentDepth()];
		if (valueMap.contains(name))
		{
			value = parser[name].As<float>();
			inherit = false;
		}
	}

	void DisplayVariable() override
	{
		ImGui::DragFloat(name.c_str(), &value, 1.f, 0.0f, 0.0f, "%.2f");
	}
public:
	float value;
};

struct StyleColor
{
	std::string name;
	ImGuiCol_ enumValue;
	Vec4f color;
	bool inherit = true;

	void Serialize(std::string& content) const;

	void Initialize()
	{
		color = ImGui::GetStyleColorVec4(enumValue);
	}

	void Use(int& count) const
	{
		if (!inherit)
		{
			ImGui::PushStyleColor(enumValue, color);
			count++;
		}
	}

	void Display()
	{
		ImGui::PushID(name.c_str());
		ImGui::BeginDisabled(inherit);
		ImGui::ColorEdit4(name.c_str(), &color.x, ImGuiColorEditFlags_NoInputs);
		ImGui::EndDisabled();
		ImGui::SameLine();
		ImGui::Checkbox("Inherit", &inherit);
		ImGui::PopID();
	}
};

