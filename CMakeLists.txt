cmake_minimum_required(VERSION 3.22.1)
 
project(MyProject)
   
include_directories(include)
   
add_subdirectory(src)
   
set(CMAKE_INSTALL_BINDIR "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_INSTALL_LIBDIR "${CMAKE_SOURCE_DIR}/lib")
  
install(TARGETS MyExecutable MyLibrary
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}) 
set(CMAKE_BUILD_TYPE"Debug")