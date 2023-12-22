---@diagnostic disable: lowercase-global, undefined-global

require "ninja"

workspace "Mythos"
    configurations {"release", "debug"}
    targetdir "build"
    architecture "x86_64"
    flags "MultiProcessorCompile"

outputdir = "%{cfg.buildcfg}"

project "GLFW"
	kind "StaticLib"
    systemversion "latest"
	language "C"
	staticruntime "off"
	warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"./vendor/glfw/include/GLFW/glfw3.h",
		"./vendor/glfw/include/GLFW/glfw3native.h",
		"./vendor/glfw/src/**.h",
        "./vendor/glfw/src/**.c"
	}

	defines 
	{ 
		"_CRT_SECURE_NO_WARNINGS"
	}

    links 
    {
        "gdi32"
    }
    
	filter "configurations:debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:release"
		runtime "Release"
		optimize "speed"

    filter "system:linux"
        pic "On"
        defines "_GLFW_X11"

    filter "system:windows"
        defines "_GLFW_WIN32"

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

    includedirs
    {
        "./vendor/glm"
    }

    links
    {
        "glfw"
    }

    filter "configurations:debug"
        defines "DEBUG"
