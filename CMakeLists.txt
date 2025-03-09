cmake_minimum_required(VERSION 3.30)
project(sdl3quake LANGUAGES C VERSION 0.1.0)

# get libm (not required on all platforms)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package(Math)

# get SDL3
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_mixer REQUIRED CONFIG REQUIRED COMPONENTS SDL3_mixer-shared)

# build-time options
set(SDL3QUAKE_GAMEDIR "id1" CACHE STRING "Base game directory")
set(SDL3QUAKE_GAMETITLE "Quake" CACHE STRING "Displayed game title")
set(SDL3QUAKE_GAMEEXEC "quake.rc" CACHE STRING "Default script to execute at engine start (relative to base game directory)")
set(SDL3QUAKE_GAMEPOP "pop.lmp" CACHE STRING "Proof-of-purchase check file")
set(SDL3QUAKE_GAMEVERSION "1.09" CACHE STRING "Displayed game version (must be numeric)")
set(SDL3QUAKE_RENDERWIDTH "320" CACHE STRING "Game render width (must be numeric)")
set(SDL3QUAKE_RENDERHEIGHT "240" CACHE STRING "Game render height (must be numeric)")
option(SDL3QUAKE_USE_ASAN "Use Address Sanitizer" OFF)
option(SDL3QUAKE_USE_POP "Use proof-of-purchase check" ON)
option(SDL3QUAKE_USE_END "Show VGA end screens on quit" ON)

# grab all sources
file(GLOB SDL3QUAKE_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.c")

# setup executable
add_executable(sdl3quake ${SDL3QUAKE_SOURCES})

# link stuff
target_link_libraries(sdl3quake PUBLIC
	SDL3::SDL3
	SDL3_mixer::SDL3_mixer
	$<TARGET_NAME_IF_EXISTS:Math::Math>
)

# add config options
target_compile_definitions(sdl3quake PUBLIC
	GAMEDIR=$<QUOTE>$<PATH:CMAKE_PATH,${SDL3QUAKE_GAMEDIR}>$<QUOTE>
	GAMETITLE=$<QUOTE>${SDL3QUAKE_GAMETITLE}$<QUOTE>
	GAMEEXEC=$<QUOTE>$<PATH:CMAKE_PATH,${SDL3QUAKE_GAMEEXEC}>$<QUOTE>
	GAMEPOP=$<QUOTE>$<PATH:CMAKE_PATH,${SDL3QUAKE_GAMEPOP}>$<QUOTE>
	GAMEVERSION=${SDL3QUAKE_GAMEVERSION}
	USEGAMEPOP=$<BOOL:${SDL3QUAKE_USE_POP}>
	USEGAMEEND=$<BOOL:${SDL3QUAKE_USE_END}>
	BASEWIDTH=${SDL3QUAKE_RENDERWIDTH}
	BASEHEIGHT=${SDL3QUAKE_RENDERHEIGHT}
)

# require C23
set_target_properties(sdl3quake PROPERTIES C_STANDARD_REQUIRED ON C_STANDARD 23)

# extra warnings
if(NOT MSVC)
	target_compile_options(sdl3quake PUBLIC -Wall)
endif()

# address sanitizer
add_library(ASAN::ASAN IMPORTED INTERFACE)
target_compile_options(ASAN::ASAN INTERFACE -fsanitize=address $<$<NOT:$<COMPILE_LANG_AND_ID:C,MSVC>>:-fno-omit-frame-pointer>)
target_link_options(ASAN::ASAN INTERFACE -fsanitize=address)
target_link_libraries(sdl3quake PRIVATE $<$<BOOL:${SDL3QUAKE_USE_ASAN}>:ASAN::ASAN>)
