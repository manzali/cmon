
include_directories(
  ${Boost_INCLUDE_DIRS}
)

add_executable(
  t_shared_queue
  t_shared_queue.cpp
)

target_link_libraries(
  t_shared_queue
  ${Boost_LIBRARIES}
)
