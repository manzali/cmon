
include_directories(
  ${Boost_INCLUDE_DIRS}
)

add_executable(
  daytime_async_server
  daytime_async_server.cpp
)

target_link_libraries(
  daytime_async_server
  ${Boost_LIBRARIES}
)

add_executable(
  daytime_sync_client
  daytime_sync_client.cpp
)

target_link_libraries(
  daytime_sync_client
  ${Boost_LIBRARIES}
)

add_executable(
  async_server
  async_server.cpp
)

target_link_libraries(
  async_server
  ${Boost_LIBRARIES}
)

add_executable(
  sync_client
  sync_client.cpp
)

target_link_libraries(
  sync_client
  ${Boost_LIBRARIES}
)
