# version
cmake_minimum_required (VERSION 2.8)
set(PROJECT_NAME main)
set(LIBS_NAME loglib)
# project
project (${PROJECT_NAME})

# search the all dirs
aux_source_directory(. DIR_SRCS)
add_subdirectory(log)

#
# set(LIBRARY_OUT_PUT_PATH )
# set(CMAKE_C_COMPILER g++)
# head

include_directories(log) 
# add_library(loglib static )

# create target
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# link
target_link_libraries(${PROJECT_NAME} ${LIBS_NAME})
target_link_libraries(${PROJECT_NAME} pthread rt)


