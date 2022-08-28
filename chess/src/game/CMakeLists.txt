add_library(src_game
            Chess.h
						Chess.cpp)

target_include_directories(src_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
