# CMakeList.txt: ReadWriteFlatBuffersFile 的 CMake 專案，在此包含來源及定義
# 專案專屬邏輯。
#
cmake_minimum_required (VERSION 3.8)

# 如果支援，則為 MSVC 編譯器啟用熱重新載入。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#flatbuffers
include_directories("C:\\Program Files (x86)\\FlatBuffers\\include\\")

#rapidjson
include_directories("C:\\Users\\think\\Downloads\\rapidjson-master\\rapidjson-master\\include\\")

project ("ReadWriteFlatBuffersFile")

# 將來源新增到此專案的可執行檔。
add_executable (ReadWriteFlatBuffersFile "ReadWriteFlatBuffersFile.cpp" "ReadWriteFlatBuffersFile.h" "FlatBufferesMessage.h" "FlatBuffersMessage.cpp" "FileLoader.h" "JsonMessage.h" "JsonMessage.cpp" "CodeBlockTimer.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ReadWriteFlatBuffersFile PROPERTY CXX_STANDARD 20)
endif()

# TODO: 新增測試，並視需要安裝目標。
