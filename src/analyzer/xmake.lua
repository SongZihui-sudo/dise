add_rules("mode.debug", "mode.release")

add_defines("_analyzer_")

target("analyzer")
    set_kind("shared")
    add_files("./*.cpp")
target_end()

target("analyzer_test")
    add_deps("analyzer")
    set_kind("binary")
    add_files("./*.cpp")
target_end()
