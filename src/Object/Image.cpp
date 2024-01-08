#include "Object/Image.h"

#include <nfd.hpp>

#include "ImageLoader.h"

struct Filter
{
	std::string name;
	// ex : "Text file"
	std::string spec;
	// ex : "txt"
};

static std::string OpenFileExplorer(const std::vector<Filter>& filters);

void Image::Initialize()
{
	LoadImageFromExplorer();
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

		p_size = m_size;
	}
}

void Image::Serialize(std::string& content) const
{

}

static std::string OpenFileExplorer(const std::vector<Filter>& filters)
{
	std::string resultString = "";

	// initialize NFD
	NFD::Guard nfdGuard;

	// auto-freeing memory
	NFD::UniquePath outPath;

	const size_t count = filters.size();
	// prepare filters for the dialog
	std::vector<nfdfilteritem_t> filterItems(count);

	for (size_t i = 0; i < count; i++)
	{
		filterItems[i].name = filters[i].name.c_str();
		filterItems[i].spec = filters[i].spec.c_str();
	}

	// show the dialog
	const nfdresult_t result = NFD::OpenDialog(outPath, filterItems.data(), static_cast<uint32_t>(count));
	if (result == NFD_OKAY) {
		resultString = std::string(outPath.get());
	}
	else if (result == NFD_CANCEL) {
	}
	else {
	}

	// NFD::Guard will automatically quit NFD.
	return resultString;
}