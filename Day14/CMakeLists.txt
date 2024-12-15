add_executable(day14
    main.cc
    day14.cc)

target_link_libraries(day14 PRIVATE helper)
target_include_directories(day14 PUBLIC ../lib/helper)

add_executable(day14_tests
    day14.cc
    tests.cc
    )

target_link_libraries(day14_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day14_tests PUBLIC ../lib/helper)

target_compile_features(day14 PRIVATE cxx_std_20)
target_compile_features(day14_tests PRIVATE cxx_std_20)

catch_discover_tests(day14_tests)