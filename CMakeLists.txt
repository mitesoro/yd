#指定要求的 CMake 最低版本。
cmake_minimum_required(VERSION 3.8)

#设置项目名称为 "HelloWorld"，并指定 C 和 C++ 语言。
project(HelloWorld C CXX)

#包含一个名为 "common.cmake" 的 CMake 文件，该文件可能包含一些常用的配置和设置。
include(./common/cmake/common.cmake)

# Proto file
#获取 helloworld.proto 文件的绝对路径，并将其所在的目录存储在变量 hw_proto_path 中。
get_filename_component(hw_proto "./protos/helloworld.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
#设置生成的源文件的路径和名称。
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.h")


#添加自定义命令来生成源文件。该命令使用 Protocol Buffers 编译器（${_PROTOBUF_PROTOC}）和 gRPC 插件（${_GRPC_CPP_PLUGIN_EXECUTABLE}）来生成 C++ 源文件和头文件。
add_custom_command(
        OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
        DEPENDS "${hw_proto}")

# 头文件目录
include_directories(include)
# 库文件目录
link_directories(linux64)



# Include generated *.pb.h files
#将生成的 .pb.h 文件所在的目录添加到包含目录中，以便在构建过程中能够找到这些文件。
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# hw_grpc_proto
#创建一个名为 hw_grpc_proto 的库，并将生成的源文件添加到该库中。然后，将 gRPC 和 Protocol Buffers 相关的库链接到该库中。
add_library(hw_grpc_proto
        ${hw_grpc_srcs}
        ${hw_grpc_hdrs}
        ${hw_proto_srcs}
        ${hw_proto_hdrs})
target_link_libraries(hw_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})



# Targets greeter_[async_](client|server)
#创建多个可执行文件，每个文件对应一个示例的客户端或服务器。将生成的源文件和所需的库链接到每个可执行文件中。
#foreach(_target
#         greeter_server)
#    add_executable(${_target} "${_target}.cc")
#    target_link_libraries(${_target}
#            hw_grpc_proto
#            absl::flags
#            absl::flags_parse
#            ${_REFLECTION}
#            ${_GRPC_GRPCPP}
#            ${_PROTOBUF_LIBPROTOBUF})
#endforeach()

#add_executable(greeter_server "src/greeter_server.cc" "src/yd.cpp")
add_executable(greeter_server "src/main.cpp" "src/yd_info.cpp")
target_link_libraries(greeter_server
        hw_grpc_proto
        absl::flags
        absl::flags_parse
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})
# 加载libyd.so
target_link_libraries(greeter_server yd)