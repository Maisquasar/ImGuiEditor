#pragma once
#include "Object/IObject.h"

class ComboBox : public ScopeObject<ComboBox>
{
public:
	ComboBox() = default;
	ComboBox& operator=(const ComboBox& other) = default;
	ComboBox(const ComboBox&) = default;
	ComboBox(ComboBox&&) noexcept = default;
	~ComboBox() override = default;

	void Initialize() override;
	bool Begin() override;
	void End() override;
	void PostEnd() override;
	void DisplayOnInspector() override;
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "ComboBox"; }

private:
	ImGuiComboFlags m_flags = 0;
};