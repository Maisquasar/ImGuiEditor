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

#include "cpp_serializer/CppSerializer.h"
using namespace CppSer;

#include <glad/glad.h>

// Libs Headers
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>
