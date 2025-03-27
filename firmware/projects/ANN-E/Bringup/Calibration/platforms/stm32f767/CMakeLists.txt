target_sources(main PRIVATE bindings.cc)
target_link_libraries(main PRIVATE mcal-stm32f767)
target_link_options(main PRIVATE -u _printf_float)

add_subdirectory(cubemx/cmake/stm32cubemx)
target_link_libraries(main PRIVATE stm32cubemx)
