#ifndef _PARSER_H_
#define _PARSER_H_

class Parser {
public:
    Parser(Lexer& lexer, std::ostream& out): lexer(lexer), out(out) {}
    int parse();

private:
    Lexer& lexer;
    std::ostream& out;
};

#endif
