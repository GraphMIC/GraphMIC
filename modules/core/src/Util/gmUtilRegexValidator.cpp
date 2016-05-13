#include "gmUtilRegexValidator.hpp"

namespace gm
{
    namespace Util
    {
        RegexValidator::RegexValidator()
        {
        }
        
        auto RegexValidator::checkMatch() -> void
        {
            return this->m_regex.indexIn(this->m_input) < 0 ? setMatch(false) : setMatch(true);
        }
        
        auto RegexValidator::setInput(const QString &input) -> void
        {
            this->m_input = input;
            emit this->inputChanged();
            
            this->checkMatch();
        }
        
        auto RegexValidator::setRegex(const QString &regex) -> void
        {
            this->m_regex.setPattern(regex);
            emit this->regexChanged();
            
            this->checkMatch();
        }
        
        auto RegexValidator::setMatch(bool match) -> void
        {
            this->m_match = match;
            emit this->matchChanged();
        }
        
        auto RegexValidator::getMatch() -> bool
        {
            return this->m_match;
        }
        
        auto RegexValidator::getInput() -> QString
        {
            return this->m_input;
        }
        
        auto RegexValidator::getRegex() -> QString
        {
            return this->m_regex.pattern();
        }
        
        RegexValidator::~RegexValidator()
        {
        }
    }
}

