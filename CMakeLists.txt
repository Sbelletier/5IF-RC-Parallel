cmake_minimum_required(VERSION 3.0)
project(pdc_evol_model)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(SOURCE_FILES main.cpp src/World.cpp src/World.h src/GridCell.cpp src/GridCell.h src/Organism.cpp src/Organism.h src/DNA.cpp src/DNA.h src/BP.cpp src/BP.h src/BP_Protein_Block.cpp src/BP_Protein_Block.h src/BP_Protein.cpp src/BP_Protein.h src/BP_Pump_Block.cpp src/BP_Pump_Block.h src/BP_Pump.cpp src/BP_Pump.h src/BP_Move_Block.cpp src/BP_Move_Block.h src/BP_Move.cpp src/BP_Move.h src/RNA.cpp src/RNA.h src/Protein.cpp src/Protein.h src/Move.cpp src/Move.h src/Pump.cpp src/Pump.h src/Common.cpp src/Common.h src/MpiSlave.h src/MpiSlave.cpp)
add_executable(pdc_evol_model ${SOURCE_FILES})

if(WITH_GRAPHICS_CONTEXT)
    find_package(SFML 2 REQUIRED graphics window system)
    if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(pdc_evol_model ${SFML_LIBRARIES})
    endif(SFML_FOUND)
    list(APPEND eye_evolution SOURCES src/GraphicDisplay.cpp src/GraphicDisplay.h)
    add_definitions(-DWITH_GRAPHICS_CONTEXT=1)
endif(WITH_GRAPHICS_CONTEXT)


find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIR})
    target_link_libraries(pdc_evol_model ${ZLIB_LIBRARIES})
endif(ZLIB_FOUND)



#
# LINKING MPI
#
set(CMAKE_MODULE_PATH "/home/$USER/.ompi/*;${CMAKE_MODULE_PATH}")

find_package(MPI REQUIRED)
if(MPI_FOUND)
	include_directories(${MPI_INCLUDE_PATH})
    target_link_libraries(pdc_evol_model ${MPI_LIBRARIES})
endif(MPI_FOUND)

if(MPI_COMPILE_FLAGS)
  set_target_properties(pdc_evol_model PROPERTIES
    COMPILE_FLAGS "${CMAKE_CXX_COMPILE_FLAGS}  ${MPI_COMPILE_FLAGS}")
endif(MPI_COMPILE_FLAGS)

if(MPI_LINK_FLAGS)
  set_target_properties(pdc_evol_model PROPERTIES
    LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS}  ${MPI_LINK_FLAGS}")
endif(MPI_LINK_FLAGS)
