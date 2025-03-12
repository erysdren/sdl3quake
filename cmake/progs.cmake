
add_executable(progs
	${PROJECT_SOURCE_DIR}/src/progs/client.c
	${PROJECT_SOURCE_DIR}/src/progs/world.c
)
set_target_properties(progs PROPERTIES C_STANDARD_REQUIRED ON C_STANDARD 23)
target_compile_definitions(progs PUBLIC SERVER=1)

add_executable(csprogs
	${PROJECT_SOURCE_DIR}/src/progs/cl_main.c
)
set_target_properties(csprogs PROPERTIES C_STANDARD_REQUIRED ON C_STANDARD 23)
target_compile_definitions(csprogs PUBLIC CLIENT=1)
