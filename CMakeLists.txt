cmake_minimum_required(VERSION 3.16.3)
project(testHOG)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE_OUTPUT_PATH ${testHOG_SOURCE_DIR}/bin)

include_directories(./include)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -DDEBUG")

# add_executable(SSP ./src/HOG-SSP.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./tests/testHOG.cpp ./src/timer.cpp)
# target_compile_definitions(SSP PUBLIC SSP)
# add_executable(SK ./src/HOG-SK.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./tests/testHOG.cpp ./src/timer.cpp)
# target_compile_definitions(SK PUBLIC SK)
# add_executable(SSPEHOG ./src/HOG-SSP.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./tests/testHOG.cpp ./src/timer.cpp)
# target_compile_definitions(SSPEHOG PUBLIC SSP EHOG_CONSTRUCTION)
# add_executable(SKEHOG ./src/HOG-SK.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./tests/testHOG.cpp ./src/timer.cpp)
# target_compile_definitions(SKEHOG PUBLIC SK EHOG_CONSTRUCTION)

# add_executable(BCER ./src/HOG-BCER.cpp ./src/Aho-Corax.cpp ./src/EHOGx.cpp ./tests/testHOG.cpp ./src/timer.cpp)
# target_compile_definitions(BCER PUBLIC BCER)
# add_executable(EC ./src/HOG-EC.cpp ./src/Aho-Corax.cpp ./src/EHOGx.cpp ./tests/testHOG.cpp ./src/timer.cpp)
# target_compile_definitions(EC PUBLIC EC)
# add_executable(BCEREHOG ./src/HOG-BCER.cpp ./src/Aho-Corax.cpp ./src/EHOGx.cpp ./tests/testHOG.cpp ./src/timer.cpp)
# target_compile_definitions(BCEREHOG PUBLIC BCER EHOG_CONSTRUCTION)
# add_executable(ECEHOG ./src/HOG-EC.cpp ./src/Aho-Corax.cpp ./src/EHOGx.cpp ./tests/testHOG.cpp ./src/timer.cpp)
# target_compile_definitions(ECEHOG PUBLIC EC EHOG_CONSTRUCTION)

# add_subdirectory(malloc_count)

add_executable(TEST ./tests/testHOG ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/timer.cpp ./src/HOG-BASE.cpp ./src/HOG-SSP.cpp ./src/HOG-EC.cpp ./src/HOG-SK.cpp ./src/HOG-BCER.cpp)
target_compile_definitions(TEST PUBLIC BCER)
add_executable(AHO ./tests/testAho.cpp ./src/timer.cpp ./src/Aho-Cora.cpp ./malloc_count/malloc_count.c)
target_link_libraries(AHO PUBLIC -ldl)
# target_link_libraries(AHO PUBLIC malloc_count)
# target_include_directories(AHO PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           "${PROJECT_SOURCE_DIR}/malloc_count"
#                           )
add_executable(EHOG ./tests/testEHOG.cpp ./src/timer.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp)
add_executable(SSPAHO ./src/HOG-SSP.cpp ./tests/testHOGfromAHO.cpp ./src/timer.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/HOG-BASE.cpp)
target_compile_definitions(SSPAHO PUBLIC SSP)
add_executable(SKAHO ./src/HOG-SK.cpp ./tests/testHOGfromAHO.cpp ./src/timer.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/HOG-BASE.cpp)
target_compile_definitions(SKAHO PUBLIC SK)
add_executable(ECAHO ./src/HOG-EC.cpp ./tests/testHOGfromAHO.cpp ./src/timer.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/HOG-BASE.cpp)
target_compile_definitions(ECAHO PUBLIC EC)
add_executable(BCERAHO ./src/HOG-BCER.cpp ./tests/testHOGfromAHO.cpp ./src/timer.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/HOG-BASE.cpp)
target_compile_definitions(BCERAHO PUBLIC BCER)
add_executable(SSPEHOG ./src/HOG-SSP.cpp ./tests/testHOGfromEHOG.cpp ./src/timer.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/HOG-BASE.cpp)
target_compile_definitions(SSPEHOG PUBLIC SSP)
add_executable(SKEHOG ./src/HOG-SK.cpp ./tests/testHOGfromEHOG.cpp ./src/timer.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/HOG-BASE.cpp)
target_compile_definitions(SKEHOG PUBLIC SK)
add_executable(ECEHOG ./src/HOG-EC.cpp ./tests/testHOGfromEHOG.cpp ./src/timer.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/HOG-BASE.cpp)
target_compile_definitions(ECEHOG PUBLIC EC)
add_executable(BCEREHOG ./src/HOG-BCER.cpp ./tests/testHOGfromEHOG.cpp ./src/timer.cpp ./src/Aho-Cora.cpp ./src/EHOG.cpp ./src/HOG-BASE.cpp)
target_compile_definitions(BCEREHOG PUBLIC BCER)