group "external"

project "lodepng"
    location "lodepng"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("%{prj.location}/.build/bin/%{output_dir}/")
	objdir("%{prj.location}/.build/obj/%{output_dir}/")

    files {
		"%{prj.location}/lodepng.cpp",
        "%{prj.location}/lodepng.h"
	}
    includedirs {
        "%{prj.location}"
    }

group ""
