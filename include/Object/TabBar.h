#pragma once
#include "Object/IObject.h"

class TabBar : public IObject<TabBar>
{
public:
	TabBar() = default;
	TabBar& operator=(const TabBar& other) = default;
	TabBar(const TabBar&) = default;
	TabBar(TabBar&&) noexcept = default;
	~TabBar() override = default;

	void Draw() override {}
	void PostDraw() override;
	bool Begin() override;
	void End() override;

	void DisplayOnInspector() override {}

	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "TabBar"; }

};
