#pragma once
#include "Object/IObject.h"



class Button : public ItemObject<Button>
{
public:
	Button() = default;
	Button& operator=(const Button& other) = default;
	Button(const Button&) = default;
	Button(Button&&) noexcept = default;
	~Button() override = default;

	void Initialize() override;
	void Draw() override;
	void DisplayOnInspector() override;
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Button"; }
private:
	bool m_arrowButton = false;
	ImGuiDir_ m_arrowDir = ImGuiDir_Down;
	bool m_small = false;
	std::string m_text;
};