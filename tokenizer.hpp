#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <vector>
enum tokentype {
  KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST
};

enum keyWordType {
  CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT, BOOLEAN, CHAR, VOID, 
  VAR, STATIC, FIELD, LET, DO, IF, ELSE, WHILE, RETURN, TRUE, FALSE, 
  NULLL, THIS
};

class tokenizer {
  private:
    std::ifstream input;
    std::string curToken;
  public:  
    tokenizer(std::string filename);
    ~tokenizer();
    void setfile(std::string filename);
    bool hasMoreTokens();
    void advance();
    tokentype tokenType();
    keyWordType keyword();
    std::string symbol();
    std::string identifier();
    int intVal();
    std::string stringVal();
    std::string cur();
};

#endif