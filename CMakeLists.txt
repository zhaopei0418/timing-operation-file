cmake_minimum_required (VERSION 3.0)

# 添加c11支持
add_compile_options(-std=c11)
# 项目名称
project(tof)
# 查找当关目录下所有源文件
aux_source_directory(. SOURCES)
# 添加tool子目录
add_subdirectory(paropt)
add_subdirectory(log)

# 添加头文件信息目录
include_directories(${PROJECT_SOURCE_DIR}/include
)

# 生成目录
add_executable(${PROJECT_NAME} ${SOURCES})
# 添加链接库
target_link_libraries(${PROJECT_NAME}
  paropt
  log
)
