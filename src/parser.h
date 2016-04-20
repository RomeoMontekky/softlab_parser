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

   Parser(const Parser& rhs) = delete;
   Parser(Parser&& rhs) = delete;
   Parser& operator =(const Parser& rhs) = delete;
   Parser& operator =(Parser&& rhs) = delete;

   void Parse(const char file_name[]);
   void SaveTo(const char file_name[]);
   
private:
   struct ParsedNode;
   std::unique_ptr<ParsedNode> m_root;
};

} // namespace SoftLab
