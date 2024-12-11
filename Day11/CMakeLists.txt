add_executable(day11
    main.cc
    day11.cc)

target_link_libraries(day11 PRIVATE helper)
target_include_directories(day11 PUBLIC ../lib/helper)

add_executable(day11_tests
    day11.cc
    tests.cc
    )

target_link_libraries(day11_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day11_tests PUBLIC ../lib/helper)

target_compile_features(day11 PRIVATE cxx_std_20)
target_compile_features(day11_tests PRIVATE cxx_std_20)

catch_discover_tests(day11_tests)