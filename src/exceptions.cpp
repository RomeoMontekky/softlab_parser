#include "exceptions.h"

namespace SoftLab
{
   
Exception::Exception(const std::string& description) :
   m_description(description)
{
}

const std::string& Exception::GetDescription() const
{
   return m_description;
}

SyntaxException::SyntaxException(
   long line_number, const std::string& description) :
      Exception(description), m_line_number(line_number)
{
}

long SyntaxException::GetLineNumber() const
{
   return m_line_number;
}

void FormatString(std::stringstream& stream)
{
}
   
} // namespace SoftLab
