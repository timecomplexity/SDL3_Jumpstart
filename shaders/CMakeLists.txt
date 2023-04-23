project(Shaders)

if(DEFINED COMPILE_SHADERS)
    file(GLOB SHADERS
        ${LV_SHADER_DIR}/*.vert
        ${LV_SHADER_DIR}/*.frag
        ${LV_SHADER_DIR}/*.comp
        ${LV_SHADER_DIR}/*.geom
        ${LV_SHADER_DIR}/*.tesc
        ${LV_SHADER_DIR}/*.tese
        ${LV_SHADER_DIR}/*.mesh
        ${LV_SHADER_DIR}/*.task
        ${LV_SHADER_DIR}/*.rgen
        ${LV_SHADER_DIR}/*.rchit
        ${LV_SHADER_DIR}/*.rmiss
    )

    message(STATUS "===== COMPILING SHADERS =====")

    foreach(SHADER IN LISTS SHADERS)
        get_filename_component(FILENAME ${SHADER} NAME)
        add_custom_command(OUTPUT ${LV_SHADER_DIR}/${FILENAME}.spv
            COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${SHADER} -o ${LV_SHADER_DIR}/${FILENAME}.spv
            DEPENDS ${SHADER}
            COMMENT "Compiling ${FILENAME}")
        message("       >> ${FILENAME}.spv")
        list(APPEND SPV_SHADERS ${LV_SHADER_DIR}/${FILENAME}.spv)
    endForeach()

    add_custom_target(${PROJECT_NAME} ALL DEPENDS ${SPV_SHADERS})

    message(STATUS "===== DONE COMPILING SHADERS =====")

else()
    message(STATUS "===== SKIPPING COMPILING SHADERS =====")
    message(STATUS "        If you want to compile shaders, use the -s option on the build script")
    message(STATUS "        or alternatively pass the argument -DCOMPILE_SHADERS=1 when invoking CMake")
endif()
