#pragma once
#include "IObject.h"

class Rect : public IObject<Rect>
{
public:
	Rect() = default;
	Rect& operator=(const Rect& other) = default;
	Rect(const Rect&) = default;
	Rect(Rect&&) noexcept = default;
	~Rect() = default;

	void Initialize() override;
	void Draw() override;
	void PostDraw() override;

	void DisplayOnInspector() override;

	std::string GetTypeName() const override;
	void Serialize(std::string& content) const override;

	Vec2f GetMin() const;
	Vec2f GetMax() const;
private:
	Vec4f m_color = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
};