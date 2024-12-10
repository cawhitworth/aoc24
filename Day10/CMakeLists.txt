add_executable(day10
    main.cc
    day10.cc)

target_link_libraries(day10 PRIVATE helper)
target_include_directories(day10 PUBLIC ../lib/helper)

add_executable(day10_tests
    day10.cc
    tests.cc
    )

target_link_libraries(day10_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day10_tests PUBLIC ../lib/helper)

target_compile_features(day10 PRIVATE cxx_std_20)
target_compile_features(day10_tests PRIVATE cxx_std_20)

catch_discover_tests(day10_tests)