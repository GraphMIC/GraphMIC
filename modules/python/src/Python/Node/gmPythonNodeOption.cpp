#include "gmPythonNodeOption.hpp"

#include <QRegularExpression>

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Option::Option(Object* node) : Param(gm::Component::Type::Option, node)
            {
                this->setName("option param");

                this->m_options.append("option 1");
            }

            auto Option::setIndex(int index) -> void
            {
                if (this->m_index != index)
                {
                    this->m_index = index;
                    emit this->indexChanged();
                }
            }

            auto Option::changeOption(const QString& label, int index) -> void
            {
                this->m_options.replace(index, label);

                emit this->optionsChanged();
                emit this->indexChanged();
            }

            auto Option::addOption() -> void
            {
                this->m_options.append("option " + QString::number(this->m_options.count() + 1));
                emit this->optionsChanged();

                this->setIndex(this->m_options.count() - 1);
            }

            auto Option::removeOption() -> void
            {
                if (this->m_options.count() > 1)
                {
                    this->m_options.removeAt(this->m_index);
                    emit this->optionsChanged();
                    this->setIndex(std::max(0, this->m_index - 1));
                }
            }

            auto Option::getOptions() -> QStringList
            {
                return this->m_options;
            }

            auto Option::getIndex() -> int
            {
                return this->m_index;
            }
        }
    }
}
