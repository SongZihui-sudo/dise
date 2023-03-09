#include "../../parser/parser.h"
#include "../analyzer.h"
#include <iostream>
#include <string>

int main()
{
    dise::Parser::ptr parser( new dise::Parser() );
    std::string path     = "C:\\Users\\songz\\Desktop\\dise\\diagram\\test_diag.xml";
    bool tmp             = parser->read( path );
    TiXmlElement* xmldoc = parser->get_main_element();
    if ( tmp )
    {
        parser->generate_meta_data_list( xmldoc );
        parser->generate_component_list( xmldoc );
        dise::Analyzer::ptr analyzer( new dise::Analyzer( parser ) );
        analyzer->atom_analyze();
    }
    return 0;
}
