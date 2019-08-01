cmake_minimum_required (VERSION 2.6)

project (CuriousWeb)
set (CuriousWeb_VERSION_MAJOR 0)
set (CuriousWeb_VERSION_MINOR 1)

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )
set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH}  "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH  lib )
set ( INSTALL_HEADERS_PATH include )


# Make relative paths absolute (needed later on)

foreach(p LIB BIN HEADERS AR)
    set(var INSTALL_${p}_PATH)
    if(NOT IS_ABSOLUTE "${${var}}")
        set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif()
endforeach()


### Search for Lib/Headers

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(WEBKIT2 REQUIRED webkit2gtk-4.0 )      
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0) 


### Configure a header file to pass some of the CMake settings
### to the source code

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/src/config.h"
)


### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include"
	                 "${CMAKE_CURRENT_SOURCE_DIR}/src"
        	         "${CMAKE_CURRENT_BINARY_DIR}"
                     "${CMAKE_INSTALL_PREFIX}/include"
				     "${WEBKIT2_INCLUDE_DIRS}"
                     "${GTK3_INCLUDE_DIRS}")


### File Lists

file( GLOB src "src/*.c" )

### Main Target and linking

add_executable( "CuriousWeb" ${src} )

target_link_libraries ( "CuriousWeb" 
                        ${GTK3_LIBRARIES}
				        ${WEBKIT2_LIBRARIES} )

### Install targets

install( TARGETS "CuriousWeb"
        RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
        LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
        ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )


