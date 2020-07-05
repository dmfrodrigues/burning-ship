cmake_minimum_required(VERSION 3.10)

project(burning-ship)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/.. )

find_package(wxWidgets COMPONENTS core base REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/../fractal-app/include)
include_directories(${PROJECT_SOURCE_DIR}/../fractal-app/lib)

include_directories(../include)
include(${wxWidgets_USE_FILE})

add_executable(burning-ship FractalApp.cpp BurningShip.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    fractalapp
    )

set(CPP_COMPILER_WARNINGS -Wall -Wunused-result -pedantic-errors -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts
                          -Wcomment -Wconversion -Wdisabled-optimization -Wfloat-equal  -Wformat  -Wformat=2
                          -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winvalid-pch
                          -Wmissing-braces -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs
                          -Wmissing-noreturn -Wpacked -Wparentheses  -Wpointer-arith -Wredundant-decls -Wreturn-type
                          -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2
                          -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized -Wunknown-pragmas 
                          -Wunreachable-code -Wunused -Wunused-function  -Wunused-label  -Wunused-parameter
                          -Wunused-value  -Wunused-variable  -Wvariadic-macros -Wvolatile-register-var  -Wwrite-strings)

set(CPP_COMPILER_OPTIMIZE -ffast-math -O3)

target_compile_options(burning-ship PRIVATE -g ${CPP_COMPILER_WARNINGS} ${CPP_COMPILER_OPTIMIZE})
