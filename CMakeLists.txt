cmake_minimum_required(VERSION 3.10)
project(sdl3quake LANGUAGES C VERSION 0.1.0)

find_package(SDL2 REQUIRED)

set(SDL3QUAKE_GAMEDIR "id1" CACHE STRING "Base game directory")
set(SDL3QUAKE_GAMETITLE "Quake" CACHE STRING "Displayed game title")
set(SDL3QUAKE_GAMEEXEC "quake.rc" CACHE STRING "Default script to execute at engine start")
set(SDL3QUAKE_GAMEVERSION "1.09" CACHE STRING "Displayed game version (must be numeric)")

add_library(libsdl3quake STATIC)
target_link_libraries(libsdl3quake PUBLIC SDL2::SDL2)
target_compile_definitions(libsdl3quake PUBLIC GAMEDIR=\"${SDL3QUAKE_GAMEDIR}\")
target_compile_definitions(libsdl3quake PUBLIC GAMETITLE=\"${SDL3QUAKE_GAMETITLE}\")
target_compile_definitions(libsdl3quake PUBLIC GAMEEXEC=\"${SDL3QUAKE_GAMEEXEC}\")
target_compile_definitions(libsdl3quake PUBLIC GAMEVERSION=${SDL3QUAKE_GAMEVERSION})
set_target_properties(libsdl3quake PROPERTIES OUTPUT_NAME "sdl3quake" C_STANDARD_REQUIRED ON C_STANDARD 23)
target_sources(libsdl3quake PRIVATE
	${PROJECT_SOURCE_DIR}/src/cdaudio.c
	${PROJECT_SOURCE_DIR}/src/chase.c
	${PROJECT_SOURCE_DIR}/src/cl_demo.c
	${PROJECT_SOURCE_DIR}/src/cl_input.c
	${PROJECT_SOURCE_DIR}/src/cl_main.c
	${PROJECT_SOURCE_DIR}/src/cl_parse.c
	${PROJECT_SOURCE_DIR}/src/cl_tent.c
	${PROJECT_SOURCE_DIR}/src/cmd.c
	${PROJECT_SOURCE_DIR}/src/common.c
	${PROJECT_SOURCE_DIR}/src/console.c
	${PROJECT_SOURCE_DIR}/src/crc.c
	${PROJECT_SOURCE_DIR}/src/cvar.c
	${PROJECT_SOURCE_DIR}/src/d_edge.c
	${PROJECT_SOURCE_DIR}/src/d_fill.c
	${PROJECT_SOURCE_DIR}/src/d_init.c
	${PROJECT_SOURCE_DIR}/src/d_modech.c
	${PROJECT_SOURCE_DIR}/src/d_part.c
	${PROJECT_SOURCE_DIR}/src/d_polyse.c
	${PROJECT_SOURCE_DIR}/src/d_scan.c
	${PROJECT_SOURCE_DIR}/src/d_sky.c
	${PROJECT_SOURCE_DIR}/src/d_sprite.c
	${PROJECT_SOURCE_DIR}/src/d_surf.c
	${PROJECT_SOURCE_DIR}/src/d_vars.c
	${PROJECT_SOURCE_DIR}/src/d_zpoint.c
	${PROJECT_SOURCE_DIR}/src/draw.c
	${PROJECT_SOURCE_DIR}/src/host_cmd.c
	${PROJECT_SOURCE_DIR}/src/host.c
	${PROJECT_SOURCE_DIR}/src/input.c
	${PROJECT_SOURCE_DIR}/src/keys.c
	${PROJECT_SOURCE_DIR}/src/mathlib.c
	${PROJECT_SOURCE_DIR}/src/menu.c
	${PROJECT_SOURCE_DIR}/src/model.c
	${PROJECT_SOURCE_DIR}/src/net_loop.c
	${PROJECT_SOURCE_DIR}/src/net_main.c
	${PROJECT_SOURCE_DIR}/src/net_none.c
	${PROJECT_SOURCE_DIR}/src/pr_cmds.c
	${PROJECT_SOURCE_DIR}/src/pr_edict.c
	${PROJECT_SOURCE_DIR}/src/pr_exec.c
	${PROJECT_SOURCE_DIR}/src/r_aclip.c
	${PROJECT_SOURCE_DIR}/src/r_alias.c
	${PROJECT_SOURCE_DIR}/src/r_bsp.c
	${PROJECT_SOURCE_DIR}/src/r_draw.c
	${PROJECT_SOURCE_DIR}/src/r_edge.c
	${PROJECT_SOURCE_DIR}/src/r_efrag.c
	${PROJECT_SOURCE_DIR}/src/r_light.c
	${PROJECT_SOURCE_DIR}/src/r_main.c
	${PROJECT_SOURCE_DIR}/src/r_misc.c
	${PROJECT_SOURCE_DIR}/src/r_part.c
	${PROJECT_SOURCE_DIR}/src/r_sky.c
	${PROJECT_SOURCE_DIR}/src/r_sprite.c
	${PROJECT_SOURCE_DIR}/src/r_surf.c
	${PROJECT_SOURCE_DIR}/src/r_vars.c
	${PROJECT_SOURCE_DIR}/src/sbar.c
	${PROJECT_SOURCE_DIR}/src/screen.c
	${PROJECT_SOURCE_DIR}/src/sound.c
	${PROJECT_SOURCE_DIR}/src/sv_main.c
	${PROJECT_SOURCE_DIR}/src/sv_move.c
	${PROJECT_SOURCE_DIR}/src/sv_phys.c
	${PROJECT_SOURCE_DIR}/src/sv_user.c
	${PROJECT_SOURCE_DIR}/src/sys.c
	${PROJECT_SOURCE_DIR}/src/vid.c
	${PROJECT_SOURCE_DIR}/src/view.c
	${PROJECT_SOURCE_DIR}/src/wad.c
	${PROJECT_SOURCE_DIR}/src/world.c
	${PROJECT_SOURCE_DIR}/src/zone.c
	${PROJECT_SOURCE_DIR}/src/libsdl3quake.c
)

add_executable(sdl3quake)
set_target_properties(sdl3quake PROPERTIES C_STANDARD_REQUIRED ON C_STANDARD 23)
target_link_libraries(sdl3quake PRIVATE libsdl3quake)
target_sources(sdl3quake PRIVATE
	${PROJECT_SOURCE_DIR}/src/sdl3quake.c
)

find_library(LIBMATH m)
if(LIBMATH)
	target_link_libraries(sdl3quake PRIVATE ${LIBMATH})
endif()
