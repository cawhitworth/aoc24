add_executable(day13
    main.cc
    day13.cc)

target_link_libraries(day13 PRIVATE helper)
target_include_directories(day13 PUBLIC ../lib/helper)

add_executable(day13_tests
    day13.cc
    tests.cc
    )

target_link_libraries(day13_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day13_tests PUBLIC ../lib/helper)

target_compile_features(day13 PRIVATE cxx_std_20)
target_compile_features(day13_tests PRIVATE cxx_std_20)

catch_discover_tests(day13_tests)