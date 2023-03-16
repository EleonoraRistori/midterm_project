cmake_minimum_required(VERSION 3.3)
project(openmp_producer_consumer_exercise)

set(CMAKE_CXX_STANDARD 11)

# in Linux just use -fopenmp, without -lomp and -Xpreprocessor
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
# the following 2 lines are needed on macOS.
# update paths as required
include_directories(/usr/local/include/)
link_directories(/usr/local/lib/)

set(SOURCE_FILES main.cpp NGramsCounter.cpp NGramsCounter.h)
add_executable(openmp_producer_consumer_exercise ${SOURCE_FILES})
