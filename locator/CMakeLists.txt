set(BINARY ${CMAKE_PROJECT_NAME})
set(SOURCE_F locator.cpp  locator.hpp subscriber.hpp cell.hpp trigger.hpp)
add_library(${BINARY} STATIC ${SOURCE_F} )
target_link_libraries(${BINARY} nlohmann_json::nlohmann_json spdlog::spdlog)
