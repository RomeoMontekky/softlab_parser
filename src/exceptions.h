#include <string>
#include <sstream>

namespace SoftLab
{
   
class Exception
{
public:
   Exception(const std::string& description);
   Exception(const char description[]);

   const std::string& GetDescription() const;
   
private:
   std::string m_description;
};

class SyntaxException : public Exception
{
public:
   SyntaxException(long line_number, const std::string& description);
   SyntaxException(long line_number, const char description[]);

   long GetLineNumber() const;

private:
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

void SyntaxError(long line_number, const char description[]);

} // namespace SoftLab
