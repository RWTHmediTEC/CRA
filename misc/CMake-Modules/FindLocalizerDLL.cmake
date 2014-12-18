############################################
# Locates LocalizerDLL library.
# ------------------------------------------
# If LocalizerDLL headers and library files
# are not found in the standard CMake
# locations, then %MEDITEC_LIBS%/LocalizerDLL/<version>
# is checked. In this, letter case it is
# necessary that the version is matched
# exactly. Consider using symbolic links
# when you have a compatible version.
#-------------------------------------------
# The following variables are set:
#	LOCALIZERDLL_INCLUDE_DIR	points to headers
#	LOCALIZERDLL_LIBRARIES		points to lib files
#	LOCALIZERDLL_FOUND			indicates success
#-------------------------------------------
# Leonid Kostrykin, 18.12.2014
############################################

find_path(	LOCALIZERDLL_INCLUDE_DIR
			localizerDll/Localizer.h
			PATHS ENV MEDITEC_LIBS
			PATH_SUFFIXES "localizerDll/${LocalizerDLL_FIND_VERSION}/include"
			DOC "LocalizerDLL headers")
			
############################################
# Find RELEASE libraries
############################################

find_library(	LOCALIZERDLL_LIBRARY_RELEASE
				NAMES "LocalizerDLL-${LocalizerDLL_FIND_VERSION}" "LocalizerDLL"
				PATHS ENV MEDITEC_LIBS
				PATH_SUFFIXES "LocalizerDLL/${LocalizerDLL_FIND_VERSION}/bin"
				DOC "LocalizerDLL library (release)")
			
############################################
# Find DEBUG libraries
############################################

find_library(	LOCALIZERDLL_LIBRARY_DEBUG
				NAMES "LocalizerDLL-${LocalizerDLL_FIND_VERSION}d" "LocalizerDLLd"
				PATHS ENV MEDITEC_LIBS
				PATH_SUFFIXES "LocalizerDLL/${LocalizerDLL_FIND_VERSION}/bin"
				DOC "LocalizerDLL library (debug)")

# handles REQUIRED, QUIET and version-related
# arguments and also sets the _FOUND variable
find_package_handle_standard_args(LOCALIZERDLL
	REQUIRED_VARS LOCALIZERDLL_INCLUDE_DIR
	LOCALIZERDLL_LIBRARY_RELEASE
	LOCALIZERDLL_LIBRARY_DEBUG)

# set paths to library files
if( LOCALIZERDLL_FOUND )
	set( LOCALIZERDLL_LIBRARIES
			optimized	${LOCALIZERDLL_LIBRARY_RELEASE}
			debug		${LOCALIZERDLL_LIBRARY_DEBUG} )
endif()