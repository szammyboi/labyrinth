---@diagnostic disable: lowercase-global, undefined-global

require "ninja"

workspace "Mythos"
    configurations {"release", "debug"}
    targetdir "build"
    architecture "x86_64"
    flags "MultiProcessorCompile"

outputdir = "%{cfg.buildcfg}"

--include "vendor/glfw-premake"

project "Labyrinth"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("build/bin/" .. outputdir)
    objdir ("build/bin-int/" .. outputdir)

    symbols "on"
    buildoptions {"-Werror", "-Wuninitialized", "-Wno-narrowing"}
    files 
    { 
        "src/**.h",
        "src/**.cpp"
    }

    filter "configurations:debug"
        defines "DEBUG"
