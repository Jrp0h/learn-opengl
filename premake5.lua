workspace "OpenGlTest"
   architecture "x64"

   configurations {
      "Debug",
      "Release"
   }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDirs = {}
IncludeDirs['glad'] = "OpenGLTest/vendor/glad/include"

include "OpenGLTest/vendor/glad"

project "OpenGLTest"
   location "OpenGLTest"
   kind "ConsoleApp"

   language "C++"
   cppdialect "C++17"

   targetdir("bin/".. outputdir .. "/%{prj.name}")
   objdir("bin-int/".. outputdir .. "/%{prj.name}")

   files {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp",
   }

   includedirs {
      "%{prj.name}/src",
      "%{IncludeDirs.glad}"
   }

   links {
      "glad"
   }

   filter "system:linux"
      buildoptions { "-std=c++17" } 
      links { "glfw", "GL", "X11", "pthread", "Xrandr", "Xi", "dl" } 

      defines {
         "PLATFORM_LINUX"
      }

      staticruntime "On"

   filter "configurations:Debug"
      defines "_DEBUG"
      -- symbols "On"

   filter "configurations:Release"
      defines "_RELEASE"
      optimize "On"

