add_executable(day3
    main.cc
    day3.cc)

target_link_libraries(day3 PRIVATE helper)
target_include_directories(day3 PUBLIC ../lib/helper)

add_executable(day3_tests
    day3.cc
    tests.cc
    )

target_link_libraries(day3_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day3_tests PUBLIC ../lib/helper)

target_compile_features(day3 PRIVATE cxx_std_20)
target_compile_features(day3_tests PRIVATE cxx_std_20)

catch_discover_tests(day3_tests)