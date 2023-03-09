#ifndef analyzer_h
#define analyzer_h

#include "../parser/parser.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace dise
{

/**
 * @brief 分析器
 */
class Analyzer
{
public:
    typedef std::shared_ptr< Analyzer > ptr;

    Analyzer( Parser::ptr _parser )
    : m_parser( _parser )
    {
        if ( !_parser )
        {
            return;
        }
        /* 获取解析器处理后的信息 */
        std::unordered_map< std::string, component > tmp = this->m_parser->get_meta_data();
        /* 遍历元器件元数据 */
        for ( auto it = tmp.begin(); it != tmp.end(); it++ )
        {
            /* 将元器件元数据信息插入分析器处理后的信息中 */
            if ( it->second.m_type == "vcc" || it->second.m_type == "gnd" )
            {
                this->_detail[it->first] = std::make_tuple( it->second, true );
            }
            else
            {
                this->_detail[it->first] = std::make_tuple( it->second, false );
            }
        }
    }

    /**
     * @brief 原子性的分析每个元器件的管脚信息
     * @return bool
     */
    bool atom_analyze();

private:
    /**
     * @brief 分析元器件的管脚信息
     * @param _component元器件
     * @return bool管脚
     */
    bool analyze_pin( component& _component );

private:
    Parser::ptr m_parser; /* 解析器 */
    std::unordered_map< std::string, std::tuple< component, bool > > _detail; /* 分析器处理后各元器件的信息 */
};

}

#endif
