#include "myFunction.hpp"
void processComments(std::ifstream &input, std::ofstream &output) {
  char buffer[1000];
  while (input.getline(buffer, 1000)) {
    std::string temp(buffer);
    std::string out;
    if (temp.find("//") != std::string::npos) {
      int index = temp.find("//");
      output << temp.substr(0, index) << std::endl;
    } else if (temp.find("/**") != std::string::npos) {
      int index = temp.find("/**");
      output << temp.substr(0, index) << std::endl;
      while ( temp.find("*/") == std::string::npos) {
        input.getline(buffer, 1000);
        temp = buffer;
      }
      int index2 = temp.find("*/");
      output << temp.substr(index2 + 2);
    } else 
      output << temp << std::endl;
    
    //std::cout << out << std::endl;
    
  }
}