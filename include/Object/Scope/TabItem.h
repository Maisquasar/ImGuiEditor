#pragma once
#include "Object/IObject.h"

class TabItem : public ScopeObject<TabItem>
{
public:
	TabItem() = default;
	TabItem& operator=(const TabItem& other) = default;
	TabItem(const TabItem&) = default;
	TabItem(TabItem&&) noexcept = default;
	~TabItem() override = default;

	void Initialize() override;
	bool Begin() override;
	void End() override;
	void PostEnd() override;

	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "TabItem"; }
private:
	int m_randomValue;
};
