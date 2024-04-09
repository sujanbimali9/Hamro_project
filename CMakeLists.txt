cmake_minimum_required(VERSION 3.5)
project(Hamro_project VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# List all your source files here
set(SOURCES
    Login.cpp
    apis.cpp
    CartScreen.cpp
    Description.cpp
    HomeScreen.cpp
    Password.cpp
    Product.cpp
    ProductCart.cpp
    Screen.cpp
    User.cpp
)

# Include directory for RapidJSON
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rapidjson)

# Create the executable with all source files
add_executable(Hamro_project ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(cpr CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(Hamro_project PRIVATE fmt::fmt)
target_link_libraries(Hamro_project PRIVATE cpr::cpr)


if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(Hamro_project PRIVATE "-O3" "-DNDEBUG")
endif()


# add_custom_target(run
#     COMMAND ${PROJECT_NAME}
#     DEPENDS ${PROJECT_NAME}
#     WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
# )
