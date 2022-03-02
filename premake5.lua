workspace "RELang"
    architecture "x64"
    targetdir "build"

    configurations
    {
        "Release",
        "Debug"
    }

    startproject "RELang-Interpreter"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "RELang-Common"
    location "RELang-Common"
    kind "StaticLib"
    staticruntime "off"
    language "C"
    cdialect "C11"

    targetdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build-obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Common/**.c",
        "%{prj.name}/Common/**.h"
    }

    includedirs
    {
        "%{prj.name}/"
    }

    filter "system:linux"
        systemversion "latest"
        pic "on"

    filter "configurations:Release"
        defines
        {
            "RE_RELEASE"
        }

        optimize "on"

    filter "configurations:Debug"
        defines
        {
            "RE_DEBUG"
        }

        symbols "on"

project "RELang-Interpreter"
    location "RELang-Interpreter"
    kind "ConsoleApp"
    language "C"
    cdialect "C11"

    targetdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build-obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.h"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{wks.location}/RELang-Common"
    }

    links
    {
        "RELang-Common"
    }

    filter "system:linux"
        systemversion "latest"
        pic "on"

    filter "configurations:Release"
        defines
        {
            "RE_RELEASE"
        }

        optimize "on"

    filter "configurations:Debug"
        defines
        {
            "RE_DEBUG"
        }

        symbols "on"

project "RELang-Compiler"
    location "RELang-Compiler"
    kind "ConsoleApp"
    language "C"
    cdialect "C11"

    targetdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/build-obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.h"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{wks.location}/RELang-Common"
    }

    links
    {
        "RELang-Common"
    }

    filter "system:linux"
        systemversion "latest"
        pic "on"

    filter "configurations:Release"
        defines
        {
            "RE_RELEASE"
        }

        optimize "on"

    filter "configurations:Debug"
        defines
        {
            "RE_DEBUG"
        }

        symbols "on"