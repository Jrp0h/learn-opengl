workspace "OpenGlTest"
   architecture "x64"

   configurations {
      "Debug",
      "Release"
   }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


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
   }


   filter "system:linux"
      buildoptions { "-std=c++17" } 
      libdirs { "vendor/" }
      links { "glfw", "GL", "X11", "pthread", "Xrandr", "Xi", "dl", "GLEW" } 

      defines {
         "PLATFORM_LINUX"
      }

      staticruntime "On"

   filter "configurations:Debug"
      defines "_DEBUG"
      symbols "On"

   filter "configurations:Release"
      defines "_RELEASE"
      optimize "On"

