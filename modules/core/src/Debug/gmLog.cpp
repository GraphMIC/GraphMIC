#include "gmLog.hpp"

#include <iostream>
#include <sstream>

#include <QThread>
#include <QApplication>

namespace gm
{
    std::mutex Log::m_mutex;
    
    auto Log::format(std::string format, va_list args) -> std::string
    {
        char buffer[256];
        vsnprintf(buffer, 256, format.c_str(), args);
        return buffer;
    }

    auto Log::logInfo_f(std::string formatString, ...) -> void
    {
        std::lock_guard<std::mutex> lock(instance->m_mutex);

        auto threadString = QApplication::instance() ? QApplication::instance()->thread() == QThread::currentThread() ? "main " : "task " : "n/a  ";

        va_list args;
        va_start(args, formatString);
        std::string out = threadString + format(formatString, args) + "\n";
        std::cout << out;
    }
            
    auto Log::logInfo(std::stringstream ss) -> void
    {
        std::lock_guard<std::mutex> lock(instance->m_mutex);

        auto threadString = QApplication::instance() ? QApplication::instance()->thread() == QThread::currentThread() ? "main " : "task " : "n/a  ";

        std::stringstream out;
        out << threadString << ss.str() << "\n";
        std::cout << out.str();
    }
        
    auto Log::logTrace(Type type, std::stringstream ss) -> void
    {
        std::lock_guard<std::mutex> lock(instance->m_mutex);
        
        std::string typeString;

        auto threadString = QApplication::instance() ? QApplication::instance()->thread() == QThread::currentThread() ? "main " : "task " : "n/a  ";
            
        switch (type) {
            case New: typeString        = "* "; break;
            case Get: typeString        = "< "; break;
            case Set: typeString        = "> "; break;
            case Func: typeString       = "| "; break;
            case Del: typeString        = "~ "; break;
            case Default: typeString    = "  "; break;
        }
            
        std::stringstream out;
        
        out << threadString << typeString << " " << ss.str() << "\n";
        
        std::cout << out.str();
    }
    
    auto Log::logTrace(Type type) -> void
    {
        std::lock_guard<std::mutex> lock(instance->m_mutex);
        
        std::string typeString;

        auto threadString = QApplication::instance() ? QApplication::instance()->thread() == QThread::currentThread() ? "main " : "task " : "n/a  ";

        switch (type) {
            case New: typeString        = "* "; break;
            case Get: typeString        = "< "; break;
            case Set: typeString        = "> "; break;
            case Func: typeString       = "| "; break;
            case Del: typeString        = "~ "; break;
            case Default: typeString    = "  "; break;
        }
                    
        std::stringstream out;
            
        out << threadString << typeString << "\n";
            
        std::cout << out.str();
    }
}