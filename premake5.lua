workspace "OpenGlTest"
   architecture "x64"

   configurations {
      "Debug",
      "Release"
   }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "Engine"
   location "Engine"
   kind "SharedLib"

   language "C++"
   cppdialect "C++17"

   targetdir("bin/".. outputdir .. "/%{prj.name}")
   objdir("bin-int/".. outputdir .. "/%{prj.name}")

   files {
      "%{prj.name}/src/*/**.h",
      "%{prj.name}/src/*/**.cpp",
   }

   includedirs {
      "%{prj.name}/src",
   }


   filter "system:linux"
      buildoptions { "-std=c++17" } 
      -- libdirs { "vendor/" }
      links { "glfw", "GL", "X11", "pthread", "Xrandr", "Xi", "dl", "GLEW", "assimp" } 

      defines {
         "PLATFORM_LINUX"
      }

      postbuildcommands {
         ("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
         ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/Engine")
      }

      staticruntime "On"

   filter "configurations:Debug"
      defines "ENGINE_DEBUG"
      symbols "On"

   filter "configurations:Release"
      defines "ENGINE_RELEASE"
      optimize "On"


project "Sandbox"
   location "Sandbox"
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
      "Engine/src"
   }

   filter "system:linux"
      buildoptions { "-std=c++17" } 
      -- libdirs { "vendor/" }
      links { "Engine",  "glfw", "GL", "X11", "pthread", "Xrandr", "Xi", "dl", "GLEW", "assimp" } 

      defines {
         "PLATFORM_LINUX"
      }

      staticruntime "On"

   filter "configurations:Debug"
      defines "GAME_DEBUG"
      symbols "On"

   filter "configurations:Release"
      defines "GAME_RELEASE"
      optimize "On"
