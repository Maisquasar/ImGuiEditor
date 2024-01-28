#pragma once
#include "Object/IObject.h"


class Text : public ItemObject<Text>
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
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Text"; }
private:
	std::string m_text = "Text";
	bool m_wrap = false;
	Vec2f m_textAlign;
	bool m_autoWrap = true;
	float m_wrapWidth = 200;
};