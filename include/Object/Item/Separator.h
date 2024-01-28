#pragma once
#include "Object/IObject.h"

class Separator : public ItemObject<Separator>
{
public:
	Separator() = default;
	Separator& operator=(const Separator& other) = default;
	Separator(const Separator&) = default;
	Separator(Separator&&) noexcept = default;
	~Separator() override = default;

	void Initialize() override;
	void Draw() override;
	void DisplayOnInspector() override;
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Separator"; }

private:
	std::string m_text;
};