#include "Object/Image.h"

#include "ImageLoader.h"
#include "Editor.h"

void Image::Initialize()
{
	//LoadImageFromExplorer();
}

void Image::Draw()
{
	ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(m_id)), p_size);
}

void Image::DisplayOnInspector()
{
	if (ImGui::Button("Set Image"))
	{
		LoadImageFromExplorer();
	}
	ImGui::SameLine();
	ImGui::TextUnformatted(m_imagePath.c_str());
}

void Image::LoadImageFromExplorer()
{
	const std::vector<Filter> filters = { { "Image", "png\0jpeg\0jpg" } };
	if (const auto filePath = OpenFileExplorer(filters); !filePath.empty())
	{
		LoadTexture(filePath);
	}
}

void Image::LoadTexture(const std::string filePath, bool setSizeToImageSize /*= true*/)
{
	m_imagePath = filePath;
	int numColCh;
	const auto bytes = ImageLoader::Load(m_imagePath.c_str(), &m_size.x, &m_size.y, &numColCh, 4);

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	ImageLoader::ImageFree(bytes);

	if (setSizeToImageSize)
		p_size = m_size;
}

void Image::Serialize(std::string& content) const
{
	content += "ImGui::Image(\"" + m_imagePath + "\", ImVec2(" + std::to_string(m_size.x) + ", " + std::to_string(m_size.y) + "));\n";
	SerializeChildren(content);
}

void Image::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::KEY << "Image Path" << Pair::VALUE << m_imagePath;
}

void Image::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_imagePath = parser["Image Path"].As<std::string>();
	LoadTexture(m_imagePath, false);
}
