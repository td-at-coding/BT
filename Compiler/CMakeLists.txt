project (BT_COMPILER)

include_directories(
        ${BT_PARSER_SOURCE_DIR}
        # ${BT_COMPILER_SOURCE_DIR}
        ${BT_STATE_SOURCE_DIR}
)


add_executable(compiler main.cpp)

target_link_libraries (compiler parser state expression)

install (TARGETS compiler)