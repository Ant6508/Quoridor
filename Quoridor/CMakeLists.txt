cmake_minimum_required(VERSION 3.28)
project(wxQuoridor)

add_executable(wxQuoridor src/App.cpp src/MainFrame.cpp src/base/Partie.cpp )

add_subdirectory(external/wxWidgets-3.2.4)


target_link_libraries(wxQuoridor wx::net wx::core wx::base)

    