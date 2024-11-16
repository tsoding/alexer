#define ALEXER_IMPLEMENTATION
#include "alexer.h"

typedef enum {
    PUNCT_PLUS,
    PUNCT_MULT,
    PUNCT_EQUALS,
    PUNCT_OPAREN,
    PUNCT_CPAREN,
    PUNCT_OCURLY,
    PUNCT_CCURLY,
    PUNCT_SEMICOLON,
    COUNT_PUNCTS,
} Punct_Index;

static_assert(COUNT_PUNCTS == 8, "Amount of puncts have changed");
const char *puncts[COUNT_PUNCTS] = {
    [PUNCT_PLUS] = "+",
    [PUNCT_MULT] = "*",
    [PUNCT_OPAREN] = "(",
    [PUNCT_CPAREN] = ")",
    [PUNCT_OCURLY] = "{",
    [PUNCT_CCURLY] = "}",
    [PUNCT_EQUALS] = "==",
    [PUNCT_SEMICOLON] = ";",
};

typedef enum {
    KEYWORD_IF,
    KEYWORD_RETURN,
    COUNT_KEYWORDS,
} Keyword_Index;

static_assert(COUNT_KEYWORDS == 2, "Amount of keywords have changed");
const char *keywords[COUNT_KEYWORDS] = {
    [KEYWORD_IF] = "if",
    [KEYWORD_RETURN] = "return",
};

const char *single_line_comments[] = {
    "//",
    "#",
};

int main()
{
    const char *file_path = "example/path"; // The file path is only needed for diagnostic message
    const char *content =
        "#include <stdio.h>\n"
        "if (a == 17*2 + 35) { // single line comment\n"
        "    return b;\n"
        "}\n";
    Alexer l = alexer_create(file_path, content, strlen(content));
    l.puncts = puncts;
    l.puncts_count = ALEXER_ARRAY_LEN(puncts);
    l.keywords = keywords;
    l.keywords_count = ALEXER_ARRAY_LEN(keywords);
    l.single_line_comments = single_line_comments;
    l.single_line_comments_count = ALEXER_ARRAY_LEN(single_line_comments);
    Alexer_Token t = {0};
    while (alexer_get_token(&l, &t)) {
        l.diagf(t.loc, "INFO", "%s: %.*s", alexer_kind_name(t.kind), t.end - t.begin, t.begin);
    }
    if (!alexer_expect_kind(&l, t, ALEXER_END)) return 1;
    return 0;
}
