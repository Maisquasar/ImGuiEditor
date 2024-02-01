#pragma once
#include "Object/IObject.h"

class Image : public ItemObject<Image>
{
public:
	Image() = default;
	Image& operator=(const Image& other) = default;
	Image(const Image&) = default;
	Image(Image&&) noexcept = default;
	~Image() override;

	void PostInitialize() override;
	void Draw() override;
	void DisplayOnInspector() override;

	void LoadImageFromExplorer();

	void LoadTexture(const std::string filePath, bool setSizeToImageSize = true);

	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Image"; }
private:
	uint32_t m_id = -1;
	std::string m_imagePath;
	Vec2i m_size;

	bool m_isAButton = false;
};