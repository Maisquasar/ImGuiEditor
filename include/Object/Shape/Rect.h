#pragma once
#include "Object/IObject.h"

//TODO : Add shapeObject class
class Rect : public ShapeObject<Rect>
{
public:
	Rect() = default;
	Rect& operator=(const Rect& other) = default;
	Rect(const Rect&) = default;
	Rect(Rect&&) noexcept = default;
	~Rect() = default;

	void Initialize() override;
	void Draw() override;

	void DisplayOnInspector() override;

	std::string GetTypeName() const override;
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;
private:
	Vec4f m_color = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

	bool m_filled = true;
	float m_rounding = 0.f;

	float m_thickness = 1.f;
};
