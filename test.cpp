#include <iostream>
#include <fstream>
#include "tokenizer.hpp"
#include "myFunction.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Please enter the file you want to compile !" << std::endl;
    exit(0);
  }
  std::string file(argv[1]);
  int index = file.find(".jack");
  std::string tmpfile(file.substr(0, index) + "Tyb.temp");
  std::string oputfile(file.substr(0, index) + "Tyb.xml");
  std::ifstream input(file);
  std::ofstream output(tmpfile);
  std::ofstream outfile(oputfile);
  processComments(input, output);
  tokenizer t(tmpfile);
  outfile << "<tokens>" << std::endl;

  while (t.hasMoreTokens()) {
    switch(t.tokenType())
    //output << "<" << t.tokenType() << ">"  << t.cur() << "<" << t.tokenType() << ">" << std::endl;
    {
      case KEYWORD:
        outfile << "<" << "keyword" << "> "  << t.cur() << " <" << "/keyword" << ">" << std::endl;
        break;
      case SYMBOL:
        outfile << "<" << "symbol" << "> "  << t.cur() << " <" << "/symbol" << ">" << std::endl;
        break;
      case IDENTIFIER:
        outfile << "<" << "identifier" << "> "  << t.cur() << " <" << "/identifier" << ">" << std::endl;
        break;
      case INT_CONST:
        outfile << "<" << "integerConstant" << "> "  << t.cur() << " </" << "integerConstant" << ">" << std::endl;
        break;
      case STRING_CONST:
        outfile << "<" << "stringConstant" << "> "  << t.cur() << " </" << "stringConstant" << ">" << std::endl;
        break;

    }
    t.advance();
  }
  outfile << "</tokens>" << std::endl;
  output.close();
  outfile.close();
}