#pragma once
#include "Object/IObject.h"

class ChildObject : public ScopeObject<ChildObject>
{
public:
	void Initialize() override;
	bool Begin() override;
	void End() override;
	void PostEnd() override;
	void DisplayOnInspector() override;

	std::string GetTypeName() const override;

	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;
private:
	bool m_hasBorder = true;
};