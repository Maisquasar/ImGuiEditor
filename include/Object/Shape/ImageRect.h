#pragma once
#include "Object/IObject.h"

class ImageRect : public ShapeObject<ImageRect>
{
public:
	ImageRect() = default;
	ImageRect& operator=(const ImageRect& other) = default;
	ImageRect(const ImageRect&) = default;
	ImageRect(ImageRect&&) noexcept = default;
	~ImageRect() override = default;

	void Initialize() override;
	void PostInitialize() override;
	void Draw() override;

	void DisplayOnInspector() override;

	std::string GetTypeName() const override { return "ImageRect"; }
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	void LoadImageFromExplorer();
	void LoadTexture(const std::string& filePath, bool setSizeToImageSize = true);
private:
	uint32_t m_id = -1;
	std::string m_imagePath;
	Vec2i m_imageSize;

	Vec4f m_color = Vec4f(1);
	float m_rounding = 0.0f;

};