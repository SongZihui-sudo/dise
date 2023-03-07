#ifndef PARSER_H
#define PARSER_H

#include <functional>
#include <memory>
#include <tinyxml.h>
#include <unordered_map>


#include "../components.h"

namespace dise
{
/**
 * @brief xml 解析器
 *
 */
class Parser
{
public:
    typedef std::shared_ptr< Parser > ptr;
    /**
     * @brief 构造函数
     *
     */
    Parser(){};

    /**
     * @brief 销毁对象
     *
     */
    ~Parser() { delete this->doc; };

    /**
     * @brief 读取 xml 文件
     *
     * @param _filename 文件名
     */
    bool read( std::string _filename );

    /**
     * @brief 生成元器件清单
     *
     * @param _node xml 节点
     */
    void generate_component_list( TiXmlElement* _node );

    /**
     * @brief 预处理，获取元器件类型，名称，输出输出信息
     *
     * @param _node xml 节点
     */
    void generate_meta_data_list( TiXmlElement* _node );

private:
    /**
     * @brief 查找指定节点
     *
     * @param pRootEle 开始查找位置的指针
     * @param strNodeName 节点名
     * @param destNode 结果
     * @return true
     * @return false
     */
    bool GetNodePointerByName( TiXmlElement* pRootEle, const char* strNodeName, TiXmlElement*& destNode );

private:
    TiXmlDocument* doc; /* xml 文档对象 */
private:
    std::unordered_map< std::string, int > m_component_list; /* 元器件清单 */
    std::unordered_map< std::string, component > meta_data_list; /* 元器件类型，名称，输出输出信息 */
};
}
#endif
