#pragma once

#include "gmDataBase.hpp"
#include "gmCoreExport.hpp"

#include <QString>
#include <mitkImage.h>
#include <mitkDataNode.h>

namespace gm
{
    namespace Image
    {
        class Attributes;
    }

    namespace Data
    {
        class GM_CORE_EXPORT Image : public Base
        {
            Q_OBJECT
            Q_PROPERTY(QString componentString READ getComponentString CONSTANT);
            Q_PROPERTY(QString pixelString READ getPixelString CONSTANT);
            Q_PROPERTY(unsigned int dimension READ getDimension CONSTANT);
            Q_PROPERTY(bool isImage READ getIsImage CONSTANT);
        private:
            mitk::DataNode::Pointer m_mitkDataNode;
            mitk::Image::Pointer m_mitkImage;
            gm::Image::Attributes* m_attributes;
        public:
            static Type DataType;
        private:
            auto getIsImage() -> bool;
        public:
            Image(mitk::Image::Pointer);
            static auto FromFile(const QString&) -> Image*;
            auto saveToDir(const QString&) -> void;
            auto getDimension() -> unsigned int;
            auto getComponentString() -> QString;
            auto getPixelString() -> QString;
            auto getMitkImage() -> mitk::Image::Pointer;
            auto getMitkDataNode() -> mitk::DataNode::Pointer;
            auto getAttributes() -> gm::Image::Attributes*;
            auto printDebugInfo() -> void;
            ~Image();
        };
    }
}