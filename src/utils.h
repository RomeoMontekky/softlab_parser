#include <string>

namespace SoftLab
{

void SkipSpaces(const char*& curr_char, long& line_number);
bool GetQualifier(const char*& curr_char, std::string& value);
bool GetQuotedString(const char*& curr_char, std::string& value);

} // namespace SoftLab
