project (BT_EXPRESSION)

include_directories(
    ${BT_EXPRESSION_SOURCE_DIR}
    ${BT_STATE_SOURCE_DIR}
    ${BT_STATEMACHINE_SOURCE_DIR}
)

add_library (expression SHARED Expression.cpp Operation.cpp util.cpp Term.cpp)

install(TARGETS expression )