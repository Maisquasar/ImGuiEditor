add_rules("mode.release", "mode.debug")
add_rules("plugin.vsxmake.autoupdate")

if is_plat("windows") then
    set_runtimes(is_mode("debug") and "MDd" or "MD")
    if is_mode("debug") and is_kind("binary") then
        if is_host("windows") then
            add_cxflags("/ZI", {force = true})
            add_ldflags("/INCREMENTAL", {force = true})
        end
    end
end

if is_mode("release") then
    add_ldflags("-mwindows", {force = true}) -- This flag is for MinGW/GCC
    add_cxflags("-DWINDOW_APP", {force = true}) -- Define a preprocessor macro if needed
end
-- Custom repo
add_repositories("galaxy-repo https://github.com/GalaxyEngine/xmake-repo")

-- Packages
add_requires("galaxymath")
add_requires("cpp_serializer")
add_requires("imgui v1.92.0-docking", { configs = { glfw_opengl3 = true } })
add_requires("glad")
add_requires("stb")
add_requires("nativefiledialog-extended")

set_languages("c++20")
set_rundir("$(projectdir)")

target("ImGuiEditor")
    set_symbols("debug")
    set_kind("binary")

    add_includedirs("include")
    add_headerfiles("include/**.h")
    add_files("src/**.cpp")
    add_files("icons/ImGuiEditor.rc") -- Add this line to include the resource file
    set_pcxxheader("include/pch.h")

    add_packages("galaxymath")
    add_packages("cpp_serializer")
    add_packages("glfw")
    add_packages("imgui")
    add_packages("glad")
    add_packages("stb")
    add_packages("nativefiledialog-extended")
target_end()

