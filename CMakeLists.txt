cmake_minimum_required(VERSION 3.16.3)
project(testHOG)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# add_link_options(LDFLAGS -ldl)
# set (CMAKE_EXE_LINKER_FLAGS -ldl)
# set(LDFLAGS "-Wl,--no-as-needed")

set(EXECUTABLE_OUTPUT_PATH ${testHOG_SOURCE_DIR}/bin)

include_directories(./include)
include_directories(./malloc_count)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -DDEBUG")

add_library(COMMON_LIBRARY ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/timer.cpp ./malloc_count/malloc_count.c ./malloc_count/stack_count.c)
target_link_libraries(COMMON_LIBRARY ${CMAKE_DL_LIBS})

add_library(COMMON_LIBRARY_TIME ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/timer.cpp)

# change according to algorithm being tested
add_executable(TEST ./src/HOG-SSP.cpp ./tests/validateHOG.cpp)
target_compile_definitions(TEST PUBLIC SSP)
target_link_libraries(TEST PUBLIC COMMON_LIBRARY)

# add_executable(AHO ./src/HOG-SSP.cpp ./tests/testHOG.cpp)
# target_compile_definitions(AHO PUBLIC CONSTRUCT_AHO)
# target_link_libraries(AHO PUBLIC COMMON_LIBRARY)
# add_executable(EHOG ./src/HOG-SSP.cpp ./tests/testHOG.cpp)
# target_compile_definitions(EHOG PUBLIC CONSTRUCT_EHOG)
# target_link_libraries(EHOG PUBLIC COMMON_LIBRARY)

# Hog from Aho Corasick, No dumping, Time Reading
add_executable(SSP_TIME_DIRECT_AHO ./src/HOG-SSP.cpp ./tests/testHOG.cpp)
target_compile_definitions(SSP_TIME_DIRECT_AHO PUBLIC SSP DIRECT)
target_link_libraries(SSP_TIME_DIRECT_AHO PUBLIC COMMON_LIBRARY_TIME)

add_executable(SK_TIME_DIRECT_AHO ./src/HOG-SK.cpp ./tests/testHOG.cpp)
target_compile_definitions(SK_TIME_DIRECT_AHO PUBLIC SK DIRECT)
target_link_libraries(SK_TIME_DIRECT_AHO PUBLIC COMMON_LIBRARY_TIME)

add_executable(SP_TIME_DIRECT_AHO ./src/HOG-SP.cpp ./tests/testHOG.cpp)
target_compile_definitions(SP_TIME_DIRECT_AHO PUBLIC SP DIRECT)
target_link_libraries(SP_TIME_DIRECT_AHO PUBLIC COMMON_LIBRARY_TIME)

add_executable(BCER_TIME_DIRECT_AHO ./src/HOG-BCER.cpp ./tests/testHOG.cpp)
target_compile_definitions(BCER_TIME_DIRECT_AHO PUBLIC BCER DIRECT)
target_link_libraries(BCER_TIME_DIRECT_AHO PUBLIC COMMON_LIBRARY_TIME)

add_executable(EC_TIME_DIRECT_AHO ./src/HOG-EC.cpp ./tests/testHOG.cpp)
target_compile_definitions(EC_TIME_DIRECT_AHO PUBLIC EC DIRECT)
target_link_libraries(EC_TIME_DIRECT_AHO PUBLIC COMMON_LIBRARY_TIME)

# Hog from EHOG, No dumping, Time Reading
add_executable(SSP_TIME_DIRECT_EHOG ./src/HOG-SSP.cpp ./tests/testHOG.cpp)
target_compile_definitions(SSP_TIME_DIRECT_EHOG PUBLIC SSP DIRECT VIA_EHOG)
target_link_libraries(SSP_TIME_DIRECT_EHOG PUBLIC COMMON_LIBRARY_TIME)

add_executable(SK_TIME_DIRECT_EHOG ./src/HOG-SK.cpp ./tests/testHOG.cpp)
target_compile_definitions(SK_TIME_DIRECT_EHOG PUBLIC SK DIRECT VIA_EHOG)
target_link_libraries(SK_TIME_DIRECT_EHOG PUBLIC COMMON_LIBRARY_TIME)

add_executable(SP_TIME_DIRECT_EHOG ./src/HOG-SP.cpp ./tests/testHOG.cpp)
target_compile_definitions(SP_TIME_DIRECT_EHOG PUBLIC SP DIRECT VIA_EHOG)
target_link_libraries(SP_TIME_DIRECT_EHOG PUBLIC COMMON_LIBRARY_TIME)

add_executable(BCER_TIME_DIRECT_EHOG ./src/HOG-BCER.cpp ./tests/testHOG.cpp)
target_compile_definitions(BCER_TIME_DIRECT_EHOG PUBLIC BCER DIRECT VIA_EHOG)
target_link_libraries(BCER_TIME_DIRECT_EHOG PUBLIC COMMON_LIBRARY_TIME)

add_executable(EC_TIME_DIRECT_EHOG ./src/HOG-EC.cpp ./tests/testHOG.cpp)
target_compile_definitions(EC_TIME_DIRECT_EHOG PUBLIC EC DIRECT VIA_EHOG)
target_link_libraries(EC_TIME_DIRECT_EHOG PUBLIC COMMON_LIBRARY_TIME)

