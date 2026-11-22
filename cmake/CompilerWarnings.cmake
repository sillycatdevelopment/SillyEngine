# SillyEngine
# Build setup created by Claude (Anthropic AI) for SillyCatDevelopment.

# sillyengine_set_warnings(<target>)
# The same strict warnings as Aerith Chess, for your own code.
function(sillyengine_set_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic
            -Wshadow -Wconversion -Wsign-conversion
            -Wnon-virtual-dtor -Wold-style-cast
            -Woverloaded-virtual -Wnull-dereference)
    endif()
endfunction()
