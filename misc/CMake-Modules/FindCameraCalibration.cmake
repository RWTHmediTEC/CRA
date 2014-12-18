############################################
# Locates CameraCalibration library.
# ------------------------------------------
# If CameraCalibration headers and library
# files are not found in the standard CMake
# locations, then %MEDITEC_LIBS%/CameraCalibration/<version>
# is checked. In this, letter case it is
# necessary that the version is matched
# exactly. Consider using symbolic links
# when you have a compatible version.
#-------------------------------------------
# The following variables are set:
#	CAMERACALIBRATION_INCLUDE_DIR	points to headers
#	CAMERACALIBRATION_LIBRARIES		points to lib files
#	CAMERACALIBRATION_FOUND			indicates success
#-------------------------------------------
# Leonid Kostrykin, 18.12.2014
############################################

find_path(	CAMERACALIBRATION_INCLUDE_DIR
			cameracalibration/CameraCalibration.h
			PATHS ENV MEDITEC_LIBS
			PATH_SUFFIXES "cameracalibration/${CameraCalibration_FIND_VERSION}/include"
			DOC "CameraCalibration headers")
			
############################################
# Find RELEASE libraries
############################################

find_library(	CAMERACALIBRATION_LIBRARY_RELEASE
				NAMES "CameraCalibration-${CameraCalibration_FIND_VERSION}" "CameraCalibration"
				PATHS ENV MEDITEC_LIBS
				PATH_SUFFIXES "CameraCalibration/${CameraCalibration_FIND_VERSION}/bin"
				DOC "CameraCalibration library (release)")
			
############################################
# Find DEBUG libraries
############################################

find_library(	CAMERACALIBRATION_LIBRARY_DEBUG
				NAMES "CameraCalibration-${CameraCalibration_FIND_VERSION}d" "CameraCalibrationd"
				PATHS ENV MEDITEC_LIBS
				PATH_SUFFIXES "CameraCalibration/${CameraCalibration_FIND_VERSION}/bin"
				DOC "CameraCalibration library (debug)")

# handles REQUIRED, QUIET and version-related
# arguments and also sets the _FOUND variable
find_package_handle_standard_args(CAMERACALIBRATION
	REQUIRED_VARS CAMERACALIBRATION_INCLUDE_DIR
	CAMERACALIBRATION_LIBRARY_RELEASE
	CAMERACALIBRATION_LIBRARY_DEBUG)

# set paths to library files
if( CAMERACALIBRATION_FOUND )
	set( CAMERACALIBRATION_LIBRARIES
			optimized	${CAMERACALIBRATION_LIBRARY_RELEASE}
			debug		${CAMERACALIBRATION_LIBRARY_DEBUG} )
endif()