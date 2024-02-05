#pragma once
#include "pch.h"
#include "Style.h"

enum class ObjectType
{
	None,
	Item,
	Scope,
	Shape
};

enum class Anchor
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight
};

inline const char* AnchorEnumToString()
{
	return "TopLeft\0TopRight\0BottomLeft\0BottomRight\0";
}


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
	// Called after draw all children only if begin return true
	virtual void End() = 0;
	// Called after draw all children
	virtual void PostEnd() = 0;

	virtual void Draw() = 0;
	virtual std::shared_ptr<Object> Clone() = 0;
	virtual std::string GetTypeName() const = 0;
	virtual void Serialize(std::string& content) const = 0;
	virtual void Serialize(Serializer& serializer) const;
	virtual void Deserialize(Parser& parser);
	virtual void DisplayOnInspector();

	virtual void PostDraw(bool editorMode) {}

	void Destroy();

	virtual void InternalSerialize(std::string& content) const;

	virtual void SerializeChildren(std::string& content) const;
	void BeginSerializeStyle(std::string& content) const;
	void EndSerializeStyle(std::string& content) const;

	bool IsAParentOfThis(Object* object) const;
	bool IsAParent() const { return !p_children.empty(); }
	void AddChild(const std::shared_ptr<Object>& child);
	void RemoveChild(Object* child);

	void SelectUpdate(bool clicked, bool hovered);

	Vec2f GetPosition() const { return p_position; }
	Vec2f GetSize() const { return p_size; }
	std::string GetName() const { return p_name; }

	virtual ObjectType GetObjectType() const = 0;
	virtual std::string GetObjectTypeName() const = 0;
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

	static std::string SerializeFloat(float value, const std::string& operatorSTR);
protected:
	friend class Hierarchy;
	friend class Inspector;
	friend class Canvas;

	//TODO : ADD UUID
	std::string p_name;

	bool p_enable = true;
	bool p_selected = false;

	bool p_open = true;

	size_t p_index = -1;
	size_t p_id = -1;
	int p_uuid = 0;

	Vec2f p_position;
	Vec2f p_size;
	Vec2f p_realPos;
	Vec2f p_realSize;

	Vec2f p_anchorPosition;

	bool p_sameLine = false;
	bool p_disabled = false;
	bool p_scoped = false;
	bool p_shouldPushID = true;

	Object* p_parent = nullptr;
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

	virtual ObjectType GetObjectType() const override = 0;
	virtual std::string GetObjectTypeName() const override = 0;
};

template <typename T>
class ItemObject : public IObject<T>
{
public:
	bool Begin() final { return true; }
	void End() final {}
	void PostEnd() final {}

	virtual void Draw() override = 0;
	void PostDraw(bool editorMode) final
	{
		this->p_realSize = ImGui::GetItemRectSize();
		if (!editorMode) {
			this->SelectUpdate(ImGui::IsItemClicked(ImGuiMouseButton_Left), ImGui::IsItemHovered(ImGuiMouseButton_Left));

			if (this->p_selected)
				ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255));
		}

		if (this->p_sameLine)
			ImGui::SameLine();
	}
	void SerializeChildren(std::string& content) const final
	{
		if (this->p_sameLine)
			content += "ImGui::SameLine();\n";
		Object::SerializeChildren(content);
	}

	ObjectType GetObjectType() const override { return ObjectType::Item; }
	std::string GetObjectTypeName() const override { return "Item"; }
private:

};

template<typename T>
class ScopeObject : public IObject<T>
{
public:
	void Draw() final {}

	void InternalSerialize(std::string& content) const override
	{
		this->BeginSerializeStyle(content);
		this->Serialize(content);
		if (this->p_sameLine)
			content += "ImGui::SameLine();\n";
		this->EndSerializeStyle(content);
	}

	virtual bool Begin() override = 0;
	virtual void End() override = 0;
	virtual void PostEnd() override {}
	ObjectType GetObjectType() const override { return ObjectType::Scope; }
	std::string GetObjectTypeName() const override { return "Scope"; }
};

template <typename T>
class ShapeObject : public IObject<T>
{
public:
	virtual void Initialize() override
	{
		this->p_shouldPushID = false;
	}
	bool Begin() final { return true; }
	void End() final {}
	void PostEnd() final {}

	virtual void Draw() override = 0;
	void PostDraw(bool editorMode) final
	{
		this->p_realSize = this->p_size;
		if (!editorMode) {

			const bool hovered = ImGui::IsMouseHoveringRect(GetMin(), GetMax());
			this->SelectUpdate(hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left), hovered);

			if (this->p_selected)
				ImGui::GetWindowDrawList()->AddRect(GetMin(), GetMax(), IM_COL32(255, 255, 0, 255));
		}
	}

	virtual void DisplayOnInspector() override
	{
		ImGui::SeparatorText("Flags");
		ImGui::CheckboxFlags("Closed", &this->p_flags, ImDrawFlags_Closed);
		ImGui::CheckboxFlags("Round corners all", &this->p_flags, ImDrawFlags_RoundCornersAll);
		ImGui::CheckboxFlags("Round corners top-left", &this->p_flags, ImDrawFlags_RoundCornersTopLeft);
		ImGui::CheckboxFlags("Round corners top-right", &this->p_flags, ImDrawFlags_RoundCornersTopRight);
		ImGui::CheckboxFlags("Round corners bottom-left", &this->p_flags, ImDrawFlags_RoundCornersBottomLeft);
		ImGui::CheckboxFlags("Round corners bottom-right", &this->p_flags, ImDrawFlags_RoundCornersBottomRight);
		ImGui::CheckboxFlags("Round corners top", &this->p_flags, ImDrawFlags_RoundCornersTop);
		ImGui::CheckboxFlags("Round corners bottom", &this->p_flags, ImDrawFlags_RoundCornersBottom);
		ImGui::CheckboxFlags("Round corners left", &this->p_flags, ImDrawFlags_RoundCornersLeft);
		ImGui::CheckboxFlags("Round corners right", &this->p_flags, ImDrawFlags_RoundCornersRight);
		ImGui::CheckboxFlags("Round corners none", &this->p_flags, ImDrawFlags_RoundCornersNone);

		Object::DisplayOnInspector();

	}

	Vec2f GetMin() const
	{
		const Vec2f min = ImGui::GetWindowPos() + ImGui::GetWindowContentRegionMin() + this->p_position - this->p_size / 2;
		return min;
	}

	Vec2f GetMax() const
	{
		const Vec2f max = ImGui::GetWindowPos() + ImGui::GetWindowContentRegionMin() + this->p_position + this->p_size / 2;
		return max;
	}
	virtual void Serialize(Serializer& serializer) const
	{
		Object::Serialize(serializer);
		serializer << Pair::Key << "Flags" << Pair::Value << this->p_flags;

	}
	virtual void Deserialize(Parser& parser)
	{
		Object::Deserialize(parser);
		this->p_flags = parser["Flags"].As<int>();
	}

	ObjectType GetObjectType() const override { return ObjectType::Shape; }
	std::string GetObjectTypeName() const override { return "Shape"; }
protected:
	ImDrawFlags p_flags = 0;
};
