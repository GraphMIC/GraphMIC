#pragma once

#include "gmLog.hpp"
#include "gmLogicFactory.hpp"
#include "gmNodeSearch.hpp"

#include <QtQml>

namespace gm
{
    namespace Logic
    {
        template <class T>
        class Register
        {
        public:
            Register() = delete;
            
            Register(const QString& prefix, const QString& name, const QString& link = 0)
            {
                auto identifier = prefix + "::" + name;
                
                Factory::RegisterLogic(identifier, [link](void) -> T* {
                    auto logic = new T();
                    logic->setDocLink(link);

                    return logic;
                });

                Node::Search::AddEntry(identifier);
            }
        };
    }
}