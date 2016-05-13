#pragma once

#include "gmCoreExport.hpp"
#include "gmImageAttributes.hpp"

#include <QBitArray>
#include <QObject>
#include <bitset>

namespace gm
{
    namespace Data
    {
        class Base;
    }

    namespace Slot
    {
        class GM_CORE_EXPORT Constraints : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QList<int> scalars READ getScalars NOTIFY scalarsChanged);
        private:
            QList<int> m_scalars;
            std::bitset<4> m_dimensionBits;
            std::bitset<8> m_scalarBits;
            std::bitset<8> m_rgbBits;
            std::bitset<8> m_rgbaBits;
        public:
            Constraints() = delete;
            Constraints(std::bitset<4>, std::bitset<8>, std::bitset<8>, std::bitset<8>);
            auto getScalars() -> QList<int>;
            auto updateBits() -> void;
            auto debugPrint() -> void;
            auto dimension(unsigned int) -> bool;
            auto scalarPixel(Image::Component::ID) -> bool;
            auto rgbPixel(Image::Component::ID) -> bool;
            auto rgbaPixel(Image::Component::ID) -> bool;
            auto accept(Data::Base*) -> bool;
        signals:
            void scalarsChanged();
        };
    }
}