# Hog from Aho Corasick, No dumping, Memory Reading
add_executable(SSP_MEMORY_DIRECT_AHO ./src/HOG-SSP.cpp ./tests/testHOG.cpp)
target_compile_definitions(SSP_MEMORY_DIRECT_AHO PUBLIC SSP DIRECT MEMORY_READING)
target_link_libraries(SSP_MEMORY_DIRECT_AHO PUBLIC COMMON_LIBRARY)

add_executable(SK_MEMORY_DIRECT_AHO ./src/HOG-SK.cpp ./tests/testHOG.cpp)
target_compile_definitions(SK_MEMORY_DIRECT_AHO PUBLIC SK DIRECT MEMORY_READING)
target_link_libraries(SK_MEMORY_DIRECT_AHO PUBLIC COMMON_LIBRARY)

add_executable(SP_MEMORY_DIRECT_AHO ./src/HOG-SP.cpp ./tests/testHOG.cpp)
target_compile_definitions(SP_MEMORY_DIRECT_AHO PUBLIC SP DIRECT MEMORY_READING)
target_link_libraries(SP_MEMORY_DIRECT_AHO PUBLIC COMMON_LIBRARY)

add_executable(BCER_MEMORY_DIRECT_AHO ./src/HOG-BCER.cpp ./tests/testHOG.cpp)
target_compile_definitions(BCER_MEMORY_DIRECT_AHO PUBLIC BCER DIRECT MEMORY_READING)
target_link_libraries(BCER_MEMORY_DIRECT_AHO PUBLIC COMMON_LIBRARY)

add_executable(EC_MEMORY_DIRECT_AHO ./src/HOG-EC.cpp ./tests/testHOG.cpp)
target_compile_definitions(EC_MEMORY_DIRECT_AHO PUBLIC EC DIRECT MEMORY_READING)
target_link_libraries(EC_MEMORY_DIRECT_AHO PUBLIC COMMON_LIBRARY)

# Hog from EHOG, No dumping, Memory Reading
add_executable(SSP_MEMORY_DIRECT_EHOG ./src/HOG-SSP.cpp ./tests/testHOG.cpp)
target_compile_definitions(SSP_MEMORY_DIRECT_EHOG PUBLIC SSP DIRECT VIA_EHOG MEMORY_READING)
target_link_libraries(SSP_MEMORY_DIRECT_EHOG PUBLIC COMMON_LIBRARY)

add_executable(SK_MEMORY_DIRECT_EHOG ./src/HOG-SK.cpp ./tests/testHOG.cpp)
target_compile_definitions(SK_MEMORY_DIRECT_EHOG PUBLIC SK DIRECT VIA_EHOG MEMORY_READING)
target_link_libraries(SK_MEMORY_DIRECT_EHOG PUBLIC COMMON_LIBRARY)

add_executable(SP_MEMORY_DIRECT_EHOG ./src/HOG-SP.cpp ./tests/testHOG.cpp)
target_compile_definitions(SP_MEMORY_DIRECT_EHOG PUBLIC SP DIRECT VIA_EHOG MEMORY_READING)
target_link_libraries(SP_MEMORY_DIRECT_EHOG PUBLIC COMMON_LIBRARY)

add_executable(BCER_MEMORY_DIRECT_EHOG ./src/HOG-BCER.cpp ./tests/testHOG.cpp)
target_compile_definitions(BCER_MEMORY_DIRECT_EHOG PUBLIC BCER DIRECT VIA_EHOG MEMORY_READING)
target_link_libraries(BCER_MEMORY_DIRECT_EHOG PUBLIC COMMON_LIBRARY)

add_executable(EC_MEMORY_DIRECT_EHOG ./src/HOG-EC.cpp ./tests/testHOG.cpp)
target_compile_definitions(EC_MEMORY_DIRECT_EHOG PUBLIC EC DIRECT VIA_EHOG MEMORY_READING)
target_link_libraries(EC_MEMORY_DIRECT_EHOG PUBLIC COMMON_LIBRARY)

# add_executable(SSPEHOG ./src/HOG-SSP.cpp ./tests/testHOG.cpp)
# target_compile_definitions(SSPEHOG PUBLIC SSP VIA_EHOG)
# target_link_libraries(SSPEHOG PUBLIC COMMON_LIBRARY)
# add_executable(SKEHOG ./src/HOG-SK.cpp ./tests/testHOG.cpp)
# target_compile_definitions(SKEHOG PUBLIC SK VIA_EHOG)
# target_link_libraries(SKEHOG PUBLIC COMMON_LIBRARY)
# add_executable(SPEHOG ./src/HOG-SP.cpp ./tests/testHOG.cpp)
# target_compile_definitions(SPEHOG PUBLIC SP VIA_EHOG)
# target_link_libraries(SPEHOG PUBLIC COMMON_LIBRARY)

# add_executable(BCEREHOG ./src/HOG-BCER.cpp ./tests/testHOG.cpp)
# target_compile_definitions(BCEREHOG PUBLIC BCER VIA_EHOG)
# target_link_libraries(BCEREHOG PUBLIC COMMON_LIBRARY)
# add_executable(ECEHOG ./src/HOG-EC.cpp ./tests/testHOG.cpp)
# target_compile_definitions(ECEHOG PUBLIC EC VIA_EHOG)
# target_link_libraries(ECEHOG PUBLIC COMMON_LIBRARY)

