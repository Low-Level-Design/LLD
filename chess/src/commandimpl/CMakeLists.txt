add_library(src_command
						CommandImpl.h
						CommandImpl.cpp)

target_include_directories(src_command PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(src_command src_viewcontroller)
