#pragma once

#include "gmLogicBase.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Object;
            class Input;
            class Output;
            class Component;
            class Bool;
            class Number;
            class String;
            class Vector;
            class Option;
            class Dir;
            class Files;
        }

        namespace Object
        {
            class Node;
        }
        
        class Logic : public gm::Logic::Base
        {
        private:
            Node::Object*   m_nodeObject;
            Object::Node*   m_nodePython;
        private:
            auto setupBoolParam(Node::Bool*) -> void;
            auto setupNumberParam(Node::Number*) -> void;
            auto setupStringParam(Node::String*) -> void;
            auto setupVectorParam(Node::Vector*) -> void;
            auto setupOptionParam(Node::Option*) -> void;
            auto setupDirParam(Node::Dir*) -> void;
            auto setupFilesParam(Node::Files*) -> void;
            auto setupInput(Node::Input*) -> void;
            auto setupOutput(Node::Output*) -> void;
        public:
            Logic(Node::Object*);
            auto run() -> void override;
            ~Logic();
        };
    }
}