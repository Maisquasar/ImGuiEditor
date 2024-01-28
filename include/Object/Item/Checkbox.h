#pragma once
#include "Object/IObject.h"

class Checkbox : public ItemObject<Checkbox>
{
public:
	Checkbox() = default;
	Checkbox& operator=(const Checkbox& other) = default;
	Checkbox(const Checkbox&) = default;
	Checkbox(Checkbox&&) noexcept = default;
	~Checkbox() override = default;

	void Initialize() override;
	void Draw() override;
	void DisplayOnInspector() override;
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Checkbox"; }
private:
	bool m_value;
};