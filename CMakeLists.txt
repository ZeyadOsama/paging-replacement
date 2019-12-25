cmake_minimum_required(VERSION 3.15)
project(Paging_Replacement)

set(CMAKE_CXX_STANDARD 17)

add_executable(Paging_Replacement main.cpp core/LinkedList.cpp core/LinkedList.h core/PageReplacer.cpp core/PageReplacer.h)