cmake_minimum_required(VERSION 3.16)
project(code_analysis)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
# set(CMAKE_CXX_CPPCHECK cppcheck)

###
add_library(lib_a lib_a/include/lib_a/lib_a.hpp lib_a/src/lib_a.cpp)
add_library(lib_a::lib_a ALIAS lib_a)
target_include_directories(lib_a PRIVATE lib_a/include/lib_a PUBLIC lib_a/include)
target_compile_options(lib_a PRIVATE -fsanitize=address)
target_link_options(lib_a PRIVATE -fsanitize=address) # this is useless
target_link_directories(lib_a PRIVATE "$ENV{ProgramFiles\(x86\)}/Microsoft Visual Studio/2019/Community/VC/Tools/Llvm/x64/lib/clang/12.0.0/lib/windows")
target_link_libraries(lib_a PRIVATE clang_rt.asan_dynamic-x86_64 clang_rt.asan_dynamic_runtime_thunk-x86_64)
target_link_options(lib_a PRIVATE /wholearchive:clang_rt.asan_dynamic_runtime_thunk-x86_64.lib)

###
add_executable(code_analysis app/main.cpp)
target_link_libraries(code_analysis PRIVATE lib_a::lib_a)

###
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build/modules)
find_package(GTest)
include(GoogleTest)
add_executable(test tests/main.cpp tests/test_a.cpp)
target_link_libraries(test PRIVATE GTest::GTest PRIVATE lib_a::lib_a)
target_compile_features(test PUBLIC cxx_std_17)

# conan install tests --install-folder build/modules --settings build_type=Debug --settings compiler="Visual Studio" --settings compiler.version=16 --build missing

# set CC='C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\Llvm\x64\bin\clang.exe'
# & set CXX='C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\Llvm\x64\bin\clang++.exe'
# & set RC='C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\Llvm\x64\bin\llvm-rc.exe'
# & conan install tests --install-folder build/modules --settings build_type=Debug --settings compiler="clang" --settings compiler.version=12 --build missing