aux_source_directory(. LOG_SOURCES)
# add_compile_options(-DLOG_USE_COLOR)

add_library(log ${LOG_SOURCES})
