#pragma once
#include "Object/IObject.h"

class Selectable : public IObject<Selectable>
{
public:
	Selectable() = default;
	Selectable& operator=(const Selectable& other) = default;
	Selectable(const Selectable&) = default;
	Selectable(Selectable&&) noexcept = default;
	~Selectable() override = default;

	void Initialize() override;
	void Draw() override;
	void DisplayOnInspector() override;
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Selectable"; }
private:
	bool m_selected = false;
	ImGuiSelectableFlags m_flags;
};