#pragma once
#include "Object/IObject.h"

class ChildObject : public IObject<ChildObject>
{
public:
	void Initialize() override;
	void PostDraw() override {}
	bool Begin() override;
	void End() override;
	void PostEnd() override;
	void DisplayOnInspector() override;

	void Draw() override {}
	std::string GetTypeName() const override;

	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;
private:
	bool m_hasBorder = true;
};