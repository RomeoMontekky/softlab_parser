#include "parser.h"
#include "exceptions.h"
#include "utils.h"

#include <fstream>
#include <memory>

namespace SoftLab
{
   
struct Parser::ParsedNode
{
   ParsedNode(long input_id);

   long id;
   std::unique_ptr<char[]> name;
   std::unique_ptr<char[]> value;
   std::unique_ptr<std::vector<ParsedNode>> children;
};

Parser::ParsedNode::ParsedNode(long input_id) :
   id(input_id), name(), value(), children()
{
}
   
Parser::Parser() : m_root()
{
}

Parser::~Parser()
{
}

void Parser::Parse(const char file_name[])
{
   std::unique_ptr<char[]> file_content;

   {
      std::ifstream file(file_name, std::ios::binary);
      if (!file.is_open())
      {
         Error("Can't open file '", file_name, "' for reading.");
      }

      file.seekg(0, std::ios::end);
      const long file_size = file.tellg();
      file.seekg(0, std::ios::beg);

      file_content = std::make_unique<char[]>(file_size + 1);
      file.read(file_content.get(), file_size);
      file_content[file_size] = '\0';

      file.close();
   }

   m_root = std::make_unique<ParsedNode>(-1);
   m_root->children = std::make_unique<std::vector<ParsedNode>>();
   
   long line_number = 1;
   const char* token_start = nullptr;
   const char* curr_char = file_content.get();

   std::vector<ParsedNode*> nodes_stack;

   ParsedNode* curr_parent = m_root.get();
   ParsedNode* curr_node = nullptr;
   
   do
   {
      curr_parent->children->emplace_back(0);
      curr_node = &curr_parent->children->back();

      SkipSpaces(curr_char, line_number);
      if ('\0' == *curr_char)
      {
         SyntaxError(line_number, "Node name is expected.");
      }
      
      if (!GetQualifier(curr_char, curr_node->name))
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
         curr_node->children = std::make_unique<std::vector<ParsedNode>>();
         curr_parent = curr_node;
         continue;
      }
      else if ('"' == *curr_char)
      {
         if (!GetQuotedString(curr_char, curr_node->value))
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
