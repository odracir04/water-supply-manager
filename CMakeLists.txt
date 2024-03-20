cmake_minimum_required(VERSION 3.27)
project(da_proj1)

set(CMAKE_CXX_STANDARD 11)

add_executable(da_proj1 src/main.cpp
        src/Reservoir.cpp
        src/Reservoir.h
        src/Station.cpp
        src/Station.h
        src/City.cpp
        src/City.h
        src/Parser.cpp
        src/Parser.h
        src/Interface.h
        src/Interface.cpp
        src/Vertex.cpp
        src/Vertex.h
        src/Pipe.cpp
        src/Pipe.h
        src/Graph.cpp
        src/Graph.h
        src/Manager.h
        src/Manager.cpp
)

