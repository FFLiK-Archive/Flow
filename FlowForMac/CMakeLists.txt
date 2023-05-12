cmake_minimum_required(VERSION 3.25)
project(FlowForMac)

set(CMAKE_CXX_STANDARD 20)

include_directories(include json)
add_executable(FlowForMac Main.cpp Branch.cpp Branch.h Config.h FileIO.cpp FileIO.h History.cpp History.h Jsoncpp.cpp Log.cpp Log.h Metadata.cpp Metadata.h ProtableFileDialogs.h UUID.h Log.cpp)