#pragma once
#include <QList>
#include "gmComponentBase.hpp"

#include "boost/numpy.hpp"
#include "boost/python.hpp"

namespace gm
{
    namespace Node
    {
        class Object;
    }

    namespace Python
    {
        namespace Object
        {
            class Param
            {
            private:
                gm::Node::Object*       m_node;
                std::array<double, 4>*  m_vector;
            public:
                Param();
                ~Param();
                auto setNode(gm::Node::Object* node) -> void;
                auto getBool(std::string id) -> bool;
                auto getNumber(std::string id) -> double;
                auto getString(std::string id) -> QString;
                auto getOption(std::string id) -> int;
                auto getDir(std::string id) -> QString;
                auto getFiles(std::string id) -> QList<QString>;
                auto getVector(std::string id) -> boost::numpy::ndarray;
            };
        }
    }
}