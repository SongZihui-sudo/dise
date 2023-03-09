#include <string>

#include "../log/log.h"
#include "parser.h"

namespace dise
{

static star::Logger::ptr g_logger( STAR_NAME( "global_logger" ) );

bool Parser::read( std::string _filename )
{
    this->doc     = new TiXmlDocument( _filename );
    bool loadOkay = this->doc->LoadFile();
    if ( !loadOkay )
    {
        ERROR_STD_STREAM_LOG( g_logger )
        << "Failed to load file " << _filename << star::Logger::endl();
        return false;
    }
    DEBUG_STD_STREAM_LOG( g_logger ) << "Load file: " << _filename << " ok!" << star::Logger::endl();
    return true;
}

void Parser::generate_component_list( TiXmlElement* _node )
{
    if ( !_node )
    {
        return;
    }
    for ( TiXmlElement* currentele = _node; currentele; currentele = currentele->NextSiblingElement() )
    {
        TiXmlElement* tmpele = currentele;
        if ( !tmpele->ValueStr().empty() )
        {
            /* 获取元器件类型名 */
            std::string attributValue = tmpele->Attribute( "type" );
            if ( m_component_list.find( attributValue ) == m_component_list.end() )
            {
                m_component_list.insert( std::pair< std::string, int >( attributValue, 1 ) );
            }
            else
            {
                m_component_list[attributValue]++;
            }
        }
    }
}

bool Parser::GetNodePointerByName( TiXmlElement* pRootEle, const char* strNodeName, TiXmlElement*& destNode )
{
    if ( !pRootEle )
    {
        return false;
    }
    // if equal root node then return
    if ( 0 == strcmp( strNodeName, pRootEle->Value() ) )
    {
        destNode = pRootEle;
        return true;
    }

    TiXmlElement* pEle = pRootEle;
    for ( pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement() )
    {
        // recursive find sub node return node pointer
        if ( 0 != strcmp( pEle->Value(), strNodeName ) )
        {
            GetNodePointerByName( pEle, strNodeName, destNode );
        }
        else
        {
            destNode = pEle;
            return true;
        }
    }

    return false;
}

void Parser::generate_meta_data_list( TiXmlElement* _node )
{
    if ( !_node )
    {
        return;
    }
    for ( TiXmlElement* currentele = _node; currentele; currentele = currentele->NextSiblingElement() )
    {
        TiXmlElement* tmpele = currentele;
        if ( !tmpele->ValueStr().empty() )
        {
            /* 获取元器件类型名 */
            std::string attributValue = tmpele->Attribute( "type" );
            /* 获取元器件的名 */
            component tmp;
            if ( tmpele->ValueStr() == "component" )
            {
                /* 获取元器件的名与类型 */
                tmp.m_name = tmpele->Attribute( "name" );
                tmp.m_type = tmpele->Attribute( "type" );
                /* 获取元器件输入管脚信息 */
                TiXmlElement* m_input_ele = new TiXmlElement( "input" );
                GetNodePointerByName( tmpele, "input", m_input_ele );
                for ( TiXmlElement* currentele = m_input_ele->FirstChildElement(); currentele;
                      currentele               = currentele->NextSiblingElement() )
                {
                    tmp.m_inputs.insert( std::pair< std::string, bool >( currentele->GetText(), false ) );
                }
                /* 获取元器件输出管脚信息 */
                TiXmlElement* m_output_ele = new TiXmlElement( "output" );
                GetNodePointerByName( tmpele, "output", m_output_ele );
                for ( TiXmlElement* currentele = m_output_ele->FirstChildElement(); currentele;
                      currentele               = currentele->NextSiblingElement() )
                {
                    tmp.m_outputs.insert( std::pair< std::string, bool >( currentele->GetText(), false ) );
                }
            }
            else if ( tmpele->ValueStr() == "vcc" || tmpele->ValueStr() == "gnd" )
            {
                /* 获取元器件的名与类型 */
                tmp.m_name                = tmpele->Attribute( "name" );
                tmp.m_type                = tmpele->Attribute( "type" );
                TiXmlElement* m_input_ele = new TiXmlElement( "value" );
                GetNodePointerByName( tmpele, "value", m_input_ele );
                tmp.m_inputs.insert( std::pair< std::string, bool >( m_input_ele->GetText(), false ) );
                tmp.m_outputs = tmp.m_inputs;
            }
            else
            {
                ERROR_STD_STREAM_LOG( g_logger )
                << "No such component: " << attributValue << star::Logger::endl();
                return;
            }
            meta_data_list.insert( std::pair< std::string, component >( tmp.m_name, tmp ) );
        }
    }
    return;
}

TiXmlElement* Parser::get_main_element()
{
    TiXmlElement* tmp = new TiXmlElement( "main" );
    GetNodePointerByName( get_first_element(), "main", tmp );
    if ( !tmp )
    {
        return nullptr;
    }
    return tmp->FirstChildElement();
}

}
