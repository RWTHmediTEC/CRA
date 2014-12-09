include_directories( ${CMAKE_PROJECT_DIR}ModuleTests )

list( APPEND TESTS
		BuildTest
	)

list( APPEND TESTS_QOBJECT_HEADERS
		ModuleTests/BuildTest.h
	)

list( APPEND TESTS_HEADERS
		""
	)

list( APPEND TESTS_SOURCES
		ModuleTests/BuildTest.cpp
	)
