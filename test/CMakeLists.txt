find_package(GTest REQUIRED)

add_executable(test_core
    main.cpp
    core.cpp
)

target_include_directories(test_core
    PRIVATE
        ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(test_core ${GTEST_LIBRARIES} pthread core)
install(TARGETS test_core RUNTIME DESTINATION bin)
