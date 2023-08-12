function(add_tool tool_name)

    add_executable(${tool_name} ${tool_name}/main.cpp)

    target_link_libraries(${tool_name} PRIVATE graphs)

endfunction()

add_tool(custom)
add_tool(generation)
