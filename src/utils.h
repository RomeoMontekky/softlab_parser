#include <string>
#include <memory>

namespace SoftLab
{

void SkipSpaces(const char*& curr_char, long& line_number);
bool GetQualifier(const char*& curr_char, std::unique_ptr<char[]>& value);
bool GetQuotedString(const char*& curr_char, std::unique_ptr<char[]>& value);

} // namespace SoftLab
