add_executable(day1
    main.cc
    day1.cc)

target_link_libraries(day1 PRIVATE helper)
target_include_directories(day1 PUBLIC ../lib/helper)

add_executable(day1_tests
    day1.cc
    tests.cc
    )

target_link_libraries(day1_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day1_tests PUBLIC ../lib/helper)

target_compile_features(day1 PRIVATE cxx_std_20)
target_compile_features(day1_tests PRIVATE cxx_std_20)

catch_discover_tests(day1_tests)