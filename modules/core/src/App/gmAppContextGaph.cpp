#include "gmAppContextGraph.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace App
    {
        namespace Context
        {
            Graph* Graph::instance = nullptr;
            
            Graph::Graph() : Base("Node")
            {
                log_trace(Log::New);
                
                if (instance)
                {
                    throw "instance already existing";
                }
                
                instance = this;
            }

            auto Graph::Create() -> Graph*
            {
                log_trace(Log::Func);
                
                return new Graph();
            }
            
            Graph::~Graph()
            {
                log_trace(Log::Del, this);
            }
        }
    }
}