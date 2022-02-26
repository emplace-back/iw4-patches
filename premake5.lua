workspace "iw4-patches"
    startproject "iw4-patches"
    location "build/"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}/"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}/"
    buildlog "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}.log"

    systemversion "latest"
    architecture "x86"
    characterset "mbcs"
    warnings "off"
    editandcontinue "off"
    staticruntime "on"

    disablewarnings {
        "4005",
        "4099",
        "5054",
        "26812"
    }
    
    includedirs {
        "src/",
    }

    buildoptions {
        "/Zm200",
        "/utf-8",
        "/std:c++latest",
    }

    flags {
        "shadowedvariables",
        "noincrementallink",
        "undefinedidentifiers",
        "multiprocessorcompile",
    }

    defines {
        "NOMINMAX",
        "WIN32_LEAN_AND_MEAN",
        "_CRT_SECURE_NO_WARNINGS",
    }

    platforms {
        "x86",
    }

    configurations {
        "debug",
        "release",
    }

    configuration "debug"
        defines {
             "DEBUG",
             "STEAM"
        }

        optimize "debug"
        runtime "debug"
        symbols "off"

        targetname "iw4-patches-debug"

    configuration "release"
        defines {
            "NDEBUG",
            "STEAM"
        }
        
        optimize "off"
        runtime "release"
        symbols "off"

        targetname "iw4-patches-release"

project "iw4-patches"
    kind "sharedlib"
    language "c++"
    
    files {
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
    }
    
	links {
        "detours.lib",
        "ws2_32.lib",
    }
    
    includedirs {
        "src/",
    }

    libdirs {
        "thirdparty/detours/lib/",
    }