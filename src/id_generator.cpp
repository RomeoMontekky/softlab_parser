#include "id_generator.h"

namespace SoftLab
{
   
IDGenerator::IDGenerator() : m_curr_id(0)
{
}

long IDGenerator::Next()
{
   return m_curr_id++;
}
   
} // namespace SoftLab
