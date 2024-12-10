add_executable(day9
    main.cc
    day9.cc)

target_link_libraries(day9 PRIVATE helper)
target_include_directories(day9 PUBLIC ../lib/helper)

add_executable(day9_tests
    day9.cc
    tests.cc
    )

target_link_libraries(day9_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day9_tests PUBLIC ../lib/helper)

target_compile_features(day9 PRIVATE cxx_std_20)
target_compile_features(day9_tests PRIVATE cxx_std_20)

catch_discover_tests(day9_tests)