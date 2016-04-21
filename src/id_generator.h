namespace SoftLab
{
   
class IDGenerator
{
public:
   IDGenerator();
   long Next();
   
private:
   long m_curr_id;
};
   
} // namespace SoftLab
