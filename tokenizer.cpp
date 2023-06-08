#include "tokenizer.hpp"

std::string tokenizer::cur() {
  if (tokenType() == SYMBOL) {
    if (curToken[0] == '<') 
      return "&lt;";
    if (curToken[0] == '&')
      return "&amp;";
    if (curToken[0] == '>')
      return "&gt;";
    if (curToken[0] == '\"')
      return "&quot;";
  } else if (tokenType() == STRING_CONST)
    return curToken.substr(1, (int)curToken.size() - 2);
  return curToken;
}

tokenizer::tokenizer(std::string filename) {
  input.open(filename, std::ios::in);
  if (!input.is_open()) {
    std::cout << "Cannot open file " << filename << std::endl; 
    exit(1);
  }
  advance();
}

void tokenizer::setfile(std::string filename) {
  input.open(filename, std::ios::in);
  if (!input.is_open()) {
    std::cout << "Cannot open file " << filename << std::endl; 
    exit(1);
  }
  advance();
}
bool tokenizer::hasMoreTokens() {
  return !input.eof();
}

void tokenizer::advance() {
  if (!hasMoreTokens()) {
    std::cout << "There are no more tokens !" << std::endl;
    return ;
  }
  std::string token;
  char c;
  input.get(c);
  while (hasMoreTokens() && isspace(c)) {
    input.get(c);
  }
  if (!hasMoreTokens()) {
    std::cout << "There are no more tokens !" << std::endl;
    return ;
  }


  // symbol
  char temp[] = {'{', '}', '[', ']', '(', ')', '.', ',', ';', '+', '-', '*', '/', '&', '|', '<', '>', '=', '~'};
  for (int i = 0; i < 19; i ++) {
  if (c == temp[i]){ 
      token.push_back(c);
      curToken = token;
      return;
    }
  }
  
  //integerConstant
  if (isdigit(c)) {
    while (isdigit(c) && hasMoreTokens()) {
      token.push_back(c);
      input >> c;
    }
    if (hasMoreTokens())
      input.seekg(-1, std::ios::cur);
    curToken = token;
    return;
  }

  //StringConstant
  if (c == '\"') {
    input >> c;
    while (c != '\"' && hasMoreTokens()) {
      token.push_back(c);
      input >> c;
    }
    curToken = "\"" + token + "\"";
    return;
  }
  
  // keyword or identifier
  while (hasMoreTokens() &&( isalnum(c) || c == '_')) {
    token.push_back(c);
    input.get(c);
  }
    
  if (hasMoreTokens())
    input.seekg(-1, std::ios::cur);
  curToken = token;
  return ;
}


tokentype tokenizer::tokenType() {
  char ch = curToken[0];
  char temp[] = {'{', '}', '[', ']', '(', ')', '.', ',', ';', '+', '-', '*', '/', '&', '|', '<', '>', '=', '~'};
  for (int i = 0; i < 19; i ++) {
    if (temp[i] == ch) {
      return SYMBOL;
    }
  }
  if (isdigit(ch))
    return INT_CONST;

  if (ch == '\"')
    return STRING_CONST;
  
  std::vector<std::string>  keywords = {"class", "method", "function", "constructor", "int", "boolean", "char", "void", "var", "static", "field", "let", "do", "if", "else", "while", "return", "true", "false", "null", "this"};
  for (int i = 0; i < (int)keywords.size(); i ++) {
    if (curToken == keywords[i])
      return KEYWORD;
  } 

  return IDENTIFIER;
}

std::string up(std::string str) {
  for (int i = 0; i < (int)str.size(); i ++) {
    str[i] = toupper(str[i]);
  }
  return str;
}
keyWordType tokenizer::keyword() {
  std::vector<std::string>  keywords = {"class", "method", "function", "constructor", "int", "boolean", "char", "void", "var", "static", "field", "let", "do", "if", "else", "while", "return", "true", "false", "null", "this"};
  return CLASS;
}
std::string tokenizer::symbol() {
  // std::cout << "temp: " << curToken << " " << curToken.size() << std::endl;
  if (curToken[0] == '<') 
    return "&lt;";
  if (curToken[0] == '&')
    return "&amp;";
  if (curToken[0] == '>')
    return "&gt;";
  if (curToken[0] == '\"')
    return "&quot;";
  return curToken;
}
std::string tokenizer::identifier() {
  return curToken;
}
int tokenizer::intVal() {
  return std::stol(curToken);
}
std::string tokenizer::stringVal() {
  //std::cout << curToken << std::endl;
  int n = curToken.size();
  return curToken.substr(1, n-1);
}


tokenizer::~tokenizer() {
  input.close();
}