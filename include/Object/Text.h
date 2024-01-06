#pragma once
#include "pch.h"
#include "IObject.h"


class Text : public IObject<Text>
{
public:
	Text() = default;
	Text& operator=(const Text& other) = default;
	Text(const Text&) = default;
	Text(Text&&) noexcept = default;
	~Text() override = default;

	void Initialize() override;
	void Draw() override;
	void DisplayOnInspector() override;
	void Serialize(std::string& content) const override;

	std::string GetTypeName() const override { return "Text"; }
private:
	std::string m_text = "Text";
	bool m_wrap = false;
	bool m_autoWrap = true;
	float m_wrapWidth = 200;
};