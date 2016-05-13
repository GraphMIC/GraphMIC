#include "gmIOGraph.hpp"

#include "gmIONode.hpp"
#include "gmIOFile.hpp"
#include "gmIOPath.hpp"
#include "gmIOJson.hpp"

#include "gmNodeList.hpp"
#include "gmNodeGraph.hpp"
#include "gmNodeObject.hpp"
#include "gmConnectionObject.hpp"
#include "gmSlotInputBase.hpp"
#include "gmSlotOutputBase.hpp"

#include "gmLog.hpp"

#include <QHash>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

namespace gm
{
    namespace IO
    {
        namespace Graph
        {
            auto ToJsonFile(const QString& path, gm::Node::Graph* graph) -> void
            {
                log_trace(Log::Func);
                
                if (path.isEmpty())
                {
                    log_exception("IO::Graph::ToJsonFile: no path specified");
                    throw std::runtime_error("IO::Graph::ToJsonFile: no path specified");
                }
                
                if (!graph)
                {
                    log_exception("IO::Graph::ToJsonFile: nullptr object received");
                    throw std::runtime_error("IO::Graph::ToJsonFile: nullptr object received");
                }

                auto name           = Path::ExtractFileName(path);
                auto nodes          = graph->getNodes();
                auto connections    = graph->getConnections();

                graph->setPath(path);
                graph->setName(name);
                
                QJsonObject json;
                QJsonArray jsonNodes;
                QJsonArray jsonConnections;
                QJsonArray jsonPosition;
                
                auto position = graph->getPosition();
                
                jsonPosition.append(position.x());
                jsonPosition.append(position.y());
                
                json["graph"]      = graph->getName();
                json["position"]   = jsonPosition;
                
                for (auto node : nodes)
                {
                    jsonNodes.append(IO::Node::ToJsonObject(node));
                }
                
                json["nodes"] = jsonNodes;
                
                for (auto connection : connections)
                {
                    QJsonObject jsonConnection;
                    
                    auto input = connection->getInput();
                    auto output = connection->getOutput();
                    
                    jsonConnection["i_slot"] = input->getName();
                    jsonConnection["o_slot"] = output->getName();
                    jsonConnection["i_node"] = QString().sprintf("%8p", input->getNode());
                    jsonConnection["o_node"] = QString().sprintf("%8p", output->getNode());
                    
                    jsonConnections.append(jsonConnection);
                }
                
                json["connections"] = jsonConnections;
                
                QJsonDocument doc(json);
                
                File::Write(path, doc.toJson());

                graph->setModified(false);
            }
            
            auto FromJsonFile(const QString& path) -> gm::Node::Graph*
            {
                log_trace(Log::Func);
                
                if (path.isEmpty())
                {
                    log_exception("IO::Graph::FromJsonFile: no path specified");
                    throw std::runtime_error("IO::Graph::FromJsonFile: no path specified");
                }
                
                auto json = Json::FromFile(path);
                
                auto graph              = new gm::Node::Graph();
                auto jsonName           = json["graph"].toString();
                auto jsonNodes          = json["nodes"].toArray();
                auto jsonConnections    = json["connections"].toArray();
                auto jsonPos            = json["position"].toArray();
                auto nodeMap            = QHash<QString, gm::Node::Object*>();
                
                graph->setName(jsonName);
                graph->setPath(path);
                
                graph->setPosition(jsonPos.at(0).toInt(),jsonPos.at(1).toInt());
                
                for (auto i = 0; i < jsonNodes.count(); ++i)
                {
                    auto jsonNode = jsonNodes.at(i).toObject();
                    auto node = IO::Node::FromJsonObject(jsonNode);
                    
                    nodeMap [jsonNode["id"].toString()] = node;
                    graph->addNode(node);
                }
                
                for (auto i = 0; i < jsonConnections.count(); ++i)
                {
                    auto jsonConnection = jsonConnections.at(i).toObject();
                    auto inputNodeID    = jsonConnection["i_node"].toString();
                    auto outputNodeID   = jsonConnection["o_node"].toString();
                    auto inputName      = jsonConnection["i_slot"].toString();
                    auto outputName     = jsonConnection["o_slot"].toString();
                    
                    if (!nodeMap.contains(inputNodeID) || !nodeMap.contains(outputNodeID))
                    {
                        throw new std::runtime_error("io format exception");
                    }
                    
                    auto inputNode          = nodeMap.value(inputNodeID);
                    auto outputNode         = nodeMap.value(outputNodeID);
                    auto inputComponents    = inputNode->getComponentMap();
                    auto outputComponents   = outputNode->getComponentMap();
                    
                    auto inputComponent     = inputComponents.value(inputName);
                    auto outputComponent    = outputComponents.value(outputName);

                    inputComponent->as<Slot::InputBase>()->connect(outputComponent->as<Slot::OutputBase>());
                }

                graph->setModified(false);
                
                return graph;
            }
        }
    }
}
