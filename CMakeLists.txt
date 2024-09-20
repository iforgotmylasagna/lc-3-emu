cmake_minimum_required(VERSION 3.10)
project(lc3vm)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE RELEASE)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Werror -Wconversion) #-Wpedantic)
endif()

#set SOURCES to all cpp files in src
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

#find_package(SDL2 REQUIRED)

add_executable(lc3vm "${PROJECT_SOURCE_DIR}/src/main.cpp" ${SOURCES})
#target_link_libraries(lc3vm PRIVATE SDL2::SDL2)

target_include_directories(lc3vm
	PUBLIC ${PROJECT_SOURCE_DIR}/include/
	PRIVATE $(PROJECT_SOURCE_DIR)/src
)



	
set_target_properties(lc3vm PROPERTIES
    OUTPUT_NAME "run"
)

set_target_properties( PROPERTIES VERSION 1.0 SOVERSION 1)


#install
set(LC3VM_DIR "${PROJECT_SOURCE_DIR}/bin")
install(TARGETS lc3vm
	RUNTIME DESTINATION ${LC3VM_DIR}
)


#add_subdirectory( ${PROJECT_SOURCE_DIR}/examples)
