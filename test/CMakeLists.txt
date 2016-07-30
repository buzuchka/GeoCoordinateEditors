project(geocoordinateeditors_demo)

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

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME}
    ${QTLIBRARIES}
    geocoordinateeditors
)
