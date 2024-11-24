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
    [PUNCT_PLUS]      = "+",
    [PUNCT_MULT]      = "*",
    [PUNCT_OPAREN]    = "(",
    [PUNCT_CPAREN]    = ")",
    [PUNCT_OCURLY]    = "{",
    [PUNCT_CCURLY]    = "}",
    [PUNCT_EQUALS]    = "==",
    [PUNCT_SEMICOLON] = ";",
};

typedef enum {
    KEYWORD_IF,
    KEYWORD_RETURN,
    COUNT_KEYWORDS,
} Keyword_Index;

static_assert(COUNT_KEYWORDS == 2, "Amount of keywords have changed");
const char *keywords[COUNT_KEYWORDS] = {
    [KEYWORD_IF]     = "if",
    [KEYWORD_RETURN] = "return",
};

const char *sl_comments[] = {
    "//",
    "#",
};

Alexer_ML_Comments ml_comments[] = {
    {"/*", "*/"},
};

int main()
{
    const char *file_path = "example/path"; // The file path is only needed for diagnostic message
    const char *content =
        "#include <stdio.h>\n"
        "if (a == 17*2 + 35) { // single line comment\n"
        "if (x == 0xff) {      // testing hex support\n"
        "    /* multi\n"
        "     * line\n"
        "     * comment\n"
        "     */\n"
        "    return b;\n"
        "}\n";
    Alexer l = alexer_create(file_path, content, strlen(content));
    l.puncts = puncts;
    l.puncts_count = ALEXER_ARRAY_LEN(puncts);
    l.keywords = keywords;
    l.keywords_count = ALEXER_ARRAY_LEN(keywords);
    l.sl_comments = sl_comments;
    l.sl_comments_count = ALEXER_ARRAY_LEN(sl_comments);
    l.ml_comments = ml_comments;
    l.ml_comments_count = ALEXER_ARRAY_LEN(ml_comments);
    Alexer_Token t = {0};
    while (alexer_get_token(&l, &t)) {
        l.diagf(t.loc, "INFO", "%s: %.*s", alexer_kind_name(ALEXER_KIND(t.id)), t.end - t.begin, t.begin);
    }
    if (!alexer_expect_id(&l, t, ALEXER_END)) return 1;
    return 0;
}
