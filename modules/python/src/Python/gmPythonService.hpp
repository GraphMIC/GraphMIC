#pragma once
#include <boost/python.hpp>
#include <boost/numpy.hpp>

namespace gm
{
    namespace Python
    {
        using namespace boost::python;

        namespace Object
        {
            class Node;
        }

        class Service
        {
        private:
            PyThreadState*  m_GlobalThreadState;
            char*           m_PythonHome;
        public:
            static Service* instance;
        public:
            Service();
            ~Service();
            static auto Create() -> Service*;
            auto startInterpreter() -> void;
            auto startThreadedInterpreter() -> PyThreadState*;
            auto stopInterpreter() -> void;
            auto stopThreadedInterpreter(PyThreadState* threadState) -> void;
            auto prepareForThreading() -> void;
            auto finalizeThreading() -> void;
            auto runSimpleString(std::string script) -> std::string;
            auto runSimpleString(std::string script, Object::Node* node) -> std::string;
            auto parsePythonException() -> std::string;
        };
    }
}