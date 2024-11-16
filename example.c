#define ALEXER_IMPLEMENTATION
#include "alexer.h"

typedef enum {
    PUNCT_PLUS,
    PUNCT_MULT,
    PUNCT_OPAREN,
    PUNCT_CPAREN,
} Punct_Index;

const char *puncts[] = {
    [PUNCT_PLUS] = "+",
    [PUNCT_MULT] = "*",
    [PUNCT_OPAREN] = "(",
    [PUNCT_CPAREN] = ")",
};

int main()
{
    const char *file_path = "example/path"; // The file path is only needed for diagnostic message
    const char *content = "a + (35*45)";
    Alexer l = alexer_create(file_path, content, strlen(content));
    l.puncts = puncts;
    l.puncts_count = ALEXER_ARRAY_LEN(puncts);
    Alexer_Token t = {0};
    while (alexer_get_token(&l, &t)) {
        l.diagf(t.loc, "INFO", "%s: %.*s", alexer_kind_name(t.kind), t.end - t.begin, t.begin);
    }
    if (!alexer_expect_kind(&l, t, ALEXER_END)) return 1;
    return 0;
}
