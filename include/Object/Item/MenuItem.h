#pragma once
#include "Object/IObject.h"


class MenuItem : public ItemObject<MenuItem>
{
public:
	MenuItem() = default;
	MenuItem& operator=(const MenuItem& other) = default;
	MenuItem(const MenuItem&) = default;
	MenuItem(MenuItem&&) noexcept = default;
	~MenuItem() override = default;

	void Draw() override;

	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	void DisplayOnInspector() override;

	std::string GetTypeName() const override { return "MenuItem"; }
private:
	std::string m_shortcut;
};
