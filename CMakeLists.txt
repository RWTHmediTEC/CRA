cmake_minimum_required(VERSION 3.0.2)
project( CRA )

set( MAJOR_VERSION	 1 )
set( MINOR_VERSION	16 )
set( PATCH_VERSION	 0 )

############################################

set(CMAKE_DEBUG_POSTFIX d)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(FULL_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
set(TARGET_NAME ${PROJECT_NAME}-${FULL_VERSION})
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_CAPS)

############################################
# Options
# Set default options for this build
############################################

option(BUILD_DOC	"Build and install the API documentation"	OFF)
option(BUILD_TEST	"Build the unit tests"						OFF)

############################################
# Macro that sets variable to default value
# only when the variable isn't defined yet
############################################

macro( option_default_to var_name default_val var_type doc_string )
	if( NOT DEFINED ${var_name} )
		set(${var_name} ${default_val})
	endif()
	set(${var_name} ${${var_name}} CACHE ${var_type} ${doc_string} FORCE)
endmacro()

############################################
# Locate Find<ModuleName>.cmake scripts
############################################

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/misc/CMake-Modules)

############################################
# Run MediTEC compatiblity script
############################################

add_subdirectory(misc/MediTEC)

############################################
# Define default paths for the installation
############################################

# set default library and header destinations (relative to CMAKE_INSTALL_PREFIX)
option_default_to(INSTALL_LIBRARY_DIR "lib" String "Installation directory for libraries")
option_default_to(INSTALL_HEADERS_DIR "include" String "Installation directory for headers")

# set default destination for CMake modules
if( WIN32 )
	option_default_to(INSTALL_CMAKE_DIR "share/cmake-3.0/Modules" String "Installation directory for CMake files")
else( WIN32 )
	option_default_to(INSTALL_CMAKE_DIR "share/cmake/Modules" String "Installation directory for CMake files")
endif( WIN32 )

############################################
# Normalize installation paths
# (get rid of Windows-style delimiters)
############################################

file(	TO_CMAKE_PATH	${INSTALL_LIBRARY_DIR}	INSTALL_LIBRARY_DIR )
file(	TO_CMAKE_PATH	${INSTALL_HEADERS_DIR}	INSTALL_HEADERS_DIR )
file(	TO_CMAKE_PATH	${INSTALL_CMAKE_DIR}	INSTALL_CMAKE_DIR )

############################################

configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/src/doc/Doxyfile.in
				${CMAKE_CURRENT_SOURCE_DIR}/src/doc/Doxyfile @ONLY)

configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/misc/Find${PROJECT_NAME}.cmake.in
				${CMAKE_CURRENT_BINARY_DIR}/misc/Find${PROJECT_NAME}.cmake @ONLY)

############################################
# Find required dependencies
############################################

# Qt
set( QT_USE_QTMAIN		TRUE )
set( QT_USE_QTOPENGL	TRUE )
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )

# GLEW
find_package( GLEW 1.7.0 REQUIRED )
include_directories( ${GLEW_INCLUDE_DIRS} )

# LocalizerDLL
include( $ENV{MEDITEC_LIBS}/LocalizerDLL/0.1.0/configure.cmake )

# CameraCalibration
include( $ENV{MEDITEC_LIBS}/CameraCalibration/0.1.0/configure.cmake )

# Eigen
find_package( Eigen3 3.0.5 REQUIRED )
include_directories( ${EIGEN3_INCLUDE_DIR} )

# TRTK
find_package( TRTK 0.13.1 REQUIRED )
include_directories( ${TRTK_INCLUDE_DIR} )

############################################
# Project
############################################

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

############################################

QT4_WRAP_CPP( QOBJECT_HEADERS_MOC ${QOBJECT_HEADERS} )
QT4_WRAP_UI( FORMS_HEADERS ${FORMS} )
QT4_ADD_RESOURCES( RESOURCES_RCC ${RESOURCES} )

############################################	
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
############################################

add_library( ${TARGET_NAME} SHARED
			${SRC}
			${PUBLIC_HEADERS}
			${PRIVATE_HEADERS}
			${QOBJECT_HEADERS_MOC}
			${FORMS_HEADERS}
			${RESOURCES_RCC}
		)

############################################

add_definitions( -D${PROJECT_NAME_CAPS}_LIB -DNOMINMAX -DTRTK_SUPPORT_CVECTOR )

############################################
# Add dependencies to the linker
############################################

target_link_libraries( ${TARGET_NAME}
			opengl32
			glu32
			${GLEW_LIBRARIES}
			${QT_LIBRARIES}
			${TRTK_LIBRARIES}
			${LOCALIZERDLL_LIBLIST}
			${MATHBIB_LIBLIST}
			${CAMERACALIBRATION_LIBLIST}
		)

############################################
# Define installation routines
############################################

install(TARGETS	${TARGET_NAME}
		RUNTIME	DESTINATION	${INSTALL_LIBRARY_DIR}
		ARCHIVE	DESTINATION	${INSTALL_LIBRARY_DIR}
		LIBRARY	DESTINATION	${INSTALL_LIBRARY_DIR})

# install headers
install(DIRECTORY ${CMAKE_PROJECT_DIR}include/CRA
		DESTINATION ${INSTALL_HEADERS_DIR})

# also install '.PDB' files on Windows
if( WIN32 )
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bin/${TARGET_NAME}${CMAKE_DEBUG_POSTFIX}.pdb
			DESTINATION ${INSTALL_LIBRARY_DIR}
			OPTIONAL)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bin/${TARGET_NAME}${CMAKE_DEBUG_POSTFIX}.pdb
			DESTINATION ${INSTALL_LIBRARY_DIR}
			OPTIONAL)
endif( WIN32 )

# install CMake Find<Module> file
install(	FILES ${CMAKE_CURRENT_BINARY_DIR}/misc/Find${PROJECT_NAME}.cmake
			DESTINATION ${INSTALL_CMAKE_DIR})

# install MediTEC-specific files			
add_meditec_install_routines()

############################################
# Process unit tests
############################################

if( BUILD_TEST )
#	add_subdirectory(test)
endif()

############################################
# Doxygen API documentation
############################################

if( BUILD_DOC )
	add_subdirectory(src/doc)
endif()

############################################
