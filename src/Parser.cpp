#include "pch.h"
#include "Parser.h"

#define MAP_SEPARATOR_BEGIN " ------------- "
#define MAP_SEPARATOR_END " ============= "

#pragma region Serializer
Serializer::Serializer(const std::filesystem::path& path)
{
	m_filePath = path;
}

Serializer::~Serializer()
{
	if (!m_filePath.empty() && m_saveOnDestroy)
		CloseFile();
}

void Serializer::Create(const std::filesystem::path& path)
{
	m_filePath = path;
}

void Serializer::CloseFile() const
{
	auto file = std::ofstream(m_filePath);
	if (!file.is_open()) {
		std::cerr << ("File %s could'nt be create", m_filePath.string().c_str()) << std::endl;
		file.close();
	}
	file << m_content.str();
	file.close();
}

template<typename T> Serializer& Serializer::operator<<(const T& value)
{
	return *this;
}

template<typename T> Serializer& Serializer::operator<<(T* value)
{
	return *this;
}

template<> Serializer& Serializer::operator<<(const std::string& value)
{
	*this << value.c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const char& value)
{
	const std::string stringValue(1, value);
	*this << stringValue.c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const std::filesystem::path& value)
{
	*this << value.generic_string().c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const bool& value)
{
	const std::string stringValue = std::to_string(value);
	*this << stringValue.c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const float& value)
{
	const std::string stringValue = std::to_string(value);
	*this << stringValue.c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const int& value)
{
	const std::string stringValue = std::to_string(value);
	*this << stringValue.c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const unsigned long& value)
{
	const std::string stringValue = std::to_string(value);
	*this << stringValue.c_str();
	return *this;
}
template<> Serializer& Serializer::operator<<(const long long& value)
{
	const std::string stringValue = std::to_string(value);
	*this << stringValue.c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const unsigned long long& value)
{
	const std::string stringValue = std::to_string(value);
	*this << stringValue.c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const double& value)
{
	const std::string stringValue = std::to_string(value);
	*this << stringValue.c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const Quat& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const Mat4& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> Serializer& Serializer::operator<<(const Pair& value)
{
	SetCurrentType(value);
	return *this;
}

Serializer& Serializer::operator<<(const char* value)
{
	switch (m_currentType)
	{
	case Pair::KEY:
	{
		SetCurrentKey(value);
	}
	break;
	case Pair::VALUE:
	{
		SetCurrentValue(value);
		WriteLine();
	}
	break;
	case Pair::TITLE:
	{
		AddLine(value);
	}
	break;
	case Pair::BEGIN_MAP:
	{
		m_content << value << MAP_SEPARATOR_BEGIN << '\n';
	}
	break;
	case Pair::END_MAP:
	{
		m_content << value << MAP_SEPARATOR_END << '\n';
	}
	break;
	default:
		break;
	}
	return *this;
}

void Serializer::SetCurrentType(const Pair val)
{
	switch (val)
	{
	case Pair::BEGIN_TAB:
		PushTab();
		break;
	case Pair::END_TAB:
		PopTab();
		break;
	case Pair::BEGIN_MAP:
		m_currentType = val;
		m_content << m_tab << MAP_SEPARATOR_BEGIN;
		break;
	case Pair::END_MAP:
		m_currentType = val;
		m_content << m_tab << MAP_SEPARATOR_END;
		break;
	default:
		m_currentType = val;
		break;
	}
}

void Serializer::WriteLine()
{
	AddLine(m_currentPair.first, m_currentPair.second);
}
#pragma endregion

#pragma region Parser


Parser::Parser(const std::filesystem::path& path)
{
	ParseFile(path);
}

Parser::Parser(const std::string& content)
{
	ParseContent(content);
}

void Parser::ParseFile(const std::filesystem::path& path)
{
	auto file = std::fstream(path, std::ios::in);
	if (!file.is_open()) {
		file.close();
		m_fileOpen = false;
		return;
	}
	// Get file content
	const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	ParseContent(content);

	file.close();
	m_fileOpen = true;
}

void Parser::ParseContent(const std::string& content)
{
	std::stringstream ss(content);

	std::string line;
	std::unordered_map<std::string, StringSerializer>* currentMap = nullptr;

	while (std::getline(ss, line)) {
		if (line.find(MAP_SEPARATOR_BEGIN) != std::string::npos)
		{
			m_valueMap.emplace_back();
			currentMap = &m_valueMap.back();
		}

		if (const size_t pos = line.find("["); pos != std::string::npos)
		{
			std::string currentKey = line.substr(pos + 1);
			currentKey = currentKey.substr(0, currentKey.find_first_of(']'));
			std::string currentValue = line.substr(line.find_first_of(':') + 2);

			currentMap->insert({ currentKey, currentValue });
		}
	}
}

void Parser::PrintData()
{
	/*
	for (auto& maps : m_valueMap)
	{
		for (auto& [key, value] : maps)
		{
			std::cout << key << " : " << value << std::endl;
		}
		std::cout << "---------------------------" << std::endl;
	}
	*/
}

void Parser::NewDepth()
{
	m_currentDepth++;
}

StringSerializer Parser::operator[](const std::string& key)
{
	//ASSERT(m_valueMap.size() > m_currentDepth);
	//ASSERT(m_valueMap[m_currentDepth].contains(key));
	if (m_valueMap.size() <= m_currentDepth || !m_valueMap[m_currentDepth].contains(key))
		return {};

	return m_valueMap[m_currentDepth][key];
}

#pragma endregion

template <typename T>
T StringSerializer::As()
{
	// return static_cast<T>(m_content);
	std::cerr << "Error with parsing type as" << std::endl;
	return T();
}

template <>
std::string StringSerializer::As()
{
	return m_content;
}

template <>
float StringSerializer::As()
{
	try
	{
		return std::stof(m_content);
	}
	catch (...)
	{
		return 0.f;
	}
}

template <>
double StringSerializer::As()
{
	try
	{
		return std::stod(m_content);
	}
	catch (...)
	{
		return 0.0;
	}
}

template <>
unsigned long long StringSerializer::As()
{
	try
	{
		return std::stoull(m_content);
	}
	catch (...)
	{
		return -1;
	}
}

template <>
long long StringSerializer::As()
{
	try
	{
		return std::stoll(m_content);
	}
	catch (...)
	{
		return 0;
	}
}

template <>
unsigned long StringSerializer::As()
{
	try
	{
		return std::stoul(m_content);
	}
	catch (...)
	{
		return -1;
	}
}

template <>
int StringSerializer::As()
{
	try
	{
		return std::stoi(m_content);
	}
	catch (...)
	{
		return 0;
	}
}

template <>
bool StringSerializer::As()
{
	try
	{
		return std::stoi(m_content);
	}
	catch (...)
	{
		return 0;
	}
}

template <>
Vec2f StringSerializer::As()
{
	return { m_content };
}

template <>
Vec2<uint64_t> StringSerializer::As()
{
	return { m_content };
}

template <>
Vec3f StringSerializer::As()
{
	return { m_content };
}

template <>
Vec4f StringSerializer::As()
{
	return { m_content };
}

template <>
Quat StringSerializer::As()
{
	return { m_content };
}
