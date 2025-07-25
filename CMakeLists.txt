cmake_minimum_required(VERSION 3.10)
project(LPBenchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LPSOLVE_ROOT_DIR "/path/to/lp_solve" CACHE PATH "Root directory of lp_solve installation")
set(HIGHS_ROOT_DIR "/path/to/highs" CACHE PATH "Root directory of HiGHS installation")
set(SCIP_ROOT_DIR "/path/to/scip" CACHE PATH "Root directory of SCIP installation")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/ 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)

find_library(LPSOLVE_LIBRARY
    NAMES lpsolve55
    PATHS ${LPSOLVE_ROOT_DIR}/lib
        usr/lib
        usr/lib/x86_64-linux-gnu
        usr/local/lib
    PATH_SUFFIXES lp_solve lpsolve
)

find_path(LPSOLVE_INCLUDE_DIR 
    NAMES lp_lib.h
    PATHS ${LPSOLVE_ROOT_DIR}/include
        usr/include
        usr/local/include
    PATH_SUFFIXES lp_solve lpsolve
) 

if (NOT LPSOLVE_LIBRARY)
    message(FATAL_ERROR "библиотека lp_solve не найдена")
endif()

if (NOT LPSOLVE_INCLUDE_DIR)
    message(FATAL_ERROR "заголовочный файл lp_solve не найден")
endif()


find_library(SCIP_LIBRARY
    NAMES scip
    PATHS ${SCIP_ROOT_DIR}/lib
        usr/lib
        usr/lib/x86_64-linux-gnu
        usr/local/lib
    PATH_SUFFIXES scip
)

find_path(SCIP_INCLUDE_DIR
    NAMES scip.h
    PATHS ${SCIP_ROOT_DIR}/include
        usr/include
        usr/local/include
    PATH_SUFFIXES scip
)

if (NOT SCIP_LIBRARY)
    message(FATAL_ERROR "библиотека SCIP не найдена")
endif()

if (NOT SCIP_INCLUDE_DIR)
    message(FATAL_ERROR "заголовочный файл SCIP не найден")
endif()


find_library(HIGHS_LIBRARY
    NAMES highs
    PATHS ${HIGHS_ROOT_DIR}/lib
        usr/lib
        usr/lib/x86_64-linux-gnu
        usr/local/lib
    PATH_SUFFIXES highs
)

find_path(HIGHS_INCLUDE_DIR
    NAMES Highs.h
    PATHS ${HIGHS_ROOT_DIR}/include
        usr/include
        usr/local/include
    PATH_SUFFIXES highs
)

if (NOT HIGHS_LIBRARY)
    message(FATAL_ERROR "библиотека Highs не найдена")
endif()

if (NOT HIGHS_INCLUDE_DIR)
    message(FATAL_ERROR "заголовочный файл Highs не найден")
endif()


include_directories(include)

add_executable(lp_benchmark
    src/main.cpp
    src/LpSolveSolver.cpp
    src/HighsSolver.cpp
    src/ScipSolver.cpp
)

target_link_libraries(lp_benchmark
    PRIVATE
    ${LPSOLVE_LIBRARY}
    ${SCIP_LIBRARY}
    ${HIGHS_LIBRARY}
)

target_include_directories(lp_benchmark
    PRIVATE
    /usr/include
    /usr/local/include
    /usr/local/include/highs
)