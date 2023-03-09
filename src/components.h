#ifndef components_h
#define components_h

#include <cstddef>
#include <string>
#include <unordered_map>

namespace dise
{
/**
 * @brief 元器件管脚信息
 *
 */
struct pin
{
    pin(){};
    pin( std::string _name, std::string _type, std::size_t _index, std::string _connect, int _value )
    : m_name( _name )
    , m_type( _type )
    , m_index( _index )
    , m_connect( _connect )
    , m_value( _value )
    {
    }
    std::string m_name;
    std::string m_type;
    std::size_t m_index;
    std::string m_connect;
    int m_value;
};

/**
 * @brief 元器件信息
 *
 */
struct component
{
    component(){};
    component( std::string _name, std::string _type, std::unordered_map< std::string, pin > _pins )
    : m_name( _name )
    , m_type( _type )
    , m_pins( _pins )
    {
    }
    std::string m_name;
    std::string m_type;
    std::unordered_map< std::string, pin > m_pins;
};
}

#endif
