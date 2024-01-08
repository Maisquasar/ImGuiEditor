#pragma once
#include "Object/IObject.h"

class Group : public IObject<Group>
{
public:
	Group() = default;
	Group& operator=(const Group& other) = default;
	Group(const Group&) = default;
	Group(Group&&) noexcept = default;
	~Group() override = default;

	void Draw() override {}
	void PostDraw() override;
	void Begin() override;
	void End() override;

	void Serialize(std::string& content) const override;

	std::string GetTypeName() const override { return "Group"; }
};
