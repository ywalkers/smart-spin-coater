file(GLOB_RECURSE srcs "custom/*.c" "generated/*.c")
idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS "custom" "generated"
                       REQUIRES lvgl)