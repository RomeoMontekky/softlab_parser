#include "parser.h"
#include "exceptions.h"
#include "id_generator.h"
#include "utils.h"

#include <fstream>
#include <memory>
#include <iomanip>

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

      // Read the whole file at once to optimize HD access.
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
   nodes_stack.reserve(20); // empirical value

   ParsedNode* curr_parent = m_root.get();
   ParsedNode* curr_node = nullptr;
   
   IDGenerator generator;
   
   do
   {
      curr_parent->children->emplace_back(generator.Next());
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
   
   if (!nodes_stack.empty())
   {
      SyntaxError(line_number, "Closing brace is missing.");
   }
}

namespace
{
   
void SaveToImpl(std::ofstream& file, const Parser::ParsedNode& node, long parent_id)
{
   file << "| " << 
      std::setw(8)  <<  node.id <<  " | " <<
      std::setw(8)  <<  parent_id << " | " <<
      std::setw(20) <<  node.name.get() << " | " <<
      std::setw(20) << (node.value.get() != nullptr ? node.value.get() : "") << 
          " |" << std::endl;
   
   if (node.children.get() != nullptr)
   {
      for (const auto& child : *node.children)
      {
         SaveToImpl(file, child, node.id);
      }
   }
}

} // namespace

void Parser::SaveTo(const char file_name[])
{
   // In real comercial product writing to the file must be buffered,
   // but, as this is just a traning task only, let's keep it as is, 
   // relying on buffering that OS does.
   
   std::ofstream file(file_name);
   if (!file.is_open())
   {
      Error("Can't open file '", file_name, "' for writing.");
   }
   
   const std::string header = 
         "|       Id |   Par.Id |                 Name |                Value |";
   const std::string horizontal_line(header.size(), '-');
   
   file << horizontal_line << std::endl;
   file << header << std::endl;
   file << horizontal_line << std::endl;

   for (const auto& child : *m_root->children)
   {
      SaveToImpl(file, child, m_root->id);
   }
   
   file << horizontal_line << std::endl;
}
   
} // namespace SoftLab
