#include "exception.h"

namespace SoftLab
{
   
Exception::Exception(const std::string& description, long line_number) :
   m_description(description), m_line_number(line_number)
{
}

const std::string& Exception::GetDescription() const
{
   return m_description;
}

long Exception::GetLineNumber() const
{
   return m_line_number;
}

void FormatString(std::stringstream& stream)
{
}
   
} // namespace SoftLab
