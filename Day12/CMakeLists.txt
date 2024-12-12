add_executable(day12
    main.cc
    day12.cc)

target_link_libraries(day12 PRIVATE helper)
target_include_directories(day12 PUBLIC ../lib/helper)

add_executable(day12_tests
    day12.cc
    tests.cc
    )

target_link_libraries(day12_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day12_tests PUBLIC ../lib/helper)

target_compile_features(day12 PRIVATE cxx_std_20)
target_compile_features(day12_tests PRIVATE cxx_std_20)

catch_discover_tests(day12_tests)