#include <string>

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture() = default;

    void BindTo(unsigned slot);
private:
    int m_Width, m_Height; 
    unsigned m_Handle;
};