add_library(src-input
						EventHandler.h
						EventHandler.cpp
						Reactor.h
						Reactor.cpp)

target_include_directories(src-input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)



