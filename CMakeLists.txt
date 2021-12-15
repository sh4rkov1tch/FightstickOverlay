cmake_minimum_required(VERSION 3.1)

project(FightstickOverlay C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(FightstickOverlay
    src/main.cpp
    src/App/CApp.cpp
    src/Buttons/CButton.cpp
    src/Buttons/CStick.cpp
    src/ConfigParser/CConfigParser.cpp
)

if(WIN32)
include_directories(FightstickOverlay
    src
    src/App
    src/Buttons
    src/Headers
    src/ConfigParser
    C:/TDM-GCC-64/include
    C:/TDM-GCC-64/lib/gcc/x86_64-w64-mingw32/10.3.0/include
)

target_link_libraries(FightstickOverlay
    raylib
    opengl32
    glu32
    winmm
    kernel32
    user32
    gdi32
    winspool
    shell32
    ole32
    oleaut32
    uuid
    comdlg32
    advapi32
)

endif(WIN32)

if(UNIX)

include_directories(FightstickOverlay
    src
    src/App
    src/Buttons
    src/Headers
    src/ConfigParser
)

target_link_libraries(FightstickOverlay
    raylib
)

endif(UNIX)

target_compile_options(FightstickOverlay PRIVATE
    "-Wall"
    "-O2"
)



file(COPY Configs/ DESTINATION Configs/)