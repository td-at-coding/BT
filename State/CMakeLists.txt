project (BT_STATE)

include_directories(
    ${BT_STATE_SOURCE_DIR}
    ${BT_EXPRESSION_SOURCE_DIR}
)

add_library (state SHARED Data.cpp State.cpp Function.cpp)

install(TARGETS state )