#include "gmIONode.hpp"
#include "gmIOFile.hpp"
#include "gmIOPath.hpp"
#include "gmIOJson.hpp"

#include "gmNodeObject.hpp"
#include "gmNodeFactory.hpp"

#include "gmLogicBase.hpp"
#include "gmComponentBase.hpp"
#include "gmParamBool.hpp"
#include "gmParamString.hpp"
#include "gmParamDir.hpp"
#include "gmParamOption.hpp"
#include "gmParamFiles.hpp"
#include "gmParamVector.hpp"
#include "gmParamNumber.hpp"
#include "gmSlotInputBase.hpp"
#include "gmSlotOutputBase.hpp"

#include "gmLog.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariantMap>

namespace gm
{
    namespace IO
    {
        namespace Node
        {
            auto ToJsonObject(gm::Node::Object* node) -> QJsonObject
            {
                log_trace(Log::Func);
                
                QJsonObject json;
                QJsonObject jsonComponents;
                QJsonArray jsonPosition;
                
                auto pos = node->getPosition();
                
                jsonPosition.append(pos.x());
                jsonPosition.append(pos.y());
                
                json["id"]         = QString().sprintf("%8p", node);
                json["name"]       = node->getName();
                json["prefix"]     = node->getLib();
                json["layer"]      = node->getLayer();
                json["expanded"]   = node->getExpanded();
                json["position"]   = jsonPosition;
                
                auto components = node->getComponents();
                
                for (auto component : components)
                {
                    auto name = component->getName();
                    
                    switch (component->getComponentType())
                    {
                        case Component::Type::Bool:
                            jsonComponents[name] = component->as<Param::Bool>()->getValue();
                            break;
                        case Component::Type::Dir:
                            jsonComponents[name] = component->as<Param::Dir>()->getDir();
                            break;
                        case Component::Type::Files:
                        {
                            QJsonArray jsonPaths;
                            auto paths = component->as<Param::Files>()->getFilePaths();
                            
                            for (auto path : paths)
                            {
                                jsonPaths.append(path);
                            }
                            
                            jsonComponents [name] = jsonPaths;
                            break;
                        }
                        case Component::Type::Vector:
                        {
                            QJsonArray jsonValues;
                            auto values = component->as<Param::Vector>()->getValues();
                            
                            jsonValues.append(values[0]);
                            jsonValues.append(values[1]);
                            jsonValues.append(values[2]);
                            jsonValues.append(values[3]);
                            
                            jsonComponents[name] = jsonValues;
                            break;
                        }
                        case Component::Type::Input:
                            jsonComponents[name] = QString().sprintf("%8p", component);
                            break;
                        case Component::Type::Output:
                            jsonComponents[name] = QString().sprintf("%8p",component);
                            break;
                        case Component::Type::Number:
                            jsonComponents[name] = component->as<Param::Number>()->getValue();
                            break;
                        case Component::Type::Option:
                            jsonComponents[name] = component->as<Param::Option>()->getIndex();
                            break;
                        case Component::Type::String:
                            jsonComponents[name] = component->as<Param::String>()->getValue();
                            break;
                        default: break;
                    }
                }
                
                json["components"] = jsonComponents;
                
                return json;
            }
            
            auto FromJsonObject(QJsonObject json) -> gm::Node::Object*
            {
                log_trace(Log::Func);

                auto name           = json["name"].toString();
                auto layer          = json["layer"].toInt();
                auto prefix         = json["prefix"].toString();
                auto jsonPosition   = json["position"].toArray();
                auto values         = json["components"].toObject().toVariantMap();
                auto keys           = values.keys();
                auto node           = gm::Node::Factory::Create(prefix + "::" + name);
                auto logic          = node->getLogic();
                
                auto components     = node->getComponentMap();
                
                for (auto key : keys)
                {
                    auto component = logic->getComponent(key);
                    
                    if (!component)
                    {
                        throw new std::runtime_error("unmapped component");
                    }
                    
                    auto type = component->getComponentType();
                        
                    switch (type)
                    {
                        case Component::Type::Number:
                        {
                            component->as<Param::Number>()->setValue(values.value(key).toDouble());
                            break;
                        }
                        case Component::Type::String:
                        {
                            component->as<Param::String>()->setValue(values.value(key).toString());
                            break;
                        }
                        case Component::Type::Bool:
                        {
                            component->as<Param::Bool>()->setValue(values.value(key).toBool());
                            break;
                        }
                        case Component::Type::Dir:
                        {
                            component->as<Param::Dir>()->setDir(values.value(key).toString());
                            break;
                        }
                        case Component::Type::Vector:
                        {
                            auto entries = values.value(key).toList();
                            auto vector = component->as<Param::Vector>();
                            
                            vector->setX(entries[0].toDouble());
                            vector->setY(entries[1].toDouble());
                            vector->setZ(entries[2].toDouble());
                            vector->setW(entries[3].toDouble());

                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                }

                node->setLayer(layer);
                node->setGeometry(jsonPosition.at(0).toInt(), jsonPosition.at(1).toInt(), 200, 0);
                
                return node;
            }
        }
    }
}
