find_package(Qt5 REQUIRED COMPONENTS Core)

add_library(core SHARED
    Containers.cpp
    Containers.h
    Ingredients.cpp
    Ingredients.h
    IO.cpp
    IO.h
    Lot.cpp
    Lot.h
)

target_include_directories(core INTERFACE ${CMAKE_SOURCE_DIR}/src/core)
target_link_libraries(core Qt5::Core)

install(TARGETS core 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)
