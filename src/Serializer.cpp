#include "Serializer.h"

#include <cpp_serializer/CppSerializer.h>

#include <galaxymath/Maths.h>


// --------------------------------------- Serializer ---------------------------------------

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Vec2f& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Vec3f& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Vec4f& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Vec2i& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Vec3i& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Vec4i& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Vec2<uint64_t>& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Vec3<uint64_t>& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Vec4<uint64_t>& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Quat& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const Mat4& value)
{
	const std::string stringValue = value.ToString();
	*this << stringValue.c_str();
	return *this;
}

template<> CppSer::Serializer& CppSer::Serializer::operator<<(const unsigned long& value)
{
	auto stringValue = std::to_string(value);
	*this << stringValue;
	return *this;
}
// --------------------------------------- Parser ---------------------------------------
template<>
uint32_t CppSer::StringSerializer::As() const
{
	try
	{
		return std::stoul(m_content);
	}
	catch (...)
	{
		return 0;
	}
}

template <>
Vec2f CppSer::StringSerializer::As() const
{
	return { m_content };
}

template <>
Vec2<uint64_t> CppSer::StringSerializer::As() const
{
	return { m_content };
}

template <>
Vec3f CppSer::StringSerializer::As() const
{
	return { m_content };
}

template <>
Vec4f CppSer::StringSerializer::As() const
{
	return { m_content };
}

template <>
Quat CppSer::StringSerializer::As() const
{
	return { m_content };
}