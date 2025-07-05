add_library(MyLibrary head.cpp user.cpp task.cpp My_time.cpp)

add_executable(MyExecutable main.cpp)

target_link_libraries(MyExecutable MyLibrary)

find_package(OpenSSL REQUIRED)
target_include_directories(MyLibrary PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(MyLibrary PRIVATE ${OPENSSL_LIBRARIES})

set(CMAKE_BUILD_TYPE"Debug")
