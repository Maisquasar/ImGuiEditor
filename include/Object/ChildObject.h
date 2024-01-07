#pragma once
#include "Object/IObject.h"

class ChildObject : public IObject<ChildObject>
{
public:
	void Initialize() override;
	void PostDraw() override {}
	void Begin() override;
	void End() override;

	void Draw() override {}
	std::string GetTypeName() const override;

	void Serialize(std::string& content) const override;
private:
	bool m_hasBorder = true;
};