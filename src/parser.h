#include <string>
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
   
private:
   struct ParsedNode;
   std::unique_ptr<ParsedNode> m_root;
};

} // namespace SoftLab
