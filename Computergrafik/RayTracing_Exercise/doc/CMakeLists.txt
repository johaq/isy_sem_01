find_package(Doxygen)

if(DOXYGEN_FOUND STREQUAL "NO")
  message(STATUS "Doxygen not found. Please get a copy http://www.doxygen.org")
endif()

# prepare doxygen configuration file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# add doxygen as target
add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)


# cleanup $build/html on "make clean"
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES html)
