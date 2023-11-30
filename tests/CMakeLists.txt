set(BINARY ${CMAKE_PROJECT_NAME}_tst)
add_executable(${BINARY} main.cpp loc_test.cpp)
add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME} gtest gtest_main)
