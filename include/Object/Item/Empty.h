#pragma once
#include "Object/IObject.h"

class Empty : public ItemObject<Empty>
{
public:
	Empty() = default;
	Empty& operator=(const Empty& other) = default;
	Empty(const Empty&) = default;
	Empty(Empty&&) noexcept = default;
	~Empty() override = default;

	void Draw() override { }
	void Serialize(std::string& content) const override;

	std::string GetTypeName() const override { return "Empty"; }
private:

};