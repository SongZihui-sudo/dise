#ifndef components_h
#define components_h

#include <cstddef>
#include <string>
#include <unordered_map>

struct component
{
    std::string m_name;
    std::string m_type;
    std::unordered_map< std::string, bool > m_inputs;
    std::unordered_map< std::string, bool > m_outputs;
};

#endif
