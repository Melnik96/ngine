install(DIRECTORY ./ DESTINATION include/ngine
        FILES_MATCHING PATTERN "*.h")


add_subdirectory(render)
add_subdirectory(scenegraph)
add_subdirectory(iohand)
add_subdirectory(math)
add_subdirectory(physics)
add_subdirectory(sound)
add_subdirectory(core)
add_subdirectory(import)
add_subdirectory(network)
add_subdirectory(gui)
add_subdirectory(mesh)