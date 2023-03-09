add_rules("mode.debug", "mode.release")

includes("./src/parser")
includes("./src/log")
includes("./src/common")
includes("./src/analyzer")
includes("./src/printer")

add_requires("tinyxml")

target("dise")
    set_kind("binary")
    add_files("src/*.cpp")
target_end()
