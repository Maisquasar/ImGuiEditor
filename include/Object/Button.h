#pragma once
#include "pch.h"
#include "IObject.h"


class Button : public IObject<Button>
{
public:
	Button() = default;
	Button& operator=(const Button& other) = default;
	Button(const Button&) = default;
	Button(Button&&) noexcept = default;
	~Button() override = default;

	void Initialize() override;
	void Draw() override;

	std::string GetTypeName() const override { return "Button"; }
private:
};