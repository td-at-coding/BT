project (BT_STATEMACHINE)

include_directories(
    ${BT_STATEMACHINE_SOURCE_DIR}
    ${BT_EXPRESSION_SOURCE_DIR}
)

add_library (statemachine SHARED Node.cpp StateMachine.cpp)

install(TARGETS statemachine )