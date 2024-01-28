#pragma once
#include "Object/IObject.h"

#include <any>

enum class SliderType
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

static const char* SliderTypeEnumToString()
{
	return "Int\0Int2\0Int3\0Int4\0Float\0Float2\0Float3\0Float4\0";
}

class Slider : public ItemObject<Slider>
{
public:
	Slider() = default;
	Slider& operator=(const Slider& other) = default;
	Slider(const Slider&) = default;
	Slider(Slider&&) noexcept = default;
	~Slider() override = default;

	void Initialize() override;
	void Draw() override;
	void DisplayOnInspector() override;
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Slider"; }
private:
	SliderType m_sliderType = SliderType::Float;
	std::any m_value = 0.f;
	std::any m_min = 0.f;
	std::any m_max = 100.f;
	ImGuiSliderFlags m_flags = 0;

};