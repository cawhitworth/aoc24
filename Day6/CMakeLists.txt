add_executable(day6
    main.cc
    day6.cc)

target_link_libraries(day6 PRIVATE helper)
target_include_directories(day6 PUBLIC ../lib/helper)

add_executable(day6_tests
    day6.cc
    tests.cc
    )

target_link_libraries(day6_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day6_tests PUBLIC ../lib/helper)

target_compile_features(day6 PRIVATE cxx_std_20)
target_compile_features(day6_tests PRIVATE cxx_std_20)

catch_discover_tests(day6_tests)