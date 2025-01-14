# ==========================================================
# ================ FILE LOCATIONS MODULE ===================
# ==========================================================
# Module description:
#   This module is in charge of defining all the file
#   locations for the project. It also defines the
#   functions to add the files to the targets which must
#   be called in the CMakeLists.txt file of the project.


# **********************************************************
# ~~~~~~~~~~~~~~~~~~ Module initialization ~~~~~~~~~~~~~~~~~
# **********************************************************


# ----------------------------------------------------------
# Function: link_common_static_libs
# Description:
#   This function links the common libraries that the
#   project depends on to the target.
# Parameters:
#   target: The target to link the libraries to.
# ----------------------------------------------------------
function(set_new_dir dir_var dir_name)
    assert_not_empty(${dir_var})
    assert_not_empty(${dir_name})
    set(${dir_var} ${dir_name} CACHE INTERNAL "" FORCE)
    verbose_info("Created variable ${dir_var} for directory: ${dir_name}")
endfunction()
# ----------------------------------------------------------
# Function: set_all_files_of_type
# Description:
#   This function finds all the files of the given type
#   in the given directory and its subdirectories and
#   stores them in the given variable.
# Parameters:
#   var_name: The name of the variable to store the files in
#   dir: The directory to search in
# ----------------------------------------------------------
function(set_all_files_of_type var_name dir ext)
    assert_not_empty(${var_name})
    assert_not_empty(${dir})
    assert_not_empty(${ext})

    verbose_info("Finding all files of type ${ext} in directory ${dir}")
    file(GLOB_RECURSE temp_var ${dir}/*.${ext})
    set(${var_name} ${temp_var} CACHE INTERNAL "" FORCE)
    verbose_info("Variable created ${var_name} for files with extension ${ext} in directory ${dir}
\t\tFiles found: ${temp_var}")
endfunction()


verbose_info("----Defining directories and files----")

# ...................... Binary Dirs .......................
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/bin)
set_new_dir(BIN_DIR
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_new_dir(BIN_DIR
            ${BIN_DIR}/debug)
else ()
    set_new_dir(BIN_DIR
            ${BIN_DIR}/release)
endif ()

set_new_dir(BIN_BIN_LOCATION .)

set_new_dir(ASSETS_BIN_LOCATION .)
set_new_dir(ASSETS_BIN_DIR /assets)
set_new_dir(ASSETS_SOUND_BIN_DIR ${ASSETS_BIN_DIR}/sounds)
set_new_dir(ASSETS_SHADER_BIN_DIR ${ASSETS_BIN_DIR}/shaders)
set_new_dir(ASSETS_FONTS_BIN_DIR ${ASSETS_BIN_DIR}/fonts)
set_new_dir(ASSETS_IMAGES_BIN_DIR ${ASSETS_BIN_DIR}/images)
set_new_dir(ASSETS_IMAGES_CUBEMAPS_BIN_DIR ${ASSETS_IMAGES_BIN_DIR}/cubemaps)
set_new_dir(ASSETS_IMAGES_TEXTURES_BIN_DIR ${ASSETS_IMAGES_BIN_DIR}/textures)
set_new_dir(ASSETS_IMAGES_SPRITES_BIN_DIR ${ASSETS_IMAGES_BIN_DIR}/sprites)
set_new_dir(ASSETS_IMAGES_ICONS_BIN_DIR ${ASSETS_IMAGES_BIN_DIR}/icons)
set_new_dir(ASSETS_IMAGES_CUBEMAPS_BIN_DIR ${ASSETS_IMAGES_BIN_DIR}/cubemaps)
set_new_dir(ASSETS_IMAGES_CUBEMAPS_SKYBOXES_BIN_DIR ${ASSETS_IMAGES_CUBEMAPS_BIN_DIR}/skybox)
# ..........................................................

# ..................... Project Dirs .......................
# Set the source directory, this is where the source files
# are located
set_new_dir(SRC_DIR src)
# Set the include directory, this is where the header files
# are located
set_new_dir(SHADER_DEV_DIR ${CMAKE_SOURCE_DIR}/src/engine/subsystems/renderer/shaders)
# Set the assets directory, this is where the assets are
# located
set_new_dir(INCLUDE_DIR include)

set_new_dir(BIN_DEV_DIR ${CMAKE_SOURCE_DIR}/lib/bin)

set_new_dir(ASSETS_DEV_DIR ${CMAKE_SOURCE_DIR}/assets)
set_new_dir(ASSETS_SOUND_DEV_DIR ${ASSETS_DEV_DIR}/sounds)
set_new_dir(ASSETS_SHADER_DEV_DIR ${ASSETS_DEV_DIR}/shaders)
set_new_dir(ASSETS_FONTS_DEV_DIR ${ASSETS_DEV_DIR}/fonts)
set_new_dir(ASSETS_IMAGES_DEV_DIR ${ASSETS_DEV_DIR}/images)
set_new_dir(ASSETS_IMAGES_CUBEMAPS_DEV_DIR ${ASSETS_IMAGES_DEV_DIR}/cubemaps)
set_new_dir(ASSETS_IMAGES_TEXTURES_DEV_DIR ${ASSETS_IMAGES_DEV_DIR}/textures)
set_new_dir(ASSETS_IMAGES_SPRITES_DEV_DIR ${ASSETS_IMAGES_DEV_DIR}/sprites)
set_new_dir(ASSETS_IMAGES_ICONS_DEV_DIR ${ASSETS_IMAGES_DEV_DIR}/icons)
set_new_dir(ASSETS_IMAGES_CUBEMAPS_DEV_DIR ${ASSETS_IMAGES_DEV_DIR}/cubemaps)
# ..........................................................

# ..................... Library Dirs .......................
# Set the include directory for the library, this is where
# the library header files are located
set_new_dir(LIB_INCLUDE_DIR lib/include)
# Set the source directory for the library, this is where
# the library source files are located.
# Src and include are the same for the library.
set_new_dir(LIB_SRC_DIR ${LIB_INCLUDE_DIR})
# Set the static library directory, this is where the static
# library files (.a extension) are located.
# These libraries will be linked to the project and will be
# directly included in the binary increase the binary size.
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_new_dir(LIB_STATIC_DIR lib/lib)
else ()
    set_new_dir(LIB_STATIC_DIR lib/lib)
endif ()
# ..........................................................

# ....................... Test Dirs ........................
set_new_dir(TEST_DIR tests)
# ..........................................................



# ...................... Source Files ......................
# We're using GLOB_RECURSE to obtain all the files in the
# directories.
# It will be necessary to re-run cmake if you add new files
# to the project.
set_all_files_of_type(SOURCE_FILES ${SRC_DIR} cpp)
set_all_files_of_type(LIB_SOURCE_FILES ${LIB_SRC_DIR} cpp)
set_all_files_of_type(TEST_SOURCE_FILES ${TEST_DIR} cpp)
# ..........................................................


# **********************************************************
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# **********************************************************


# ----------------------------------------------------------
# Function: set_common_include_dirs
# Description:
#   This function adds the common include directories to the
#   given target.
# Parameters:
#   target: The target to add the include directories to.
# ----------------------------------------------------------
function(set_common_include_dirs target)
    important_info("Adding include directories of the project to target ${target}")
    assert_not_empty(${target})
    assert_not_empty(${INCLUDE_DIR})
    assert_not_empty(${LIB_INCLUDE_DIR})
    assert_not_empty(${Boost_INCLUDE_DIRS})
    target_include_directories(${target} SYSTEM PRIVATE
            ${INCLUDE_DIR} ${LIB_INCLUDE_DIR}
            ${Boost_INCLUDE_DIRS})

    success("Added include directories to ${target}:
\t\tProject Include Directory: ${INCLUDE_DIR}
\t\tLibrary Include Directory: ${LIB_INCLUDE_DIR}
\t\tBoost Include Directories: ${Boost_INCLUDE_DIRS}")

endfunction()
# ----------------------------------------------------------
# Function: add_extra_include_dirs
# Description:
#   This function adds extra include directories to the
#   given target. Must be used in case the target needs
#   to include directories that are not in the common
#   include directories.
# Parameters:
#  target: The target to add the include directories to.
#  dirs: The directories to add to the target.
# ----------------------------------------------------------
function(add_extra_include_dirs target dirs)
    assert_not_empty(${target})
    assert_not_empty(dirs)

    important_info("Adding extra include directories to target ${target}")

    target_include_directories(${target} PRIVATE ${dirs})

    success("Added include directories to target ${target}:
\t\t ${dirs}")
endfunction()


# ----------------------------------------------------------
# Function: set_common_static_lib_dirs
# Description:
#   This function adds the common static library directories
#   to the given target. This is needed before linking the
#   libraries to the target.
# Parameters:
#   target: The target to add the static library directories.
# ----------------------------------------------------------
function(set_common_link_lib_dirs target)
    important_info("Adding static library directories of the project to target ${target}")
    assert_not_empty(${target})
    target_link_directories(${target} PRIVATE ${LIB_STATIC_DIR})

    success("Added static library directories to target ${target}: ${LIB_STATIC_DIR}")
endfunction()
# ----------------------------------------------------------
# Function: add_extra_static_lib_dirs
# Description:
#   This function adds extra static library directories to
#   the given target. This must be done before linking the
#   libraries to the target.
# Parameters:
#   target: The target to add the static library directories.
# ----------------------------------------------------------
function(add_extra_link_lib_dirs target dirs)
    assert_not_empty(${target})
    assert_not_empty(${dirs})
    info("Adding extra static library directories to target ${target}")
    target_link_directories(${target} PRIVATE ${dirs})
    verbose_info("Added static library directories to target ${target}:
\t\t${dirs}")
endfunction()


# ----------------------------------------------------------
# Function: set_common_sources
# Description:
#   This function sets all the common sources to the given
#   target.
# Parameters:
#   target: The target to add the static library directories.
# ----------------------------------------------------------
function(set_common_sources target)
    assert_not_empty(${target})
    assert_not_empty(${SOURCE_FILES})
    assert_not_empty(${LIB_SOURCE_FILES})
    important_info("Adding common sources to target ${target}")
    target_sources(${target} PRIVATE
            # These are the source files for the project
            ${SOURCE_FILES}
            # These are the source files for the libraries
            ${LIB_SOURCE_FILES}
    )
    success("Added common sources to target ${target}:
\t\tSource Files: ${SOURCE_FILES}
\t\tLibrary Source Files: ${LIB_SOURCE_FILES}")
endfunction()
# ----------------------------------------------------------
# Function: add_extra_sources
# Description:
#   This function adds extra sources to the given target.
#   This is needed in case the target needs to include
#   sources that are not in the common sources.
# Parameters:
#   target: The target to add the static library directories.
#   srcs: The sources to add to the target.
# ----------------------------------------------------------
function(add_extra_sources target srcs)
    assert_not_empty(${target})
    assert_not_empty(${srcs})

    important_info("Adding extra sources to ${target}")
    target_sources(${target} PRIVATE ${srcs})
    success("Added extra sources to target ${target}:
\t\tExtra sources: ${srcs}")
endfunction()