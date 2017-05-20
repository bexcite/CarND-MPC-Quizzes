project(mpc)

cmake_minimum_required (VERSION 3.5)

# -g allows for gdb debugging
# turn on -03 for best performance
add_definitions(-std=c++11)

find_package( OpenCV REQUIRED )

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(sources src/MPC.cpp)

set(sourcesCvTest src/cv_test.cpp)

include_directories(src/Eigen-3.3)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(mpc ${sources})

add_executable(cv_test ${sourcesCvTest})

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
target_link_libraries(mpc ipopt python2.7)
else()
target_link_libraries(mpc ipopt python ${OpenCV_LIBS})
target_link_libraries(cv_test ${OpenCV_LIBS})
endif()