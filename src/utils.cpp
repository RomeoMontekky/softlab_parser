#include "utils.h"

#include <cstring>
#include <cctype>
#include <cassert>

namespace SoftLab
{

void SkipSpaces(const char*& curr_char, long& line_number)
{
   while (*curr_char != '\0' && std::isspace(*curr_char))
   {
      if ('\n' == *curr_char)
      {
         ++line_number;
      }
      ++curr_char;
   }
}

bool GetQualifier(const char*& curr_char, std::unique_ptr<char[]>& value)
{
   value.reset();
   
   if ('\0' == *curr_char)
   {
      return false;
   }

   const char* start = curr_char;

   // First symbol must be either undersore or alphabetic one.
   if (!std::isalpha(*curr_char) && *curr_char != '_')
   {
      return false;
   }

   ++curr_char;

   // Other symbols must be all alphanumeric.
   while (*curr_char != '\0' && !std::isspace(*curr_char))
   {
      if (!std::isalnum(*curr_char))
      {
         return false;
      }
      ++curr_char;
   }

   value = std::make_unique<char[]>(curr_char - start + 1);
   std::strncpy(value.get(), start, curr_char - start);

   return true;
}

bool GetQuotedString(const char*& curr_char, std::unique_ptr<char[]>& value)
{
   assert('"' == *curr_char);
   value.reset();
   
   const char* start = ++curr_char;
   while (*curr_char != '\0' && *curr_char != '"' && *curr_char != '\n')
   {
      ++curr_char;
   }

   if (*curr_char != '"')
   {
      return false;
   }

   value = std::make_unique<char[]>(curr_char - start + 1);
   std::strncpy(value.get(), start, curr_char - start);
   
   ++curr_char;

   return true;
}

} // namespace SoftLab
