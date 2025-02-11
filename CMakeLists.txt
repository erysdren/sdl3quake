cmake_minimum_required(VERSION 3.30)
project(sdl3quake LANGUAGES C VERSION 0.1.0)

# get libm (not required on all platforms)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package(Math)

# get SDL3
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

# build-time options
set(SDL3QUAKE_GAMEDIR "id1" CACHE STRING "Base game directory")
set(SDL3QUAKE_GAMETITLE "Quake" CACHE STRING "Displayed game title")
set(SDL3QUAKE_GAMEEXEC "quake.rc" CACHE STRING "Default script to execute at engine start (relative to base game directory)")
set(SDL3QUAKE_GAMEVERSION "1.09" CACHE STRING "Displayed game version (must be numeric)")

# grab all sources
file(GLOB SDL3QUAKE_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.c")

# setup executable
add_executable(sdl3quake ${SDL3QUAKE_SOURCES})

# link stuff
target_link_libraries(sdl3quake PUBLIC
	SDL3::SDL3
	$<TARGET_NAME_IF_EXISTS:Math::Math>
)

# add config options
target_compile_definitions(sdl3quake PUBLIC
	GAMEDIR=$<QUOTE>$<PATH:CMAKE_PATH,${SDL3QUAKE_GAMEDIR}>$<QUOTE>
	GAMETITLE=$<QUOTE>${SDL3QUAKE_GAMETITLE}$<QUOTE>
	GAMEEXEC=$<QUOTE>$<PATH:CMAKE_PATH,${SDL3QUAKE_GAMEEXEC}>$<QUOTE>
	GAMEVERSION=${SDL3QUAKE_GAMEVERSION}
)

# require C23
set_target_properties(sdl3quake PROPERTIES C_STANDARD_REQUIRED ON C_STANDARD 23)
