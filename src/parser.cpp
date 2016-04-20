#include "parser.h"
#include "exception.h"

#include <fstream>
#include <memory>
#include <cctype>
#include <cassert>

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

bool GetQualifier(const char*& curr_char, std::string& qualifier)
{
   if ('\0' == *curr_char)
   {
      return false;
   }

   const char* start = curr_char;

   // First symbol must be either undersore or alphabetic one.
   if (!std::isalpha(*curr_char) && *curr_char != '_')
   {
      return false;
   }

   ++curr_char;

   while (*curr_char != '\0' && !std::isspace(*curr_char))
   {
      if (!std::isalnum(*curr_char))
      {
         return false;
      }
      ++curr_char;
   }

   qualifier.assign(start, curr_char);

   return true;
}

bool GetQuotedString(const char*& curr_char, std::string& value)
{
   assert('"' == *curr_char);
   ++curr_char;

   const char* start = curr_char;

   while (*curr_char != '\0' && *curr_char != '"')
   {
      ++curr_char;
   }

   if (*curr_char != '"')
   {
      return false;
   }

   value.assign(start, ++curr_char);

   return true;
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
   
   auto file_content = std::make_unique<char[]>(file_size + 1);
   file.read(file_content.get(), file_size);
   file_content[file_size] = '\0';
   
   file.close();
   
   long line_number = 1;
   long nesting_level = 0;
   const char* token_start = nullptr;
   const char* curr_char = file_content.get();

   std::vector<ParsedNode*> nodes_stack;

   ParsedNode* curr_parent = &m_root;
   ParsedNode* curr_node = nullptr;
   
   do
   {
      curr_parent->m_children.emplace_back();
      curr_node = &curr_parent->m_children.back();

      SkipSpaces(curr_char, line_number);
      if ('\0' == *curr_char)
      {
         SyntaxError(line_number, "Node name is expected.");
      }
      
      if (!GetQualifier(curr_char, curr_node->m_name))
      {
         SyntaxError(line_number, "Node name must be a qualifier.");
      }

      SkipSpaces(curr_char, line_number);
      if (*curr_char != '=')
      {
         SyntaxError(line_number, "An assignment is expected.");
      }

      SkipSpaces(++curr_char, line_number);
      if ('{' == *curr_char)
      {
         ++curr_char;
         nodes_stack.push_back(curr_parent);
         curr_parent = curr_node;
         continue;
      }
      else if ('"' == *curr_char)
      {
         if (!GetQuotedString(curr_char, curr_node->m_value))
         {
            SyntaxError(line_number, "No closing quote at the line.");
         }
      }
      else
      {
         SyntaxError(line_number, "Either an opening brace or a quote is expected.");
      }

      SkipSpaces(curr_char, line_number);
      while ('}' == *curr_char)
      {
         if (nodes_stack.empty())
         {
            SyntaxError(line_number, "Closing brace is detected before an opening one.");
         }
         curr_parent = nodes_stack.back();
         nodes_stack.pop_back();
         SkipSpaces(++curr_char, line_number);
      }
   }
   while (*curr_char != '\0');
}

void Parser::SaveTo(const char file_name[])
{
}
   
} // namespace SoftLab
