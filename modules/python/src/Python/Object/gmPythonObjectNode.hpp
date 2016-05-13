#pragma once

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
            class Param;
            class Output;
            class Input;

            class Node
            {
            public:
                gm::Node::Object* m_node;
                Param*  m_param;
                Input*  m_input;
                Output* m_output;
            public:
                Node();
                ~Node();
                auto setNode(gm::Node::Object* node) -> void;
                auto getParam() -> Param*;
                auto getInput() -> Input*;
                auto getOutput() -> Output*;
            };
        }

    }
}