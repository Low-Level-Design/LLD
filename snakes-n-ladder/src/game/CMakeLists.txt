add_library(src_game
            SNLContext.h
            SNLContext.cpp
						SnakesNLadder.h
						SnakesNLadder.cpp)

target_include_directories(src_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
