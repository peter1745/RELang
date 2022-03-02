#include "scanner.h"

#include <string.h>

struct RE_Scanner {
    const char* start;
    const char* current;
    u16 line;
} scanner;

void RE_InitScanner(const char* source)
{
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

static bool RE_ScannerIsAtEnd() { return *scanner.current == '\0'; }

static RE_Token RE_MakeToken(RE_TokenType type)
{
    RE_Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (u16)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static RE_Token RE_ErrorToken(const char* message)
{
    RE_Token token;
    token.type = RE_TOKEN_ERROR;
    token.start = message;
    token.length = (u16)strlen(message);
    token.line = scanner.line;
    return token;
}

static char RE_Advance()
{
    scanner.current++;
    return scanner.current[-1];
}

static bool RE_Match(char expected)
{
    if (RE_ScannerIsAtEnd())
        return false;

    if (*scanner.current != expected)
        return false;
    
    scanner.current++;
    return true;
}

static char RE_PeekNext()
{
    if (RE_ScannerIsAtEnd())
        return '\0';
    
    return scanner.current[1];
}

static void RE_SkipWhitespace()
{
    while (true)
    {
        char c = *scanner.current;
        switch (c)
        {
        case ' ':
        case '\r':
        case '\t':
            RE_Advance();
            break;
        case '\n':
            scanner.line++;
            RE_Advance();
            break;
        case '/':
        {
            if (RE_PeekNext() == '/')
            {
                while ((*scanner.current) != '\n' && !RE_ScannerIsAtEnd())
                    RE_Advance();
            }
            else
            {
                return;
            }

            break;
        }
        default:
            return;
        }
    }
}

static RE_Token RE_StringToken()
{
    while ((*scanner.current) != '"' && !RE_ScannerIsAtEnd())
    {
        if ((*scanner.current) == '\n')
            scanner.line++;
        
        RE_Advance();
    }

    if (RE_ScannerIsAtEnd())
        return RE_ErrorToken("Unterminated string literal.");

    RE_Advance(); // Closing quote
    return RE_MakeToken(RE_TOKEN_STRING);
}

static bool RE_IsDigit(char c) { return c >= '0' && c <= '9'; }

static RE_Token RE_NumberToken()
{
    while (RE_IsDigit(*scanner.current))
        RE_Advance();

    if ((*scanner.current) == '.' && RE_IsDigit(RE_PeekNext()))
    {
        RE_Advance(); // Consume the .
        while (RE_IsDigit(*scanner.current))
            RE_Advance();
    }

    return RE_MakeToken(RE_TOKEN_NUMBER);
}

static bool RE_IsAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static RE_TokenType RE_CheckKeyword(u16 start, u16 length, const char* rest, RE_TokenType type)
{
    if (scanner.current - scanner.start == start + length && memcmp(scanner.start + start, rest, length) == 0)
        return type;

    return RE_TOKEN_IDENTIFIER;
}

static RE_TokenType RE_IdentifierType()
{
    switch (scanner.start[0])
    {
    case 'd': return RE_CheckKeyword(1, 2, "ef", RE_TOKEN_DEF);
    case 'e': return RE_CheckKeyword(1, 3, "lse", RE_TOKEN_ELSE);
    case 'f':
    {
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'a': return RE_CheckKeyword(2, 3, "lse", RE_TOKEN_FALSE);
            case 'o': return RE_CheckKeyword(2, 1, "r", RE_TOKEN_FOR);
            }
        }
        break;
    }
    case 'g': return RE_CheckKeyword(1, 2, "et", RE_TOKEN_PROPERTY_GET);
    case 'i': return RE_CheckKeyword(1, 1, "f", RE_TOKEN_IF);
    case 'n': return RE_CheckKeyword(1, 3, "ull", RE_TOKEN_NULL);
    case 'r': return RE_CheckKeyword(1, 5, "eturn", RE_TOKEN_RETURN);
    case 's':
    {
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 't': return RE_CheckKeyword(2, 5, "orage", RE_TOKEN_STORAGE);
            case 'e': return RE_CheckKeyword(2, 1, "t", RE_TOKEN_PROPERTY_SET);
            }
        }
        break;
    }
    case 't': return RE_CheckKeyword(1, 3, "rue", RE_TOKEN_TRUE);
    case 'w': return RE_CheckKeyword(1, 4, "hile", RE_TOKEN_WHILE);
    }

    return RE_TOKEN_IDENTIFIER;
}

static RE_Token RE_IdentifierToken()
{
    while (RE_IsAlpha(*scanner.current) || RE_IsDigit(*scanner.current))
    {
        RE_Advance();
    }

    return RE_MakeToken(RE_IdentifierType());
}

RE_Token RE_ScannerScanToken()
{
    RE_SkipWhitespace();
    scanner.start = scanner.current;

    if (RE_ScannerIsAtEnd())
        return RE_MakeToken(RE_TOKEN_EOF);

    char c = RE_Advance();

    if (RE_IsAlpha(c))
        return RE_IdentifierToken();

    if (RE_IsDigit(c))
        return RE_NumberToken();

    switch (c)
    {
    case '(': return RE_MakeToken(RE_TOKEN_LEFT_PAREN);
    case ')': return RE_MakeToken(RE_TOKEN_RIGHT_PAREN);
    case '{': return RE_MakeToken(RE_TOKEN_LEFT_BRACE);
    case '}': return RE_MakeToken(RE_TOKEN_RIGHT_BRACE);
    case ':': return RE_MakeToken(RE_TOKEN_COLON);
    case ';': return RE_MakeToken(RE_TOKEN_SEMICOLON);
    case ',': return RE_MakeToken(RE_TOKEN_COMMA);
    case '.': return RE_MakeToken(RE_TOKEN_DOT);
    case '+': return RE_MakeToken(RE_TOKEN_PLUS);
    case '-': return RE_MakeToken(RE_TOKEN_MINUS);
    case '*': return RE_MakeToken(RE_TOKEN_STAR);
    case '/': return RE_MakeToken(RE_TOKEN_SLASH);
    case '@': return RE_MakeToken(RE_TOKEN_AT);
    case '!': return RE_MakeToken(RE_Match('=') ? RE_TOKEN_BANG_EQUAL : RE_TOKEN_BANG);
    case '=': return RE_MakeToken(RE_Match('=') ? RE_TOKEN_EQUAL_EQUAL : RE_TOKEN_EQUAL);
    case '<': return RE_MakeToken(RE_Match('=') ? RE_TOKEN_LESS_EQUAL : RE_TOKEN_LESS);
    case '>': return RE_MakeToken(RE_Match('=') ? RE_TOKEN_GREATER_EQUAL : RE_TOKEN_GREATER);
    case '"': return RE_StringToken();
    }

    return RE_ErrorToken("Unexpected character.");
}
