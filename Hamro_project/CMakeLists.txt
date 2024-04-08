cmake_minimum_required(VERSION 3.5)
project(Hamro_project VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



foreach(flag_var
    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
    
    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif()
endforeach()


# List of all source files 
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
)

# Include directory for RapidJSON
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rapidjson)
set(CMAKE_PREFIX_PATH "C:/vcpkg/installed/x64-windows-static/share/")



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
