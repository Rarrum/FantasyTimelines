add_rules("mode.debug", "mode.release")

set_policy("build.warning", true)
set_warnings("all")

if is_mode("debug") then
    set_symbols("debug")
    add_defines("DEBUG")
    set_optimize("none")
end

--if is_mode("release") then
--    set_symbols("debug")
--end

add_requires("nlohmann_json")
add_requires("qt6widgets")

target("FantasyTimelines")
    set_languages("cxx23")
    set_policy("build.c++.modules", true)
    set_exceptions("cxx")
    add_packages("nlohmann_json")
    add_rules("qt.widgetapp")

    add_headerfiles("src/**.h")
    add_files("src/**.cpp")
    add_files("src/**.mpp")
    add_files("src/**.ixx")

