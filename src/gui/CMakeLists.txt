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
  addcontainer.ui
  AddIngredient.cpp
  addingredient.ui
  GuiUtils.cpp
  MainWindow.cpp
  mainwindow.ui
  SelectContainer.cpp
  selectcontainer.ui
  SelectIngredient.cpp
  selectingredient.ui
  resources.qrc
)

# Add the Qt5 Widgets for linking
target_link_libraries(gescoice Qt5::Widgets core)

install(TARGETS gescoice RUNTIME DESTINATION bin)
