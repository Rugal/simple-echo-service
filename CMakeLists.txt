#C
cmake_minimum_required(VERSION 3.10.0)
PROJECT(communication C)
SET(CMAKE_C_FLAGS "-O0 -ggdb -w -std=c11")
SET(CMAKE_C_COMPILER gcc)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

SET(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/implement)

SET(SOURCE
    ${SOURCE_DIR}/socket.c
    ${SOURCE_DIR}/StringUtility.c
    ${SOURCE_DIR}/Configuration.c
    ${SOURCE_DIR}/System.c
    ${SOURCE_DIR}/ArrayList.c
    ${SOURCE_DIR}/Asynchronization.c
)

SET(SERVER
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.c
    ${SOURCE}
)

SET(ASYNC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/async.c
    ${SOURCE}
)

SET(CLIENT
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client.c
    ${SOURCE}
)

ADD_EXECUTABLE("server" ${SERVER})
ADD_EXECUTABLE("client" ${CLIENT})
ADD_EXECUTABLE("async" ${ASYNC})
#TARGET_LINK_LIBRARIES(${BIN})
