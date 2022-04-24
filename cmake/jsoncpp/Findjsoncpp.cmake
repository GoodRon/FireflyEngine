#.rst:
# Findjsoncpp
# --------
#
# Find jsoncpp
#
# Find the jsoncpp headers and libraries.
#
# ::
#
#   jsoncpp_INCLUDE_DIRS   - where to find json/json.h, etc.
#   jsoncpp_LIBRARIES      - List of libraries when using jsoncpp.
#   jsoncpp_FOUND          - True if jsoncpp found.
#   jsoncpp_VERSION_STRING - the version of jsoncpp found (since CMake 2.8.8)
#
# Hints
# ^^^^^
#
# A user may set ``JSONCPP_ROOT`` to a jsoncpp installation root to tell this
# module where to look.

# Look for the header file.
find_path(jsoncpp_INCLUDE_DIR NAMES
    json/json.h
    HINTS "${JSONCPP_ROOT}/include"
)
mark_as_advanced(jsoncpp_INCLUDE_DIR)

# Look for the library (sorted from most current/relevant entry to least).
find_library(jsoncpp_LIBRARY NAMES
    jsoncpp
    HINTS "${JSONCPP_ROOT}/lib"
)
mark_as_advanced(jsoncpp_LIBRARY)

if (jsoncpp_INCLUDE_DIR AND (EXISTS "${jsoncpp_INCLUDE_DIR}/json/version.h"))
    file(STRINGS "${jsoncpp_INCLUDE_DIR}/json/version.h" jsoncpp_version_str
        REGEX "^# define JSONCPP_VERSION_STRING \".*\""
    )
    string(REGEX REPLACE "^# define JSONCPP_VERSION_STRING \"([^\"]*)\"" "\\1"
        jsoncpp_VERSION_STRING "${jsoncpp_version_str}"
    )
    unset(jsoncpp_version_str)
endif()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(jsoncpp
    REQUIRED_VARS jsoncpp_LIBRARY jsoncpp_INCLUDE_DIR
    VERSION_VAR jsoncpp_VERSION_STRING
)

if (jsoncpp_FOUND)
    set(jsoncpp_LIBRARIES ${jsoncpp_LIBRARY})
    set(jsoncpp_INCLUDE_DIRS ${jsoncpp_INCLUDE_DIR})

    # Define imported targets

    add_library(jsoncpp UNKNOWN IMPORTED)
    set_target_properties(jsoncpp PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${jsoncpp_INCLUDE_DIRS}"
    )
    set_target_properties(jsoncpp PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${jsoncpp_LIBRARIES}"
    )
endif()