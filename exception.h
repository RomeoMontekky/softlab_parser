#include <string>
#include <sstream>

namespace SoftLab
{
   
class Exception
{
public:
   Exception(const std::string& description, long line_number = -1);
   
   const std::string& GetDescription() const;
   long GetLineNumber() const;
   
private:
   std::string m_description;
   long m_line_number;
};

void FormatString(std::stringstream& stream);

template <typename FirstParamType, typename ...OtherParamsType>
void FormatString(
   std::stringstream& stream, 
   const FirstParamType& first_param, 
   const OtherParamsType&... other_params)
{
   stream << first_param;
   FormatString(stream, other_params...);
}

template <typename ...Args>
void Error(const Args&... args)
{
   std::stringstream stream;
   FormatString(stream, args...);
   throw Exception(stream.str());
}

template <typename ...Args>
void SyntaxError(long line_number, const Args&... args)
{
   std::stringstream stream;
   FormatString(stream, args...);
   throw Exception(stream.str(), line_number);
}

} // namespace SoftLab
