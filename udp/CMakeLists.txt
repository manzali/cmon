
include_directories(
  ${Boost_INCLUDE_DIRS}
)

add_executable(
  t_udp_client
  t_udp_client.cpp
)

target_link_libraries(
  t_udp_client
  ${Boost_LIBRARIES}
)

add_library(
  udp_server
  udp_server.cpp
  ${Boost_LIBRARIES}
)

add_executable(
  t_udp_server
  t_udp_server.cpp
)

target_link_libraries(
  t_udp_server
  udp_server
  ${Boost_LIBRARIES}
)
