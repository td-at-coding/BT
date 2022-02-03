project (BT_GRAPH)

include_directories(
        ${BT_STATEMACHINE_SOURCE_DIR}
        ${BT_STATE_SOURCE_DIR}
        ${BT_EXPRESSION_SOURCE_DIR}
        ${BT_GRAMMAR_SOURCE_DIR}
)


add_executable(graph main.cpp)

target_link_libraries (graph grammar statemachine expression state )

install (TARGETS graph)