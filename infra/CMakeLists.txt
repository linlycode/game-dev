set(SOURCES fmt.h fmt.cpp filepath.h filepath.cpp)

add_library(infra STATIC ${SOURCES})

target_sources(tests PRIVATE ${SOURCES} fmt_test.cpp)
