#ifndef analyzer_h
#define analyzer_h

#include "../parser/parser.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace dise
{

/**
 * @brief ������
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
        /* ��ȡ��������������Ϣ */
        std::unordered_map< std::string, component > tmp = this->m_parser->get_meta_data();
        /* ����Ԫ����Ԫ���� */
        for ( auto it = tmp.begin(); it != tmp.end(); it++ )
        {
            /* ��Ԫ����Ԫ������Ϣ�����������������Ϣ�� */
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
     * @brief ԭ���Եķ���ÿ��Ԫ�����Ĺܽ���Ϣ
     * @return bool
     */
    bool atom_analyze();

private:
    /**
     * @brief ����Ԫ�����Ĺܽ���Ϣ
     * @param _componentԪ����
     * @return bool�ܽ�
     */
    bool analyze_pin( component& _component );

private:
    Parser::ptr m_parser; /* ������ */
    std::unordered_map< std::string, std::tuple< component, bool > > _detail; /* ������������Ԫ��������Ϣ */
};

}

#endif
