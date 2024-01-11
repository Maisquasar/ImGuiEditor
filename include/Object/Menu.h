#pragma once
#include "Object/IObject.h"


class Menu : public IObject<Menu>
{
public:
	Menu() = default;
	Menu& operator=(const Menu& other) = default;
	Menu(const Menu&) = default;
	Menu(Menu&&) noexcept = default;
	~Menu() override = default;

	void Draw() override {}
	void PostDraw() override;
	bool Begin() override;
	void End() override;

	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Menu"; }
};
