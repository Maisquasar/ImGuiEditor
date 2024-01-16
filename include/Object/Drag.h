#pragma once
#include "Object/IObject.h"

#include <any>

enum class DragType
{
	Int,
	Int2,
	Int3,
	Int4,
	Float,
	Float2,
	Float3,
	Float4,
};

static const char* DragTypeEnumToString()
{
	return "Int\0Int2\0Int3\0Int4\0Float\0Float2\0Float3\0Float4\0";
}

class Drag : public IObject<Drag>
{
public:
	Drag() = default;
	Drag& operator=(const Drag& other) = default;
	Drag(const Drag&) = default;
	Drag(Drag&&) noexcept = default;
	~Drag() override = default;

	void Initialize() override;
	void Draw() override;
	void DisplayOnInspector() override;
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Drag"; }
private:
	DragType m_dragType = DragType::Float;
	ImGuiSliderFlags m_flags = 0;
	std::any m_value = 0.f;
	float m_speed = 1.f;
	std::any m_min = 0.f;
	std::any m_max = 0.f;

};