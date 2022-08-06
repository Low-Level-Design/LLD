add_library(src_game
            TttContext.h
            TttContext.cpp
						Tictactoe.h
						Tictactoe.cpp)

target_include_directories(src_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
