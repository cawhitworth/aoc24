add_executable(day7
    main.cc
    day7.cc)

target_link_libraries(day7 PRIVATE helper)
target_include_directories(day7 PUBLIC ../lib/helper)

add_executable(day7_tests
    day7.cc
    tests.cc
    )

target_link_libraries(day7_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day7_tests PUBLIC ../lib/helper)

target_compile_features(day7 PRIVATE cxx_std_20)
target_compile_features(day7_tests PRIVATE cxx_std_20)

catch_discover_tests(day7_tests)