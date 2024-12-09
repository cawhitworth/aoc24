add_executable(day8
    main.cc
    day8.cc)

target_link_libraries(day8 PRIVATE helper)
target_include_directories(day8 PUBLIC ../lib/helper)

add_executable(day8_tests
    day8.cc
    tests.cc
    )

target_link_libraries(day8_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day8_tests PUBLIC ../lib/helper)

target_compile_features(day8 PRIVATE cxx_std_20)
target_compile_features(day8_tests PRIVATE cxx_std_20)

catch_discover_tests(day8_tests)