function(define_filename_macro)
    foreach(_source IN ITEMS ${ARGN})
        file(RELATIVE_PATH relpath ${CMAKE_SOURCE_DIR} ${_source})
        set_property(
            SOURCE "${_source}" APPEND
            PROPERTY COMPILE_DEFINITIONS "__FILENAME__=\"${relpath}\"")
    endforeach()
endfunction()
