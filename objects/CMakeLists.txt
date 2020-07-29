# Create a library called "libTAIGAObjects" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/objects
)

include_directories( ${INCLUDE_DIRECTORIES})

link_directories( ${ROOT_LIBRARY_DIR})

set(SRCS
TAIGAPixel.cxx
TAIGACluster.cxx
TAIGAEvent.cxx
TAIGACamera.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF TAIGAObjectsLinkDef.h)
set(LIBRARY_NAME TAIGAObjects)
set(DEPENDENCIES Core)

GENERATE_LIBRARY()

