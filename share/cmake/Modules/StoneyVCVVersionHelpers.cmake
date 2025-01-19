## REQUIREMENTS: rack-sdk 2.5.2

macro(stoneyvcv_git_versions)

    # https://softwareengineering.stackexchange.com/questions/141973/how-do-you-achieve-a-numeric-versioning-scheme-with-git
    # 'git rev-list HEAD | wc -l'
    find_package(Git REQUIRED)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" "rev-list" "HEAD"
        COMMAND "wc" "-l"
        WORKING_DIRECTORY "${STONEYVCV_SOURCE_DIR}"
        OUTPUT_VARIABLE _STONEYVCV_GIT_COMMIT_COUNT
        ERROR_VARIABLE _STONEYVCV_GIT_COMMIT_COUNT_ERROR
    )
    if(_STONEYVCV_GIT_COMMIT_COUNT_ERROR)
        message(SEND_ERROR "${_STONEYVCV_GIT_COMMIT_COUNT_ERROR}")
    endif()
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" "rev-parse" "HEAD"
        WORKING_DIRECTORY "${STONEYVCV_SOURCE_DIR}"
        OUTPUT_VARIABLE _STONEYVCV_GIT_REF_HEAD
        ERROR_VARIABLE _STONEYVCV_GIT_REF_HEAD_ERROR
    )
    if(_STONEYVCV_GIT_REF_HEAD_ERROR)
        message(SEND_ERROR "${_STONEYVCV_GIT_REF_HEAD_ERROR}")
    endif()
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" "rev-parse" "--short" "HEAD"
        WORKING_DIRECTORY "${STONEYVCV_SOURCE_DIR}"
        OUTPUT_VARIABLE _STONEYVCV_GIT_REF_HEAD_SHORT
        ERROR_VARIABLE _STONEYVCV_GIT_REF_HEAD_SHORT_ERROR
    )
    if(_STONEYVCV_GIT_REF_HEAD_SHORT_ERROR)
        message(SEND_ERROR "${_STONEYVCV_GIT_REF_HEAD_SHORT_ERROR}")
    endif()
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" rev-parse --abbrev-ref --symbolic-full-name HEAD
        WORKING_DIRECTORY "${STONEYVCV_SOURCE_DIR}"
        OUTPUT_VARIABLE _STONEYVCV_GIT_BRANCH
        ERROR_VARIABLE _STONEYVCV_GIT_BRANCH_ERROR
    )
    if(_STONEYVCV_GIT_BRANCH_ERROR)
        message(SEND_ERROR "${_STONEYVCV_GIT_BRANCH_ERROR}")
    endif()
    string(STRIP "${_STONEYVCV_GIT_COMMIT_COUNT}" STONEYVCV_GIT_COMMIT_COUNT)
    string(STRIP "${_STONEYVCV_GIT_REF_HEAD}" _STONEYVCV_GIT_REF_HEAD)
    string(STRIP "${_STONEYVCV_GIT_REF_HEAD_SHORT}" _STONEYVCV_GIT_REF_HEAD_SHORT)
    string(STRIP "${_STONEYVCV_GIT_BRANCH}" STONEYVCV_GIT_BRANCH)

    string(HEX "${_STONEYVCV_GIT_REF_HEAD}" STONEYVCV_GIT_REF_HEAD)
    string(HEX "${_STONEYVCV_GIT_REF_HEAD_SHORT}" STONEYVCV_GIT_REF_HEAD_SHORT)

    file(READ "${STONEYVCV_SOURCE_DIR}/plugin.json" STONEYVCV_PLUGIN_JSON)
    string(CONFIGURE "2.0.@STONEYVCV_GIT_COMMIT_COUNT@" _STONEYVCV_PLUGIN_JSON_VERSION @ONLY)
    string(JSON _STONEYVCV_PLUGIN_JSON ERROR_VARIABLE _STONEYVCV_PLUGIN_JSON_SET_ROOT_ERROR SET "${STONEYVCV_PLUGIN_JSON}" "version" "\"${_STONEYVCV_PLUGIN_JSON_VERSION}\"")

    if(_STONEYVCV_PLUGIN_JSON_SET_ROOT_ERROR)
        message(FATAL_ERROR "${_STONEYVCV_PLUGIN_JSON_SET_ROOT_ERROR}")
    endif(_STONEYVCV_PLUGIN_JSON_SET_ROOT_ERROR)

    file(WRITE "${STONEYVCV_SOURCE_DIR}/plugin.json.tmp" "${_STONEYVCV_PLUGIN_JSON}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${STONEYVCV_SOURCE_DIR}/plugin.json.tmp" "${STONEYVCV_SOURCE_DIR}/plugin.json")
    file(REMOVE "${STONEYVCV_SOURCE_DIR}/plugin.json.tmp")

    unset(_STONEYVCV_PLUGIN_JSON)
    unset(_STONEYVCV_PLUGIN_JSON_VERSION)

endmacro(stoneyvcv_git_versions)

macro(stoneyvcv_update_version_file)

    if(NOT "${VCVRACK_PLUGIN_VERSION}" STREQUAL "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}")
        set(_STONEYVCV_ERROR_STRING [==[

    There is a mismatch between plugin versions in 'plugin.json' and 'CMakeLists.txt':
    plugin.json#version: @VCVRACK_PLUGIN_VERSION@
    project(VERSION @STONEYVCV_VERSION_MAJOR@.@STONEYVCV_VERSION_MINOR@.@STONEYVCV_VERSION_PATCH@
    Please update the version number in the following files in order to silence this error:
    @STONEYVCV_SOURCE_DIR@/plugin.json
    @STONEYVCV_SOURCE_DIR@/CMakeLists.txt
        ]==])
        string(CONFIGURE "${_STONEYVCV_ERROR_STRING}" STONEYVCV_ERROR_STRING @ONLY)
        if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
            message(SEND_ERROR "${STONEYVCV_ERROR_STRING}")
            return()
        elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
            message(WARNING "${STONEYVCV_ERROR_STRING}")
        endif()
    endif()

    set(STONEYVCV_VERSION_FILE "${STONEYVCV_SOURCE_DIR}/VERSION")
    file(WRITE "${STONEYVCV_VERSION_FILE}.tmp" "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}.${STONEYVCV_VERSION_TWEAK}\n")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${STONEYVCV_VERSION_FILE}.tmp" "${STONEYVCV_VERSION_FILE}")
    file(REMOVE "${STONEYVCV_VERSION_FILE}.tmp")
    set(STONEYVCV_VERSION_FILE "${STONEYVCV_VERSION_FILE}" CACHE INTERNAL "StoneyVCV current version file." FORCE)

endmacro()

macro(stoneyvcv_git_module_versions MODULE)
    set(${MODULE}_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}")
    set(${MODULE}_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}")
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" rev-list origin/module/${MODULE}
        COMMAND wc -l
        OUTPUT_VARIABLE ${MODULE}_VERSION_PATCH
        ERROR_VARIABLE _${MODULE}_VERSION_PATCH
    )
    if(${_${MODULE}_VERSION_PATCH})
        message(WARNING "git: could not find a corresponding module/${MODULE} branch for module ${MODULE}")
    endif()
    string(STRIP "${${MODULE}_VERSION_PATCH}" ${MODULE}_VERSION_PATCH)
    set(${MODULE}_VERSION "${${MODULE}_VERSION_MAJOR}.${${MODULE}_VERSION_MINOR}.${${MODULE}_VERSION_PATCH}")
endmacro()
