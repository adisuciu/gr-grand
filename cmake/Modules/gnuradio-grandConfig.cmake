find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_GRAND gnuradio-grand)

FIND_PATH(
    GR_GRAND_INCLUDE_DIRS
    NAMES gnuradio/grand/api.h
    HINTS $ENV{GRAND_DIR}/include
        ${PC_GRAND_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_GRAND_LIBRARIES
    NAMES gnuradio-grand
    HINTS $ENV{GRAND_DIR}/lib
        ${PC_GRAND_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-grandTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_GRAND DEFAULT_MSG GR_GRAND_LIBRARIES GR_GRAND_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_GRAND_LIBRARIES GR_GRAND_INCLUDE_DIRS)
