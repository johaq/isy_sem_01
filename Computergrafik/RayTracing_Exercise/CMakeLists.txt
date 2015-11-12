project(RayTracing)
cmake_minimum_required(VERSION 2.6.4)


# set output paths
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})


# default to Release builds
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()


# try to find OpenMP for multicore parallelization
find_package(OpenMP)
if(WITH_OPENMP)
  if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    if(MSVC)
      add_definitions(/arch:SSE)
    endif(MSVC)
    set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} -fopenmp)
  endif()
endif()


# compiler flags
if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_USE_MATH_DEFINES -DNOMINMAX /openmp")
endif()

# turn build type RelWithDebInfo into one the strips the solutions from the exercise code
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DSTRIP_CODE")

#include_directories(${CMAKE_SOURCE_DIR}/src/)


add_subdirectory(src)

#if(WITH_DOCS)
  add_subdirectory(doc)
#endif()