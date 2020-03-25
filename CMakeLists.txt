cmake_minimum_required(VERSION 3.13)
project(Puzzle)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread")

include_directories(.)


find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Boost 1.58 REQUIRED COMPONENTS filesystem iostreams serialization unit_test_framework log)

include_directories (${Boost_INCLUDE_DIRS})

add_executable(Puzzle
        main.cpp
        mainwindow.cpp
        mainwindow.h
        point.cpp
        point.h
        puzzle.cpp
        puzzle.h
        Segment.cpp
        Segment.h
        ui_mainwindow.h
        PuzzleList.cpp
        PuzzleList.h
        PuzzleOnBoard.cpp
        PuzzleOnBoard.h
        Layout.cpp
        Layout.h
        PointOfEnvelope.cpp
        PointOfEnvelope.h
        Polygon.cpp
        Polygon.h
        SegmentOfEnvelope.cpp
        SegmentOfEnvelope.h
        LayoutCacheImage.cpp
        LayoutCacheImage.h
        Vector.cpp
        Vector.h
        CIniFile.h
        CIniFile.cpp Solver.cpp Solver.h Math.cpp Math.h PuzzleOnBoardRepo.cpp PuzzleOnBoardRepo.h)

#qt5_generate_moc(main.cpp main.moc)
#qt5_generate_moc(mainwindow.cpp mainwindow.moc)

target_link_libraries(Puzzle Qt5::Widgets Boost::filesystem
        Boost::iostreams Boost::serialization Boost::unit_test_framework
        Boost::log)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)