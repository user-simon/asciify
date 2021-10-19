workspace "asciify"
	architecture "x64"
	
	configurations {
		"debug",
		"release"
	}

output_dir = "%{cfg.buildcfg}_%{cfg.system}"

project "asciify"
	location "src"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
    
	targetdir(".build/bin/%{output_dir}/")
	objdir(".build/obj/%{output_dir}/")

	files {
		"%{prj.location}/**.cpp",
        "%{prj.location}/**.h",
	}
	includedirs {
		"external"
	}
	libdirs {
		"external/lodepng/.build/%{output_dir}"
	}
	links {
		"lodepng"
	}

include "external"
