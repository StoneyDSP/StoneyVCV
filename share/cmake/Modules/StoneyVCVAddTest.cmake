function(stoneyvcv_add_catch2)

    set(tests_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}")
    set(tests_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}")
    set(tests_VERSION_PATCH "${STONEYVCV_VERSION_PATCH}")
    set(tests_VERSION "${tests_VERSION_MAJOR}.${tests_VERSION_MINOR}.${tests_VERSION_PATCH}")

    add_executable(tests)
    add_executable(StoneyVCV::tests ALIAS tests)
    add_executable(${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::tests ALIAS tests)
    target_include_directories(tests
        PUBLIC
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    configure_file("test/${STONEYVCV_SLUG}/test.hpp" "test/${STONEYVCV_SLUG}/test.hpp")
    target_sources(tests
        PUBLIC
        FILE_SET stoneyvcv_TESTS_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/test>
        $<INSTALL_INTERFACE:test>
        FILES
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/test/${STONEYVCV_SLUG}/test.hpp>
        $<INSTALL_INTERFACE:test/${STONEYVCV_SLUG}/test.hpp>
    )
    target_link_libraries(tests
        PUBLIC
            unofficial-vcvrack::rack-sdk::lib
            ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}
            ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::plugin
            Catch2::Catch2WithMain
    )
    set_target_properties(tests
        PROPERTIES
        VERSION "${tests_VERSION}"
        SOVERSION "${tests_VERSION_MAJOR}"
        RUNTIME_OUTPUT_DIRECTORY "${STONEYVCV_BINARY_DIR}/test"
        RUNTIME_OUTPUT_NAME "tests"
    )
    target_compile_features(tests PUBLIC cxx_std_17)
    target_compile_features(tests PUBLIC c_std_17)
    target_compile_definitions(tests
        PUBLIC
        "-Dtests_VERSION_MAJOR=${tests_VERSION_MAJOR}"
        "-Dtests_VERSION_MINOR=${tests_VERSION_MINOR}"
        "-Dtests_VERSION_PATCH=${tests_VERSION_PATCH}"
        "-Dtests_VERSION=${tests_VERSION}"
    )
    if(STONEYVCV_BUILD_PLUGIN)
        target_compile_definitions(tests
            PUBLIC
                "-DSTONEYVCV_BUILD_PLUGIN=1"
        )
    endif()
    if(STONEYVCV_BUILD_MODULES)
        target_compile_definitions(tests
            PUBLIC
                "-DSTONEYVCV_BUILD_MODULES=1"
        )
    endif()
    set(tests_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}" PARENT_SCOPE)
    set(tests_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}" PARENT_SCOPE)
    set(tests_VERSION_PATCH "${STONEYVCV_VERSION_PATCH}" PARENT_SCOPE)
    set(tests_VERSION "${tests_VERSION_MAJOR}.${tests_VERSION_MINOR}.${tests_VERSION_PATCH}")
    message(STATUS "Added target: ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::tests v${tests_VERSION}")

endfunction()

function(stoneyvcv_add_test MODULE)

    set(tests_${MODULE}_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}")
    set(tests_${MODULE}_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}")
    set(tests_${MODULE}_VERSION_PATCH "${STONEYVCV_VERSION_PATCH}")
    set(tests_${MODULE}_VERSION "${tests_${MODULE}_VERSION_MAJOR}.${tests_${MODULE}_VERSION_MINOR}.${tests_${MODULE}_VERSION_PATCH}")

    add_library(tests_${MODULE} OBJECT EXCLUDE_FROM_ALL)
    add_library(${STONEYVCV_SLUG}::tests_${MODULE} ALIAS tests_${MODULE})
    add_library(${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::tests_${MODULE} ALIAS tests_${MODULE})
    set_target_properties(tests_${MODULE}
        PROPERTIES
            VERSION "${tests_${MODULE}_VERSION}"
            SOVERSION "${tests_${MODULE}_VERSION_MAJOR}"
        )
    target_include_directories(tests_${MODULE}
        PUBLIC
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    target_sources(tests_${MODULE}
        PRIVATE
            "${STONEYVCV_SOURCE_DIR}/test/${STONEYVCV_SLUG}/${MODULE}.cpp"
    )
    target_link_libraries(tests_${MODULE}
        PUBLIC
            unofficial-vcvrack::rack-sdk::core
            ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::${MODULE}
            Catch2::Catch2
    )
    target_compile_definitions(tests_${MODULE}
        PUBLIC
            "-Dtests_${MODULE}_VERSION_MAJOR=${tests_${MODULE}_VERSION_MAJOR}"
            "-Dtests_${MODULE}_VERSION_MINOR=${tests_${MODULE}_VERSION_MINOR}"
            "-Dtests_${MODULE}_VERSION_PATCH=${tests_${MODULE}_VERSION_PATCH}"
            "-Dtests_${MODULE}_VERSION=${tests_${MODULE}_VERSION}"
    )
    target_compile_features(tests_${MODULE} PUBLIC cxx_std_17)
    target_compile_features(tests_${MODULE} PUBLIC c_std_17)
    set(tests_${MODULE}_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}" PARENT_SCOPE)
    set(tests_${MODULE}_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}" PARENT_SCOPE)
    set(tests_${MODULE}_VERSION_PATCH "${STONEYVCV_VERSION_PATCH}" PARENT_SCOPE)
    set(tests_${MODULE}_VERSION "${tests_${MODULE}_VERSION_MAJOR}.${tests_${MODULE}_VERSION_MINOR}.${tests_${MODULE}_VERSION_PATCH}" PARENT_SCOPE)

    message(STATUS "Added target: ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::tests_${MODULE} v${tests_${MODULE}_VERSION}")

endfunction()
