cmake_minimum_required (VERSION 3.0)

if (WIN32)
    message(STATUS "Now is windows.")
elseif (APPLE)
    message(STATUS "Now is Apple system.")
elseif (UNIX)
    message(STATUS "now is UNIX-like OS's.")
endif()
# 添加c11支持
#add_compile_options(-std=c11)
# 项目名称
project(tof)
# 查找当关目录下所有源文件
aux_source_directory(. SOURCES)
# 添加tool子目录
add_subdirectory(paropt)
add_subdirectory(log)
add_subdirectory(tool)
add_subdirectory(regex)

# 添加头文件信息目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 生成目录
add_executable(${PROJECT_NAME} ${SOURCES})
# 添加链接库
target_link_libraries(${PROJECT_NAME}
  paropt
  log
  tool
  regex
)
