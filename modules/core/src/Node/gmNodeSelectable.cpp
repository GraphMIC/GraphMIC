#include "gmLog.hpp"
#include "gmNodeGraph.hpp"
#include "gmNodeEditor.hpp"
#include "gmNodeSelectable.hpp"

namespace gm
{
    namespace Node
    {
        Selectable::Selectable() : m_selected(false)
        {
            log_trace(Log::New, this);
        }
        
        auto Selectable::setSelected(bool selected) -> void
        {
            log_trace(Log::Set, selected);
            
            if (this->m_selected != selected)
            {
                this->m_selected = selected;
                emit this->selectedChanged();

                if (selected && this->onSelected)
                {
                    this->onSelected();
                }
            }
        }
        
        auto Selectable::getSelected() -> bool
        {
            log_trace(Log::Get);
            
            return this->m_selected;
        }
        
        auto Selectable::select() -> void
        {
            log_trace(Log::Func);
            
            setSelected(true);
            Editor::instance->select(this);
        }
        
        Selectable::~Selectable()
        {
            log_trace(Log::Del, this);
        }
    }
}