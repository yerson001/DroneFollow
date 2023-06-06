cmake_minimum_required(VERSION 2.8)

project(DroneFollow)

find_package( OpenCV REQUIRED )
find_package(Eigen3 REQUIRED)
set(CMAKE_CXX_STANDARD 17)
MESSAGE( [Main] " EIGEN3_INCLUDE_DIRS = ${EIGEN3_INCLUDE_DIRS}")
include_directories(${EIGEN3_INCLUDE_DIRS})

include_directories( ${OpenCV_INCLUDE_DIRS})

file(GLOB INCLUDE_FILES
  "include/*.h"
  "include/utils/ *.h"
  "include/LaneDetection/ *.h"
  "include/ParticleFilter/ *.h"
)
include_directories(include)

MACRO(add_example name)
  ADD_EXECUTABLE(${name}
      source/${name}.cpp
      # heders
      include/utils/functions.h
      include/LaneDetection/laneDetection.h
      include/VanishingPoint/vanishpoint.h
      include/utils/transformation.h
      include/ParticleFilter/particle.h
      include/control/ctello.h
      # .cpp files

      include/VanishingPoint/vanishpoint.cpp
      include/LaneDetection/laneDetection.cpp
      include/utils/functions.cpp
      include/ParticleFilter/particle.cpp
      include/utils/calibration.h
      include/control/ctello.cpp
      )

  TARGET_LINK_LIBRARIES(${name} ${OpenCV_LIBS})
ENDMACRO()

#add_example(main)
#add_example(vp)
add_example(pf)
#add_example(ld)

