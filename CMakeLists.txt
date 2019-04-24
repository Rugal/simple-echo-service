#C
cmake_minimum_required(VERSION 3.10.0)
PROJECT(communication C)
SET(CMAKE_C_FLAGS "-O0 -ggdb -w -std=c11")
SET(CMAKE_C_COMPILER gcc)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

SET(SERVER
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/implement/socket.c
)

SET(CLIENT
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/implement/socket.c
)

ADD_EXECUTABLE("server" ${SERVER})
ADD_EXECUTABLE("client" ${CLIENT})
#TARGET_LINK_LIBRARIES(${BIN})

