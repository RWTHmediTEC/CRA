############################################
# Locates MathBib library.
# ------------------------------------------
# If MathBib headers and library files are
# not found in the standard CMake locations,
# then %MEDITEC_LIBS%/MathBib/<version>
# is checked. In this, letter case it is
# necessary that the version is matched
# exactly. Consider using symbolic links
# when you have a compatible version.
#-------------------------------------------
# The following variables are set:
#	MATHBIB_INCLUDE_DIR		points to headers
#	MATHBIB_LIBRARIES		points to lib files
#	MATHBIB_FOUND			indicates success
#-------------------------------------------
# Leonid Kostrykin, 18.12.2014
############################################

find_path(	MATHBIB_INCLUDE_DIR
			MathBib/MathUtils.h MathBib/Matrix.h MathBib/P2PRegistration.h MathBib/Vector.h
			PATHS ENV MEDITEC_LIBS
			PATH_SUFFIXES "MathBib/${MathBib_FIND_VERSION}/include"
			DOC "MathBib headers")
			
############################################
# Find RELEASE libraries
############################################

find_library(	MATHBIB_LIBRARY_RELEASE
				NAMES "MathBib-${MathBib_FIND_VERSION}" "MathBib"
				PATHS ENV MEDITEC_LIBS
				PATH_SUFFIXES "MathBib/${MathBib_FIND_VERSION}/bin"
				DOC "MathBib library (release)")
			
############################################
# Find DEBUG libraries
############################################

find_library(	MATHBIB_LIBRARY_DEBUG
				NAMES "MathBib-${MathBib_FIND_VERSION}d" "MathBibd"
				PATHS ENV MEDITEC_LIBS
				PATH_SUFFIXES "MathBib/${MathBib_FIND_VERSION}/bin"
				DOC "MathBib library (debug)")

# handles REQUIRED, QUIET and version-related
# arguments and also sets the _FOUND variable
find_package_handle_standard_args(MATHBIB
	REQUIRED_VARS MATHBIB_INCLUDE_DIR
	MATHBIB_LIBRARY_RELEASE
	MATHBIB_LIBRARY_DEBUG)

# set paths to library files
if( MATHBIB_FOUND )
	set( MATHBIB_LIBRARIES
			optimized	${MATHBIB_LIBRARY_RELEASE}
			debug		${MATHBIB_LIBRARY_DEBUG} )
endif()