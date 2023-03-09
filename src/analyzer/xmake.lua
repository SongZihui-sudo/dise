add_rules("mode.debug", "mode.release")

add_defines("_analyzer_")

add_packages("tinyxml")

target("analyzer")
    set_kind("static")
    add_deps("parser")
    add_files("./*.cpp")
target_end()

target("analyzer_test")
    add_deps("analyzer")
    set_kind("binary")
    add_files("./test/*.cpp")
target_end()
