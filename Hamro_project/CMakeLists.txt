cmake_minimum_required(VERSION 3.5)
project(Hamro_project VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



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
set(CMAKE_PREFIX_PATH "/home/sujan/devtools/vcpkg/installed/x64-linux/share")

# Create the executable with all source files
add_executable(Hamro_project ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(cpr CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(Hamro_project PRIVATE fmt::fmt)
target_link_libraries(Hamro_project PRIVATE cpr::cpr)
