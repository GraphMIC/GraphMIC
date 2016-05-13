#pragma once
#include <boost/python.hpp>
#include <boost/circular_buffer.hpp>

namespace gm
{
    namespace Python
    {
        class Output
        {
        typedef boost::circular_buffer<std::string> ContainerType;
        private:
            static ContainerType m_outputs;
            unsigned int m_bufferSize = 1000;
        public:
            void setBufferSize(unsigned int buffer)
            {
                this->m_bufferSize = buffer;
            }

            void write( std::string const& str )
            {
                if (m_outputs.capacity()<m_bufferSize)
                    m_outputs.resize(m_bufferSize);
                m_outputs.push_back(str);
            }
            
            static std::string GetOutput()
            {
                std::string ret;
                std::stringstream ss;
                for(auto it=m_outputs.begin(); it!=m_outputs.end(); it++)
                {
                    ss << *it;
                }
                m_outputs.clear();
                ret =  ss.str();
                return ret;
            }
        };

        Output::ContainerType Output::m_outputs;
    }
}