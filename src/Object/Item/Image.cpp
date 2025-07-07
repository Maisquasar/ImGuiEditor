#include "Object/Item/Image.h"

#include "ImageLoader.h"
#include "Editor.h"

Image::~Image()
{
	if (m_id != 0)
		glDeleteTextures(1, &m_id);
}

void Image::PostInitialize()
{
	if (m_imagePath.empty())
		LoadImageFromExplorer();
}

void Image::Draw()
{
	if (!m_isAButton)
		ImGui::Image(m_id, p_size);
	else
		ImGui::ImageButton("##", m_id, p_size);
}

void Image::DisplayOnInspector()
{
	if (ImGui::Button("Set Image"))
	{
		LoadImageFromExplorer();
	}
	ImGui::SameLine();
	ImGui::TextUnformatted(m_imagePath.c_str());
	
	ImGui::Checkbox("Is a button", &m_isAButton);
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

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	ImageLoader::ImageFree(bytes);

	if (setSizeToImageSize)
		p_size = m_size;
}

void Image::Serialize(std::string& content) const
{
	if (!m_isAButton)
		content += "ImGui::Image(0, ImVec2(" + std::to_string(p_size.x) + ", " + std::to_string(p_size.y) + ")); // Image path : " + m_imagePath + "\n";
	else
		content += "ImGui::ImageButton(0, ImVec2(" + std::to_string(p_size.x) + ", " + std::to_string(p_size.y) + ")); // Image path : " + m_imagePath + "\n";
	SerializeChildren(content);
}

void Image::Serialize(Serializer& serializer) const
{
	Object::Serialize(serializer);

	serializer << Pair::Key << "Image Path" << Pair::Value << m_imagePath;
	serializer << Pair::Key << "IsAButton" << Pair::Value << m_isAButton;
}

void Image::Deserialize(Parser& parser)
{
	Object::Deserialize(parser);

	m_imagePath = parser["Image Path"].As<std::string>();
	LoadTexture(m_imagePath, false);
	m_isAButton = parser["IsAButton"].As<bool>();
}
