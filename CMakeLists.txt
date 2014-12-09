cmake_minimum_required(VERSION 2.8.7)

set(CMAKE_DEBUG_POSTFIX d)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

############################################
# Library name
############################################
project( CRA )
############################################

############################################
# Version declaration
# Target file will be named with version suffix
############################################
set( MAJOR_VERSION		 1 )
set( MINOR_VERSION		17 )
set( RELEASE_VERSION	 0 )

set( FULL_VERSION		${MAJOR_VERSION}.${MINOR_VERSION}.${RELEASE_VERSION} )

set( TARGET_NAME		${PROJECT_NAME}-${FULL_VERSION} )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/misc/configure.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/misc/configure.cmake @ONLY )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/misc/install.bat.in ${CMAKE_CURRENT_BINARY_DIR}/misc/install.bat @ONLY )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/src/doc/Doxyfile.in ${CMAKE_CURRENT_SOURCE_DIR}/src/doc/Doxyfile @ONLY )
############################################

############################################
# Options
# Set default options for this build
############################################
option(BUILD_DOC	"Build and install the API documentation"	OFF)
option(BUILD_TEST	"Build the unit tests"				OFF)
############################################

############################################
# Find dependencies and add them later to the linker (see below)
############################################

# Qt

set( QT_USE_QTMAIN		TRUE )
set( QT_USE_QTOPENGL	TRUE )
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )

# GLEW

include( $ENV{MEDITEC_LIBS}/GLEW/1.7.0/configure.cmake )

# LocalizerDLL

include( $ENV{MEDITEC_LIBS}/LocalizerDLL/0.1.0/configure.cmake )

# CameraCalibration

include( $ENV{MEDITEC_LIBS}/CameraCalibration/0.1.0/configure.cmake )

# TRTK

include( $ENV{MEDITEC_LIBS}/TRTK/0.13.1/configure.cmake )

# Project

include_directories(${CMAKE_PROJECT_DIR}include/${PROJECT_NAME})
set( PUBLIC_HEADERS
		include/${PROJECT_NAME}/cra_global.h
		include/${PROJECT_NAME}/DefaultLocalizer.h
		include/${PROJECT_NAME}/LazyLocalizer.h
		include/${PROJECT_NAME}/Link.h
		include/${PROJECT_NAME}/LinkedCamera.h
		include/${PROJECT_NAME}/LinkedCameraDebugger.h
		include/${PROJECT_NAME}/LinkedCameraImplementation.h
		include/${PROJECT_NAME}/LinkedObject.h
		include/${PROJECT_NAME}/Localizer.h
		include/${PROJECT_NAME}/Registration.h
		include/${PROJECT_NAME}/Tool.h
		include/${PROJECT_NAME}/ToolByPort.h
		include/${PROJECT_NAME}/VirtualElement.h
		include/${PROJECT_NAME}/Transformation.h
	)
include_directories(${CMAKE_PROJECT_DIR}src/include)
set( PRIVATE_HEADERS
		src/include/glew.h
		src/include/DefaultLocalizerDetails.h
		src/include/LinkedCameraImplementationDetails.h
	)
set( QOBJECT_HEADERS
		include/${PROJECT_NAME}/Registration.h
		include/${PROJECT_NAME}/Tool.h
	)
set( SRC
		src/DefaultLocalizer.cpp
		src/LazyLocalizer.cpp
		src/LinkedCameraDebugger.cpp
		src/LinkedCameraImplementation.cpp
		src/Registration.cpp
		src/Tool.cpp
		src/ToolByPort.cpp
	)
set( FORMS
		""
	)
set( RESOURCES
		""
	)
	
QT4_WRAP_CPP( QOBJECT_HEADERS_MOC ${QOBJECT_HEADERS} )
QT4_WRAP_UI( FORMS_HEADERS ${FORMS} )
QT4_ADD_RESOURCES( RESOURCES_RCC ${RESOURCES} )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

add_library( ${TARGET_NAME} SHARED
			${SRC}
			${PUBLIC_HEADERS}
			${PRIVATE_HEADERS}
			${QOBJECT_HEADERS_MOC}
			${FORMS_HEADERS}
			${RESOURCES_RCC}
		)

string( TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER )
add_definitions( -D${PROJECT_NAME_UPPER}_LIB -DNOMINMAX -DTRTK_SUPPORT_CVECTOR )


############################################
# Add dependencies to the linker
############################################

target_link_libraries( ${TARGET_NAME}
			opengl32
			glu32
			${GLEW_LIBLIST}
			${QT_LIBRARIES}
			${TRTK_LIBLIST}
			${LOCALIZERDLL_LIBLIST}
			${MATHBIB_LIBLIST}
			${CAMERACALIBRATION_LIBLIST}
		)






#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
### NO CHANGES EVER NECESSARY BELOW THIS POINT!!
##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

string( REGEX REPLACE "\\\\" "/" INSTALL_DIR $ENV{MEDITEC_LIBS}/${PROJECT_NAME}/${FULL_VERSION} )

install(	TARGETS	${TARGET_NAME}
		RUNTIME	DESTINATION	$ENV{MEDITEC_LIBS}/bin
		)
install(	TARGETS	${TARGET_NAME}
		RUNTIME	DESTINATION	${INSTALL_DIR}/bin
		ARCHIVE	DESTINATION	${INSTALL_DIR}/bin
		LIBRARY	DESTINATION	${INSTALL_DIR}/bin
		)
install(	FILES	${CMAKE_CURRENT_BINARY_DIR}/misc/configure.cmake ${CMAKE_CURRENT_BINARY_DIR}/misc/install.bat
		DESTINATION 	${INSTALL_DIR}
		)
install(	DIRECTORY	${CMAKE_PROJECT_DIR}include
		DESTINATION 	${INSTALL_DIR}
		)
if (WIN32)
	install(	FILES	${CMAKE_CURRENT_BINARY_DIR}/bin/${TARGET_NAME}${CMAKE_DEBUG_POSTFIX}.pdb
			DESTINATION		$ENV{MEDITEC_LIBS}/bin
			OPTIONAL
			)
	install(	FILES	${CMAKE_CURRENT_BINARY_DIR}/bin/${TARGET_NAME}${CMAKE_DEBUG_POSTFIX}.pdb
			DESTINATION		${INSTALL_DIR}/bin
			OPTIONAL
			)
endif()


############################################
# Unit tests
############################################
if( BUILD_TEST )
	add_subdirectory( test )
endif()
############################################

############################################
# Doxygen API documentation
############################################
if( BUILD_DOC )
	find_package( Doxygen REQUIRED )
	if( DOXYGEN_FOUND )
		add_custom_target(	doc ALL
						${DOXYGEN_EXECUTABLE} 
						WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/doc
						COMMENT "Generating API documentation with Doxygen" VERBATIM
					)
		install(	DIRECTORY 	${CMAKE_CURRENT_SOURCE_DIR}/doc
				DESTINATION		${INSTALL_DIR}
			)
	endif( DOXYGEN_FOUND )
endif()
############################################
