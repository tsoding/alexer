#define ALEXER_IMPLEMENTATION
#include "alexer.h"
#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

typedef enum {
    PUNCT_BAR,
    PUNCT_COMMA,
    PUNCT_OPAREN,
    PUNCT_CPAREN,
    PUNCT_SEMICOLON,
} Punct_Index;

static const char *puncts[] = {
    [PUNCT_BAR] = "|",
    [PUNCT_COMMA] = ",",
    [PUNCT_OPAREN] = "(",
    [PUNCT_CPAREN] = ")",
    [PUNCT_SEMICOLON] = ";",
};

typedef enum {
    KEYWORD_IF,
    KEYWORD_ELSE,
} Keyword_Index;

static const char *keywords[] = {
    [KEYWORD_IF] = "if",
    [KEYWORD_ELSE] = "else",
};

int main()
{
    String_Builder sb = {0};
    const char *file_path = "grammar.bnf";
    if (!read_entire_file(file_path, &sb)) return 1;
    Alexer_Token t = {0};
    Alexer l = alexer_create(file_path, sb.items, sb.count);
    l.puncts = puncts;
    l.puncts_count = ARRAY_LEN(puncts);
    l.keywords = keywords;
    l.keywords_count = ARRAY_LEN(keywords);

    alexer_get_token(&l, &t);
    if (!alexer_expect_punct(&l, t, PUNCT_COMMA)) return 1;

    return 0;
}
