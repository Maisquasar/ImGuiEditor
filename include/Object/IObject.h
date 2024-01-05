#pragma once
#include "pch.h"

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
		: name(name), value(value), enumValue(enumValue) {}

	void ApplyStyle(int& count) const override {}

	void DisplayVariable() override {}
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

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	virtual void Initialize() {}
	virtual void Draw() = 0;
	virtual std::shared_ptr<Object> Clone() = 0;
	virtual std::string GetTypeName() const = 0;
	virtual void DisplayOnInspector();
	virtual void PostDraw();

	bool IsAParent(Object* object);
	void AddChild(std::shared_ptr<Object> child);

	Vec2f GetPosition() const { return p_position; }
	Vec2f GetSize() const { return p_size; }
	std::string GetName() const { return p_name; }
protected:
	void AddStyleColor(StyleColor styleColor) { styleColor.Initialize(); p_styleColors.push_back(styleColor); }

	template<typename T>
	void AddStyleVar(const std::string& name, T value, ImGuiStyleVar_ enumValue) {
		p_styleVars.push_back(std::make_shared<StyleVar<T>>(name, value, enumValue));
	}
protected:
	friend class Hierarchy;
	friend class Inspector;
	friend class Canvas;

	//TODO : ADD UUID
	std::string p_name;

	bool p_selected = false;

	bool p_open = true;

	size_t p_index = -1;

	Vec2f p_position;
	Vec2f p_size;

	Object* p_parent;
	std::vector<std::weak_ptr<Object>> p_children;

	std::vector<StyleColor> p_styleColors;
	std::vector<std::shared_ptr<BaseStyleVar>> p_styleVars;
};


template <typename T>
class IObject : public Object {
public:
	IObject() { }

	std::shared_ptr<Object> Clone() override {
		auto object = std::make_shared<T>(*static_cast<T*>(this));
		object->p_name = object->GetTypeName();
		return object;
	}

	std::string GetTypeName() const override = 0;

	void Draw() override = 0;
};