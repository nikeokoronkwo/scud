#include <string>

#include "lexer.h"

// Check whether a given character is a whitespace or not
inline bool isWhitespace(char c) { return c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r' || c == '\n';}

// Simple method to convert a `TokenKind` to a representable string, for debugging purposes
std::string Token::stringify_token_kind(TokenKind kind) const {
    switch (kind) {
        case unknown: return "unknown"; break;
        case eof: return "eof"; break;
        case identifier: return "identifier"; break;
        case string: return "string"; break;
        case left_paren: return "left parenthesis"; break;
        case left_square_paren: return "left square parenthesis"; break;
        case right_square_paren: return "right square parenthesis"; break;
        case right_paren: return "right parenthesis"; break;
        case colon: return "colon"; break;
        case equals: return "equal sign"; break;
        case left_brace: return "left brace"; break;
        case right_brace: return "right brace"; break;
        case single_quote: return "single quote (')"; break;
        case double_quote: return "double quote (\")"; break;
        case comma: return "comma"; break;

        default: return "token"; break;
    }
}

// The token as a debug string
std::string Token::to_string() const {
    return lexeme + ": " + stringify_token_kind(kind) + " at line " + std::to_string(line) + " character " + std::to_string(character);
}


// Function to proceed to the next token
const char Lexer::next() {
    return source[++ptr];
}

// Whether the lexer has reached the end of the file
bool Lexer::at_end() const { return ptr == source.size() - 1; }

// Adds a token to the list
void Lexer::add_token(const char* c, Token::TokenKind kind) { tokens.push_back(Token(c, kind, line, ptr + 2)); }
void Lexer::add_token(std::string c, Token::TokenKind kind) { tokens.push_back(Token(c, kind, line, ptr + 2)); }

// Reads a string token from the source
void Lexer::read_string() {
    std::string str = "";
    ++ptr;
    do {
        str += source[ptr];
        ++ptr;
    } while (!at_end() && source[ptr] != '"');
    add_token(str, Token::TokenKind::string);
}

// Function to scan each character from the source one after the other
//
// After each scan the tokens are deduced and added to the list
void Lexer::scan_token() {
    char c = next();
    switch (c) {
        case ')': add_token(")", Token::TokenKind::right_paren); break;
        case '(': add_token("(", Token::TokenKind::left_paren); break;
        case ':': add_token(":", Token::TokenKind::colon); break;
        case ']': add_token("]", Token::TokenKind::right_square_paren); break;
        case '[': add_token("[", Token::TokenKind::left_square_paren); break;
        case '=': add_token("=", Token::TokenKind::equals); break;
        case '{': add_token("{", Token::TokenKind::left_brace); break;
        case '}': add_token("}", Token::TokenKind::right_brace); break;
        case ',': add_token(",", Token::TokenKind::comma); break;
        case '\n': line++; break;
        case '"': read_string(); break;
        case '#': 
            while(next() != '\n' && !at_end()) { /* advance */ }
            break;
        default:
            if (isWhitespace(c)) { return; }
            else if (isalnum(c)) {
                std::string ident = "";
                ident += source[ptr];
                if (!isalnum(source[ptr + 1])) add_token(ident, Token::TokenKind::identifier);
                else {
                    do {
                        ++ptr;
                        ident += source[ptr];
                    } while (!at_end() && isalnum(source[ptr + 1]));
                    add_token(ident, Token::TokenKind::identifier);
                }
            }
    }
}
// Function to convert raw source to a list of tokens via lexing
std::vector<Token> Lexer::scan_tokens() {
    while (!at_end()) {
        // scan one by one and deduce token
        scan_token();
    }
    // add end of file token
    tokens.push_back(Token("", Token::TokenKind::eof, line));
    return tokens;
}

