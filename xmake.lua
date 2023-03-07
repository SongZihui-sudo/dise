add_rules("mode.debug", "mode.release")

includes("./src/parser/xmake.lua")
includes("./src/log/xmake.lua")

add_requires("tinyxml")

target("dise")
    set_kind("binary")
    add_files("src/*.cpp")
target_end()
