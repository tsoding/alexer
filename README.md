# Alexer

Very basic lexer for very basic cases .

## Quick Start

```c
#define ALEXER_IMPLEMENTATION
#include "alexer.h"

typedef enum {
    PUNCT_PLUS,
    PUNCT_MULT,
    PUNCT_EQUALS,
    PUNCT_OPAREN,
    PUNCT_CPAREN,
    PUNCT_SEMICOLON,
} Punct_Index;

const char *puncts[] = {
    [PUNCT_PLUS] = "+",
    [PUNCT_MULT] = "*",
    [PUNCT_OPAREN] = "(",
    [PUNCT_CPAREN] = ")",
    [PUNCT_EQUALS] = "==",
    [PUNCT_SEMICOLON] = ";",
};

typedef enum {
    KEYWORD_IF,
    KEYWORD_RETURN,
} Keyword_Index;

const char *keywords[] = {
    [KEYWORD_IF] = "if",
    [KEYWORD_RETURN] = "return",
};

int main()
{
    const char *file_path = "example/path"; // The file path is only needed for diagnostic message
    const char *content = "if (a == 17*2 + 35) return b;";
    Alexer l = alexer_create(file_path, content, strlen(content));
    l.puncts = puncts;
    l.puncts_count = ALEXER_ARRAY_LEN(puncts);
    l.keywords = keywords;
    l.keywords_count = ALEXER_ARRAY_LEN(keywords);
    Alexer_Token t = {0};
    while (alexer_get_token(&l, &t)) {
        l.diagf(t.loc, "INFO", "%s: %.*s", alexer_kind_name(t.kind), t.end - t.begin, t.begin);
    }
    if (!alexer_expect_kind(&l, t, ALEXER_END)) return 1;
    return 0;
}
```

```console
$ cc -Wall -Wextra -Wswitch-enum -ggdb -o example example.c
$ ./example
example/path:1:1: INFO: KEYWORD: if
example/path:1:4: INFO: PUNCT: (
example/path:1:5: INFO: SYMBOL: a
example/path:1:7: INFO: PUNCT: ==
example/path:1:10: INFO: INT: 17
example/path:1:12: INFO: PUNCT: *
example/path:1:13: INFO: INT: 2
example/path:1:15: INFO: PUNCT: +
example/path:1:17: INFO: INT: 35
example/path:1:19: INFO: PUNCT: )
example/path:1:21: INFO: KEYWORD: return
example/path:1:28: INFO: SYMBOL: b
example/path:1:29: INFO: PUNCT: ;
```
