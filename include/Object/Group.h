#pragma once
#include "Object/IObject.h"

class Group : public ScopeObject<Group>
{
public:
	Group() = default;
	Group& operator=(const Group& other) = default;
	Group(const Group&) = default;
	Group(Group&&) noexcept = default;
	~Group() override = default;

	bool Begin() override;
	void End() override;

	void DisplayOnInspector() override;

	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Group"; }
private:

	bool m_hasBorder = true;
	Vec4f m_borderColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	float m_borderRounding = 0.0f;
	float m_borderWidth = 0.0f;
};
