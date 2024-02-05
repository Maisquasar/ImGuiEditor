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
add_requires("galaxymath ~1.2")
add_requires("cpp_serializer")
add_requires("imgui v1.89.9-docking", { configs = { glfw_opengl3 = true } })
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

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

