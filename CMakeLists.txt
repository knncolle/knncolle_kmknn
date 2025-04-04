cmake_minimum_required(VERSION 3.14)

project(knncolle_kmknn
    VERSION 0.1.0
    DESCRIPTION "knncolle bindings for KMKNN"
    LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Library
add_library(knncolle_kmknn INTERFACE)
add_library(knncolle::knncolle_kmknn ALIAS knncolle_kmknn)

target_include_directories(knncolle_kmknn INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/knncolle_kmknn>)
target_compile_features(knncolle_kmknn INTERFACE cxx_std_17)

# Dependencies
option(KNNCOLLE_KMKNN_FETCH_EXTERN "Automatically fetch knncolle_kmknn's external dependencies." ON)
if(KNNCOLLE_KMKNN_FETCH_EXTERN)
    add_subdirectory(extern)
else()
    find_package(knncolle_knncolle CONFIG REQUIRED)
    find_package(ltla_kmeans CONFIG REQUIRED)
endif()

target_link_libraries(knncolle_kmknn INTERFACE knncolle::knncolle ltla::kmeans)

# Tests
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(KNNCOLLE_KMKNN_TESTS "Build knncolle_kmknn's test suite." ON)
else()
    option(KNNCOLLE_KMKNN_TESTS "Build knncolle_kmknn's test suite." OFF)
endif()

if(KNNCOLLE_KMKNN_TESTS)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif() 
endif()

# Install
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/knncolle_kmknn)

install(TARGETS knncolle_kmknn
    EXPORT knncolle_kmknnTargets)

install(EXPORT knncolle_kmknnTargets
    FILE knncolle_knncolle_kmknnTargets.cmake
    NAMESPACE knncolle::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/knncolle_knncolle_kmknn)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/knncolle_knncolle_kmknnConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/knncolle_knncolle_kmknn)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/knncolle_knncolle_kmknnConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/knncolle_knncolle_kmknnConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/knncolle_knncolle_kmknnConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/knncolle_knncolle_kmknn)
