project (BT_PARSER)

include_directories(
    ${BT_PARSER_SOURCE_DIR}
    ${BT_STATE_SOURCE_DIR}
)

add_library (parser SHARED Parser.cpp)

install(TARGETS parser )