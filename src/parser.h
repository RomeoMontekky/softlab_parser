#include <string>
#include <vector>

namespace SoftLab
{
   
class Parser
{
public:
   Parser();

   void Parse(const char file_name[]);
   void SaveTo(const char file_name[]);
   
private:
   struct ParsedNode
   {
      std::string m_name;
      std::string m_value;
      std::vector<ParsedNode> m_children;
   };
   
   ParsedNode m_root;
};

} // namespace SoftLab
