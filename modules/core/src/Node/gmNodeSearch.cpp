#include "gmLog.hpp"

#include "gmNodeGraph.hpp"
#include "gmNodeEditor.hpp"
#include "gmNodeSearch.hpp"
#include "gmNodeObject.hpp"
#include "gmNodeFactory.hpp"
#include "gmNodeSearchItem.hpp"
#include "gmNotificationController.hpp"

namespace gm
{
    namespace Node
    {
        Search* Search::instance = nullptr;
        
        Search::Search()
        {
            log_trace(Log::New, this);
            
            this->m_visible = false;
            
            if (instance)
            {
                throw "instance already existing";
            }
            
            instance = this;
            this->m_matches = GetEntries();
        }
        
        auto Search::Create() -> Search*
        {
            log_trace(Log::Func);
            
            return new Search();
        }
        
        auto Search::GetEntries() -> QList<QObject*>&
        {
            static QList<QObject*> List;
            return List;
        }
        
        auto Search::AddEntry(const QString& identifier) -> void
        {
            QStringList queryWords = identifier.split("::");
            
            GetEntries().append(new SearchItem(queryWords.at(0), queryWords.at(1)));
        }
                
        auto Search::setVisible(bool flag) -> void
        {
            log_trace(Log::Set, flag);

            if (this->m_visible != flag)
            {
                this->m_visible = flag;
                emit this->visibleChanged();
            }
        }
        
        auto Search::getMatches() -> QList<QObject*>
        {
            log_trace(Log::Get);
            
            return this->m_matches;
        }
        
        auto Search::getVisible() -> bool
        {
            log_trace(Log::Get);
            
            return this->m_visible;
        }
        
        auto Search::updateMatches() -> void
        {
            log_trace(Log::Func);
            
            if (this->m_query.isEmpty())
            {
                this->m_matches = GetEntries();
            }
            else
            {
                this->m_matches.clear();
                
                QStringList queryWords = this->m_query.split(QRegExp("\\s+"));

                auto entries = this->GetEntries();

                for (auto e : entries)
                {
                    auto entry = reinterpret_cast<SearchItem*>(e);
                    bool matching = false;
                    
                    for (auto word : queryWords)
                    {
                        if (entry->contains(word))
                        {
                            matching = true;
                        }
                    }
                    
                    if (matching)
                    {
                        this->m_matches.append(e);
                    }
                }
            }
            
            emit this->matchesChanged();
        }
        
        auto Search::processQuery() -> void
        {
            log_trace(Log::Func);
            
            if (this->m_matches.length() > 0)
            {
                if (Editor::instance->getGraph()->getNodeCount() >= Graph::MaxNodeCount)
                {
                    Notification::Controller::Post(Notification::Type::Info, "Node count limit reached.");
                    return;
                }
                
                auto match  = reinterpret_cast<SearchItem*>(this->m_matches.at(0));
                auto node   = Factory::Create(match->m_prefix + "::" + match->m_name);
                auto spawn  = Editor::instance->getSpawn();

                if (node)
                {
                    node->setGeometry(spawn.x(), spawn.y(), 200, 0);
                    auto graph = Editor::instance->getGraph();

                    if (graph == nullptr)
                    {
                        throw new std::runtime_error("no graph instance");
                    }

                    graph->addNode(node);
                }
                else
                {
                    Notification::Controller::Post(Notification::Type::Warning, "Unable to create Node \'" + match->m_prefix + "::" + match->m_name + "\'");
                }
            }
        }

        auto Search::contains(const QString& identifier) -> bool
        {
            auto entries = GetEntries();

            for (auto e : entries)
            {
                auto entry = reinterpret_cast<SearchItem*>(e);

                if (entry->matches(identifier))
                {
                    return true;
                }
            }

            return false;
        }
        
        auto Search::setQuery(const QString& query) -> void
        {
            log_trace(Log::Set);
            
            this->m_query = query;
            emit this->queryChanged();

            updateMatches();
        }
        
        auto Search::getQuery() -> QString
        {
            log_trace(Log::Get);
            
            return this->m_query;
        }
        
        Search::~Search()
        {
            log_trace(Log::Del, this);
        }
    }
}
