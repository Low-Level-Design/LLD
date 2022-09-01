add_library(src_viewcontroller
            ChessController.h
            ChessController.cpp
            ChessViewer.h
            ChessViewer.cpp)
						

target_include_directories(src_viewcontroller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(src_viewcontroller src_game)