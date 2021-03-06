﻿#include <string>
#include <vector>
#include <memory>

namespace SoftLab
{
   
class Parser
{
public:
   Parser();
   ~Parser();

   void Parse(const char file_name[]);
   void SaveTo(const char file_name[]);
   
   // Trick with forward declaration is needed to hide details
   // of ParsedNode implementation from the calling code.
   struct ParsedNode;
   
private:
   std::unique_ptr<ParsedNode> m_root;
};

} // namespace SoftLab
