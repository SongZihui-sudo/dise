add_rules("mode.debug", "mode.release")

add_packages("tinyxml")

target("parser")
    add_deps("Logger")
    set_kind("shared")
    add_files("./*.cpp")
target_end()

target("parser_test")
    add_deps("parser")
    set_kind("binary")
    add_files("./*.cpp")
target_end()


