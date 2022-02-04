project (BT_GRAMMAR)

include_directories(
    ${BT_GRAMMAR_SOURCE_DIR}
    ${BT_EXPRESSION_SOURCE_DIR}
    ${BT_STATEMACHINE_SOURCE_DIR}
    ${BT_STATE_SOURCE_DIR}
)

add_library (grammar SHARED Parser.cpp Linter.cpp Grammar.cpp Reader.cpp pattern.cpp mstate.cpp cstate.cpp)

install(TARGETS grammar )