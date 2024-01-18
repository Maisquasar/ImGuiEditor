#pragma once
#include "Object/IObject.h"


class MainMenuBar : public IObject<MainMenuBar>
{
public:
	MainMenuBar() = default;
	MainMenuBar& operator=(const MainMenuBar& other) = default;
	MainMenuBar(const MainMenuBar&) = default;
	MainMenuBar(MainMenuBar&&) noexcept = default;
	~MainMenuBar() override = default;

	void Initialize() override;
	void Draw() override {}
	bool Begin() override;
	void End() override;

	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "MainMenuBar"; }
};
