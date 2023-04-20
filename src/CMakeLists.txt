aux_source_directory(./server/ SERVER_SRC_LIST)
aux_source_directory(./server/db/ DB_SRC_LIST)
aux_source_directory(./server/model/ MODEL_SRC_LIST)
aux_source_directory(./server/redis/ REDIS_SRC_LIST)


add_executable(server ${SERVER_SRC_LIST} ${DB_SRC_LIST} ${MODEL_SRC_LIST} ${REDIS_SRC_LIST})
target_link_libraries(server muduo_net muduo_base mysqlclient hiredis pthread)


aux_source_directory(./client/ CLIENT_SRC_LIST)
add_executable(client ${CLIENT_SRC_LIST})
target_link_libraries(client pthread)