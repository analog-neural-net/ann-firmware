target_sources(bindings PRIVATE bindings.cc)
target_include_directories(bindings PRIVATE ${DIR_PROJECT})

target_link_libraries(bindings PUBLIC mcal-cli)