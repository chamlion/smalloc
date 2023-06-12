add_executable(
    benchtest
    bench.cpp
)

target_include_directories(
    benchtest
    PRIVATE
    ../lib/include
    ../lib/tlsf
)

target_link_libraries(
    benchtest
    PRIVATE
    smalloc
    benchmark
)


add_executable(
    test
    test.cpp
)

target_include_directories(
    test
    PRIVATE
    ../lib/include
    ../lib/tlsf
)

target_link_libraries(
    test
    PRIVATE
    smalloc
)