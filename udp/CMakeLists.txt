
include_directories(
  ${Boost_INCLUDE_DIRS}
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

add_executable(
  sync_server
  sync_server.cpp
)

target_link_libraries(
  sync_server
  ${Boost_LIBRARIES}
)
