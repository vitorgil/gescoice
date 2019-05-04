cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0022 NEW)

project(gescoice)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(RC_FILE "gescoice.rc")

# There may be a way to tell up front if Qt5 is going to be found, but I haven't found
# a foolproof way to do it yet, so settle for the default error message for now.
#if(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)
#    message(WARNING "CMAKE_PREFIX_PATH is not defined, so find_package may not work. Set the CMAKE_PREFIX_PATH "
#            "environment variable to the install prefix of Qt 5, either on the command line as "
#            "-DCMAKE_PREFIX_PATH=\"path/to/Qt5/lib/cmake\" or with set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)")
#endif(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(gescoice 
  main.cpp
  AddContainer.cpp
  AddContainer.ui
  AddIngredient.cpp
  AddIngredient.ui
  MainWindow.cpp
  MainWindow.ui
  SelectContainer.cpp
  SelectContainer.ui
  SelectIngredient.cpp
  SelectIngredient.ui
  resources.qrc)

# Add the Qt5 Widgets for linking
target_link_libraries(gescoice Qt5::Widgets core)

install(TARGETS gescoice RUNTIME DESTINATION bin)

install(
  FILES
    "C:/Qt/5.12.3/mingw73_64/bin/Qt5Widgets.dll"
    "C:/Qt/5.12.3/mingw73_64/bin/Qt5Core.dll"
    "C:/Qt/5.12.3/mingw73_64/bin/Qt5Gui.dll"
    "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/libgcc_s_seh-1.dll"
    "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/libstdc++-6.dll"
    "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/libwinpthread-1.dll"
  DESTINATION
    bin
)
