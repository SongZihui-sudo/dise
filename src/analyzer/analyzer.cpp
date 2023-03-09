#include "analyzer.h"
#include <stack>

bool dise::Analyzer::atom_analyze()
{
    /* 遍历元器件 */
    for ( auto it = this->_detail.begin(); it != this->_detail.end(); it++ )
    {
        component current = std::get< 0 >( it->second );
        /*  */
        if ( std::get< 1 >( it->second ) )
        {
            analyze_pin( current ); /* 分析元器件的引脚 */
            this->_detail[current.m_name] = std::make_tuple( current, true ); /* 更新元器件的状态 */
        }
    }
    return true;
}

bool dise::Analyzer::analyze_pin( component& _component )
{
    /* 遍历元器件的引脚 */
    for ( auto it = _component.m_pins.begin(); it != _component.m_pins.end(); it++ )
    {
        pin current = it->second;
        std::stack< std::tuple< std::string, pin > > sp;
        while ( true )
        {
            component next_componect = std::get< 0 >( this->_detail[current.m_connect] );
            pin next                 = next_componect.m_pins[current.m_connect];
            sp.push( std::make_tuple( next_componect.m_name, next ) );
            if ( next.m_value != -1 || std::get< 1 >( this->_detail[current.m_connect] ) )
            {
                break;
            }
            current = next;
        }

        /* 由栈中的内容进行倒推 */
        while ( !sp.empty() )
        {
            pin tmp = std::get< 1 >( sp.top() );
            sp.pop();
            std::get< 1 >( sp.top() ).m_value = tmp.m_value;
            std::get< 0 >( this->_detail[std::get< 0 >( sp.top() )] )
            .m_pins[std::get< 1 >( sp.top() ).m_name]
            .m_value
            = tmp.m_value;
        }
    }
    return true;
}
