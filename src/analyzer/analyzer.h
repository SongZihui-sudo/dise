#ifndef analyzer_h
#define analyzer_h

#include "../parser/parser.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace dise
{

class Analyzer
{
public:
    typedef std::shared_ptr< Analyzer > ptr;

    Analyzer( Parser::ptr _parser )
    : m_parser( _parser )
    {
    }

    bool analyze();

private:
    Parser::ptr m_parser;
};

}

#endif
