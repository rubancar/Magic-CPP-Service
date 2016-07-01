cmake_minimum_required(VERSION 3.2.2)
#project(Servicio_C++)
#include(socket.io-client-cpp/CMakeLists.txt)

set(CMAKE_BUILD_TYPE Debug)
#set(LIB "/usr/lib" CACHE PATH "Ruta a librerias compiladas de mysql")
#set(CMAKE_BUILD_TYPE Release)

set(source_files
	sample_main.cpp
	SerialPort.cpp
	BaseDeDatos.cpp
  #TestEndpointTarget.cpp
	TestTarget.cpp
)

include_directories(/usr/include/mysql++)
include_directories(/usr/include/mysql)
include_directories(socket.io-poco/include)
include_directories(/usr/local/include)
include_directories(socket.io-poco/third_party/local/include)
include_directories(socket.io-poco/include)
include_directories(/boost/boost_1_61_0)
link_directories(/boost/boost_1_61_0/boost)
#link_directories(/boost/boost_1_61_0/stage/lib)
link_directories(.)
link_directories(/usr/local/lib)
link_directories(socket.io-poco/third_party/local/lib)
link_directories(socket.io-poco/lib)

add_executable(servicio_c++ ${source_files})
#add_executable(servicio_c++ sample_main.cpp)
set_property(TARGET servicio_c++ PROPERTY CXX_STANDARD 11)
set_property(TARGET servicio_c++ PROPERTY CXX_STANDARD_REQUIRED ON)
#target_link_libraries(servicio_c++ mysqlpp boost_system boost_thread)
target_link_libraries(servicio_c++ pthread )
target_link_libraries(servicio_c++ mysqlpp)
target_link_libraries(servicio_c++ boost_system)
target_link_libraries(servicio_c++ boost_thread)
#target_link_libraries(servicio_c++ sioclient)
target_link_libraries(servicio_c++ socketiopoco_shared)


#message(STATUS ${Boost_INCLUDE_DIRS} )
