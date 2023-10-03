set_project("EasyMusic")

set_xmakever("2.8.3")

set_allowedplats("windows")
set_allowedmodes("debug", "release")

set_languages("c++20")

set_warnings("all")
add_rules("mode.debug", "mode.release")

set_encodings("source:utf-8")

add_requires("stb", "cpr", "yyjson")

if is_mode("release") and is_plat("windows") then
    add_requires("vc-ltl5")
end

target("EasyMusic")
    set_kind("binary")
    add_files("*.cpp")

    if is_plat("windows") then
        add_syslinks("gdi32", "dwmapi")
    end

    add_packages("stb", "cpr", "yyjson")
    if is_mode("release") and is_plat("windows") then
        add_packages("vc-ltl5")
    end