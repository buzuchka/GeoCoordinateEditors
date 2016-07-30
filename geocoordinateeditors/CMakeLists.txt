project(geocoordinateeditors)

file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

if( NOT BUILD_WITH_QT4 )
    find_package(Qt5Widgets QUIET)
endif()

if (Qt5Widgets_FOUND)
    include_directories(${Qt5Widgets_INCLUDE_DIRS})
    set(QTLIBRARIES ${Qt5Widgets_LIBRARIES})
else()
    find_package(Qt4 REQUIRED QtGui)
    include(${QT_USE_FILE})
    set(QTLIBRARIES ${QT_LIBRARIES})
endif()

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    ${QTLIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC   ON
)
