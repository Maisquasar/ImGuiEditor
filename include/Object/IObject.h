#pragma once
#include "pch.h"

#include "Parser.h"

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
	virtual void Serialize(Serializer& serializer) const {}
	virtual void Deserialize(Parser& parser) {}
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
		serializer << Pair::KEY << name << Pair::VALUE << static_cast<Vec2f>(value);
	}

	void Deserialize(Parser& parser) override
	{
		const std::unordered_map<std::string, StringSerializer> valueMap = parser.GetValueMap()[parser.GetCurrentDepth()];
		if (valueMap.contains(name))
		{
			value = parser[name].As<Vec2f>();
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
		content += "ImVec2(" + std::to_string(value) + "));\n";
	}

	void Serialize(Serializer& serializer) const override
	{
		if (inherit)
			return;
		serializer << Pair::KEY << name << Pair::VALUE << value;
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

class Object
{
public:
	Object();
	virtual ~Object();

	// Called on creation
	virtual void Initialize() {}

	// Called after Initialize, after parsing
	virtual void PostInitialize() {}

	// Called before draw all children
	virtual bool Begin() = 0;
	// Called after draw all children
	virtual void End() = 0;
	virtual void PostEnd() = 0;

	virtual void Draw() = 0;
	virtual std::shared_ptr<Object> Clone() = 0;
	virtual std::string GetTypeName() const = 0;
	virtual void Serialize(std::string& content) const = 0;
	virtual void Serialize(Serializer& serializer) const;
	virtual void Deserialize(Parser& parser);
	virtual void DisplayOnInspector();
	void PostDraw();

	void Destroy();

	void InternalSerialize(std::string& content) const;

	void SerializeChildren(std::string& content) const;
	void BeginSerializeStyle(std::string& content) const;
	void EndSerializeStyle(std::string& content) const;

	bool IsAParentOfThis(Object* object) const;
	bool IsAParent() const { return !p_children.empty(); }
	void AddChild(std::shared_ptr<Object> child);
	void RemoveChild(Object* child);

	void SelectUpdate(bool clicked, bool hovered);

	Vec2f GetPosition() const { return p_position; }
	Vec2f GetSize() const { return p_size; }
	std::string GetName() const { return p_name; }
protected:
	void AddStyleColor(const std::string& name, const ImGuiCol_ enumValue)
	{
		StyleColor styleColor = StyleColor(name, enumValue);
		styleColor.Initialize();
		p_styleColors.push_back(styleColor);
	}
	void AddStyleColor(StyleColor styleColor)
	{
		styleColor.Initialize();
		p_styleColors.push_back(styleColor);
	}

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
	size_t p_id = -1;
	int p_uuid = 0;

	Vec2f p_position;
	Vec2f p_size;
	Vec2f p_realPos;

	bool p_sameLine = false;
	bool p_disabled = false;

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
		std::random_device rd;
		std::mt19937_64 gen(rd());

		std::uniform_int_distribution<int> distrib;
		object->p_uuid = distrib(gen);
		return object;
	}

	std::string GetTypeName() const override = 0;

	void Draw() override = 0;

	virtual void Serialize(std::string& content) const override {}
};

template <typename T>
class ItemObject : public IObject<T>
{
public:
	bool Begin() final { return true; }
	void End() final {}
	void PostEnd() final {}
private:

};

template<typename T>
class ScopeObject : public IObject<T>
{
	void Draw() final override {}

	virtual bool Begin() override = 0;
	virtual void End() override = 0;
	virtual void PostEnd() override {}
};
