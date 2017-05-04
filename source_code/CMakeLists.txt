cmake_minimum_required (VERSION 3.1)

project (MDAtom)

# Activate c++11 flag
set (CMAKE_CXX_STANDARD 11)

# set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

set (headers
     lib/MDParameters.h
     lib/ParameterIO.h
     lib/ParameterValidityChecker.h
     lib/CoordinatesAndVelocitiesInitializer.h
     lib/Timer.h
     lib/TrajectoryFileWriter.h
     lib/MDSimulation.h
     lib/MDRun.h
     lib/MDRunOutput.h
     lib/InteractionCalculator.h
     lib/RadialDistribution.h
     lib/InstantaneousRadialDistribution.h
     lib/AveragedRadialDistribution.h
     lib/BinaryIO.h
     lib/PeriodicBoundaryConditions.h
     lib/CenterOfMassCalculator.h
     lib/RandomNumberGenerator.h
)

set (sources
     lib/MDParameters.cpp
     lib/ParameterIO.cpp
     lib/ParameterValidityChecker.cpp
     lib/CoordinatesAndVelocitiesInitializer.cpp
     lib/Timer.cpp
     lib/TrajectoryFileWriter.cpp
     lib/MDSimulation.cpp
     lib/MDRun.cpp
     lib/MDRunOutput.cpp
     lib/InteractionCalculator.cpp
     lib/InstantaneousRadialDistribution.cpp
     lib/AveragedRadialDistribution.cpp
     lib/BinaryIO.cpp
     lib/PeriodicBoundaryConditions.cpp
     lib/CenterOfMassCalculator.cpp
     lib/RandomNumberGenerator.cpp
)

add_library(mdatomLib ${sources} ${headers})
set_target_properties(mdatomLib PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mdatomLib PUBLIC lib)

add_executable(mdatom main.cpp)
target_link_libraries(mdatom mdatomLib)
