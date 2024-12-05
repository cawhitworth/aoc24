add_executable(day5
    main.cc
    day5.cc)

target_link_libraries(day5 PRIVATE helper)
target_include_directories(day5 PUBLIC ../lib/helper)

add_executable(day5_tests
    day5.cc
    tests.cc
    )

target_link_libraries(day5_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day5_tests PUBLIC ../lib/helper)

target_compile_features(day5 PRIVATE cxx_std_20)
target_compile_features(day5_tests PRIVATE cxx_std_20)

catch_discover_tests(day5_tests)