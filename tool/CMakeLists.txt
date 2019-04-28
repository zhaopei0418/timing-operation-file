aux_source_directory(. TOOL_SOURCES)

# 生成静态库
add_library(tool ${TOOL_SOURCES})
