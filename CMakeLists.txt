# Check if cmake has the required version
CMAKE_MINIMUM_REQUIRED(VERSION 3.9.4 FATAL_ERROR)

# Set project version
SET(TAIGAROOT_VERSION 1)

# Set name of our project to "TAIGAROOT".
# Has to be done after check of cmake version
# This also sets ${TAIGAROOT_VERSION} to the provided VERSION value, which would be empty if not set here explicitly
project(TAIGAROOT VERSION ${TAIGAROOT_VERSION})

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/
# is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(TAIGAROOT_LIBRARY_PROPERTIES ${TAIGAROOT_LIBRARY_PROPERTIES}
      VERSION "${TAIGAROOT_VERSION}")

# Load some basic macros which are needed later on
include(TaigaMacro)
include(WriteConfigFile)


set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(PATH $ENV{PATH})

# Check if we are on an UNIX system. If not stop with an error
# message
IF(NOT UNIX)
  MESSAGE(FATAL_ERROR "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory.")
ENDIF(NOT UNIX)


find_package(ROOT 6.00.00 REQUIRED)


# Recurse into the given subdirectories.  This does not actually
# cause another cmake executable to run.  The same process will walk through
# the project's entire directory structure.
add_subdirectory (objects)

WRITE_CONFIG_FILE(config.sh)
WRITE_CONFIG_FILE(config.csh)

#Install(FILES ${CMAKE_BINARY_DIR}/config.sh_install
#        DESTINATION bin
#        RENAME TaigaRootConfig.sh
#       )

#Install(FILES ${CMAKE_BINARY_DIR}/check_system.sh
#       DESTINATION bin
#       )

#Install(FILES ${CMAKE_BINARY_DIR}/config.csh_install
#        DESTINATION bin
#        RENAME TaigaRootConfig.csh
#       )

#Install(FILES ${CMAKE_BINARY_DIR}/check_system.csh
#        DESTINATION bin
#       )

#Install(DIRECTORY cmake
#        DESTINATION share/fairbase
#        PATTERN ".svn" EXCLUDE)
