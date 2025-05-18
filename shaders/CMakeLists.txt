project(Shaders)

if(DEFINED COMPILE_SHADERS)
    file(GLOB SHADERS
        ${SDLPG_SHADER_DIR}/*.vert
        ${SDLPG_SHADER_DIR}/*.frag
        ${SDLPG_SHADER_DIR}/*.comp
        ${SDLPG_SHADER_DIR}/*.geom
        ${SDLPG_SHADER_DIR}/*.tesc
        ${SDLPG_SHADER_DIR}/*.tese
        ${SDLPG_SHADER_DIR}/*.mesh
        ${SDLPG_SHADER_DIR}/*.task
        ${SDLPG_SHADER_DIR}/*.rgen
        ${SDLPG_SHADER_DIR}/*.rchit
        ${SDLPG_SHADER_DIR}/*.rmiss
    )

    message(STATUS "===== COMPILING SHADERS =====")

    foreach(SHADER IN LISTS SHADERS)
        get_filename_component(FILENAME ${SHADER} NAME)
        add_custom_command(OUTPUT ${SDLPG_SHADER_DIR}/${FILENAME}.spv
            COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${SHADER} -o ${SDLPG_SHADER_DIR}/${FILENAME}.spv
            DEPENDS ${SHADER}
            COMMENT "Compiling ${FILENAME}")
        message("       >> ${FILENAME}.spv")
        list(APPEND SPV_SHADERS ${SDLPG_SHADER_DIR}/${FILENAME}.spv)
    endForeach()

    add_custom_target(${PROJECT_NAME} ALL DEPENDS ${SPV_SHADERS})

    message(STATUS "===== DONE COMPILING SHADERS =====")

else()
    message(STATUS "===== SKIPPING COMPILING SHADERS =====")
    message(STATUS "        If you want to compile shaders, use the -s option on the build script")
    message(STATUS "        or alternatively pass the argument -DCOMPILE_SHADERS=1 when invoking CMake")
endif()
