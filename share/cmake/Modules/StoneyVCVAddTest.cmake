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
