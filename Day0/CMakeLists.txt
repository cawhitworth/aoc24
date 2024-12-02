add_executable(day0
    main.cc
    day0.cc)

target_link_libraries(day0 PRIVATE helper)
target_include_directories(day0 PUBLIC ../lib/helper)

add_executable(day0_tests
    day0.cc
    tests.cc
    )

target_link_libraries(day0_tests PRIVATE Catch2::Catch2WithMain helper)
target_include_directories(day0_tests PUBLIC ../lib/helper)

target_compile_features(day0 PRIVATE cxx_std_20)
target_compile_features(day0_tests PRIVATE cxx_std_20)

catch_discover_tests(day0_tests)