add_executable(day15
    main.cc
    day15.cc)

target_link_libraries(day15 PRIVATE helper)
target_include_directories(day15 PUBLIC ../lib/helper)

add_executable(day15_tests
    day15.cc
    tests.cc
    )

target_link_libraries(day15_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day15_tests PUBLIC ../lib/helper)

target_compile_features(day15 PRIVATE cxx_std_20)
target_compile_features(day15_tests PRIVATE cxx_std_20)

catch_discover_tests(day15_tests)