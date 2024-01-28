#include "Object/Shape/ImageRect.h"

#include "Editor.h"
#include "ImageLoader.h"

void ImageRect::Initialize()
{
}

void ImageRect::PostInitialize()
{
	if (m_imagePath.empty()) {
		LoadImageFromExplorer();
		p_position = p_size / 2;
	}
}

void ImageRect::Draw()
{
	ImGui::GetWindowDrawList()->AddImageRounded(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(m_id)), 
		GetMin(), GetMax(), ImVec2(0, 0), ImVec2(1, 1), 
		ImGui::ColorConvertFloat4ToU32(m_color), m_rounding, p_flags);
}

void ImageRect::DisplayOnInspector()
{
	if (ImGui::Button("Set Image"))
	{
		LoadImageFromExplorer();
	}
	ImGui::SameLine();
	ImGui::TextUnformatted(m_imagePath.c_str());

	ImGui::ColorEdit4("Color", &m_color.x, ImGuiColorEditFlags_NoInputs);
	ImGui::DragFloat("Rounding", &m_rounding);

	ShapeObject::DisplayOnInspector();
}

void ImageRect::Serialize(std::string& content) const
{
	content += "ImGui::GetWindowDrawList()->AddImageRounded(";
	content += "0, ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMin().x";

	const float minSizeX = p_position.x - p_size.x / 2;
	if (minSizeX != 0.0f)
	{
		content += " + " + std::to_string(minSizeX);
	}
	content += ", \n";
	content += "\tImGui::GetWindowPos().y + ImGui::GetWindowContentRegionMin().y";
	const float minSizeY = p_position.y - p_size.y / 2;
	if (minSizeY != 0.0f)
	{
		content += " + " + std::to_string(minSizeY);
	}
	content += "), \n";

	content += "\tImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMin().x";
	const float maxSizeX = p_position.x + p_size.x / 2;
	if (maxSizeX != 0.0f)
	{
		content += " + " + std::to_string(maxSizeX);
	}
	content += ", \n";
	content += "\tImGui::GetWindowPos().y + ImGui::GetWindowContentRegionMin().y";
	const float maxSizeY = p_position.y + p_size.y / 2;
	if (maxSizeY != 0.0f)
	{
		content += " + " + std::to_string(maxSizeY);
	}
	content += "), \n";

	content += "ImVec2(0, 0), ImVec2(1, 1), " + std::to_string(ImGui::ColorConvertFloat4ToU32(m_color))
	+ ", " + std::to_string(m_rounding) + ", " + std::to_string(p_flags) + ");\n";

}

void ImageRect::Serialize(Serializer& serializer) const
{
	ShapeObject::Serialize(serializer);
	serializer << Pair::KEY << "ImagePath" << Pair::VALUE << m_imagePath;
	serializer << Pair::KEY << "Color" << Pair::VALUE << m_color;
	serializer << Pair::KEY << "Rounding" << Pair::VALUE << m_rounding;
}

void ImageRect::Deserialize(Parser& parser)
{
	ShapeObject::Deserialize(parser);
	m_imagePath = parser["ImagePath"].As<std::string>();
	LoadTexture(m_imagePath, false);
	m_color = parser["Color"].As<Vec4f>();
	m_rounding = parser["Rounding"].As<float>();
}

void ImageRect::LoadImageFromExplorer()
{
	const std::vector<Filter> filters = { { "Image", "png\0jpeg\0jpg" } };
	if (const auto filePath = OpenFileExplorer(filters); !filePath.empty())
	{
		LoadTexture(filePath);
	}
}

void ImageRect::LoadTexture(const std::string& filePath, const bool setSizeToImageSize /*= true*/)
{
	m_imagePath = filePath;
	int numColCh;
	const auto bytes = ImageLoader::Load(m_imagePath.c_str(), &m_imageSize.x, &m_imageSize.y, &numColCh, 4);

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_imageSize.x, m_imageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	ImageLoader::ImageFree(bytes);

	if (setSizeToImageSize)
		p_size = m_imageSize;
}

