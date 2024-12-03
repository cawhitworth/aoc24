add_executable(day2
    main.cc
    day2.cc)

target_link_libraries(day2 PRIVATE helper)
target_include_directories(day2 PUBLIC ../lib/helper)

add_executable(day2_tests
    day2.cc
    tests.cc
    )

target_link_libraries(day2_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day2_tests PUBLIC ../lib/helper)

target_compile_features(day2 PRIVATE cxx_std_20)
target_compile_features(day2_tests PRIVATE cxx_std_20)

catch_discover_tests(day2_tests)