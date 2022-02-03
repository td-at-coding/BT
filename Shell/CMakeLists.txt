project (BT_SHELL)

include_directories(
        ${BT_PARSER_SOURCE_DIR}
        ${BT_GRAMMAR_SOURCE_DIR}
        ${BT_STATE_SOURCE_DIR}
        ${BT_STATEMACHINE_SOURCE_DIR}
        ${BT_EXPRESSION_SOURCE_DIR}
)


add_executable(shell main.cpp)

target_link_libraries (shell state grammar statemachine expression )

install (TARGETS shell)