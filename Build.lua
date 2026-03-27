project "N503.CppWin32.Syntax"
    kind          "Utility" -- ConsoleApp WindowedApp SharedLib StaticLib
    language      "C++"
    cppdialect    "C++20"
    staticruntime "off"
    characterset  "Unicode"

    pchheader "Pch.hpp"
    pchsource "Source/Pch.cpp"

    targetdir  ("%{wks.location}/Binaries/" .. OutputDir .. "/")
    objdir     ("%{wks.location}/Binaries-Intermediates/" .. OutputDir .. "/%{prj.name}")

    vsprops
    {
        -- VcpkgTriplet = "x64-windows-static",
        -- VcpkgEnabled = "true",
        PublicIncludeDirectories = "Include",
    }

    nuget
    {
        -- "Microsoft.Windows.ImplementationLibrary:<verion here...>",
    }

    files
    {
        "Include/**.hpp",
    }

    includedirs
    {
        "Include",
    }

    links
    {
        "N503.CppWin32.Memory", "N503.CppWin32.Diagnostics",
    }

    prebuildcommands
    {
    }

    postbuildcommands
    {
    }
