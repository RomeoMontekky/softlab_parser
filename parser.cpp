#include "parser.h"
#include "exception.h"

#include <fstream>
#include <memory>
#include <cctype>

namespace SoftLab
{
   
namespace
{
   
void SkipSpaces(const char*& curr_char, long& line_number)
{
   while (*curr_char != '\0' && std::isspace(*curr_char))
   {
      if ('\n' == *curr_char)
      {
         ++line_number;
      }
      ++curr_char;
   }
}

} // namespace
   
Parser::Parser()
{
}

void Parser::Parse(const char file_name[])
{
   std::ifstream file(file_name, std::ios::binary);
   if (!file.is_open())
   {
      Error("Can't open file '", file_name, "' for reading.");
   }
   
   file.seekg(0, std::ios::end);
   const long file_size = file.tellg();
   file.seekg(0, std::ios::beg);
   
   auto parse_content = std::make_unique<char[]>(file_size + 1);
   file.read(parse_content.get(), file_size);
   parse_content[file_size] = '\0';
   
   file.close();
   
   long line_number = 0;
   const char* token_start = nullptr;
   const char* curr_char = parse_content.get();
   ParsedNode* curr_node = &m_root;
   
   while (true)
   {
      SkipSpaces(curr_char, line_number);
      if ('\0' == *curr_char)
      {
         SyntaxError(line_number, "Expected node name");
      }
      
      
   }
}

void Parser::SaveTo(const char file_name[])
{
}
   
} // namespace SoftLab
