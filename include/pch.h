#pragma once
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

// Galaxy Headers
#define IMGUI_IMPLEMENTATION
#include <galaxymath/Maths.h>
using namespace GALAXY;

#include <glad/glad.h>

// Libs Headers
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

#define EXTRA_CPPSERIALIZER_SERIALIZER \
template<typename T>\
CppSer::Serializer& operator<<(const Vec2<T>& value)\
{\
	const std::string stringValue = value.ToString();\
	*this << stringValue.c_str();\
	return *this;\
}\
\
template<typename T>\
CppSer::Serializer& operator<<(const Vec3<T>& value)\
{\
	const std::string stringValue = value.ToString();\
	*this << stringValue.c_str();\
	return *this;\
}\
\
template<typename T>\
CppSer::Serializer& operator<<(const Vec4<T>& value)\
{\
	const std::string stringValue = value.ToString();\
	*this << stringValue.c_str();\
	return *this;\
}\

#define EXTRA_CPPSERIALIZER_PARSER \
inline Math::Vec2f As() const\
{\
	return Math::Vec2f(m_content); \
}\

#include <cpp_serializer/CppSerializer.h>