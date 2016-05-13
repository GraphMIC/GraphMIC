#include "gmTestCase.hpp"

#include "gmNodeObject.hpp"
#include "gmLogicBase.hpp"
#include "gmTestImageProvider.hpp"
#include "gmTestUnit.hpp"
#include "gmAsync.hpp"

#include <QJsonValue>
#include <QJsonObject>

namespace gm
{
    namespace Test
    {
        Case::Case()
        {
        }

        auto Case::init() -> void
        {
            if (this->m_node)
            {
                this->initImageReferences();
            }
        }

        auto Case::FromJson(QJsonValue json) -> Case*
        {
            auto testCase = new Case();
            testCase->m_attributeMap = json.toObject().toVariantMap();
            testCase->m_pass = testCase->m_attributeMap.value("pass").toBool();

            return testCase;
        }

        auto Case::addImageInfo(const QString& imageInfo) -> void
        {
            if (this->m_imageInfo.length() > 0)
            {
                this->m_imageInfo += " x ";
            }

            this->m_imageInfo += imageInfo;
        }

        auto Case::getImageInfo() -> QString
        {
            return this->m_imageInfo;
        }

        auto Case::select() -> void
        {
            if (!this->m_selected)
            {
                this->m_testUnit->onCaseSelected(this);
                this->setSelected(true);
            }
        }

        auto Case::setSelected(bool selected) -> void
        {
            if (this->m_selected != selected)
            {
                this->m_selected = selected;
                emit this->selectedChanged();
            }
        }

        auto Case::isSelected() -> bool
        {
            return this->m_selected;
        }

        auto Case::setNumber(int number) -> void
        {
            this->m_number = number;
        }

        auto Case::getNumber() -> int
        {
            return this->m_number;
        }

        auto Case::setNode(Node::Object* node) -> void
        {
            log_trace(Log::Func);

            this->m_node = node;
            node->setForceExecution(true);
        }

        auto Case::setFinished(bool finished) -> void
        {
            if (this->m_finished != finished)
            {
                this->m_finished = finished;
                emit this->finishedChanged();
            }
        }

        auto Case::getFinished() -> bool
        {
            return this->m_finished;
        }
        
        auto Case::getPass() -> bool
        {
            return this->m_pass;
        }
    
        auto Case::run() -> void
        {
            if (this->m_node)
            {
                this->applyAttributes();
                this->m_node->executeTask();
            }
        }

        auto Case::setRunning(bool running) -> void
        {
            if (this->m_running != running)
            {
                this->m_running = running;
                emit this->runningChanged();
            }
        }

        auto Case::isRunning() -> bool
        {
            return this->m_running;
        }
        
        auto Case::setPassed(bool passed) -> void
        {
            if (this->m_passed != passed)
            {
                this->m_passed = passed;
                emit this->passedChanged();
            }
        }

        auto Case::setOutput(const QString& output) -> void
        {
            this->m_output = output;
            emit this->outputChanged();
        }

        auto Case::getOutput() -> QString
        {
            return this->m_output;
        }

        auto Case::setTestUnit(Unit* testUnit) -> void
        {
            this->m_testUnit = testUnit;
        }

        auto Case::getPassed() -> bool
        {
            return this->m_passed;
        }

        auto Case::initImageReferences() -> void
        {
            log_trace(Log::Func);

            auto components     = this->m_node->getComponentMap();
            auto logic          = this->m_node->getLogic();
            auto keys           = this->m_attributeMap.keys();

            this->m_output      = "unprocessed";
            this->m_imageInfo   = "";

            for (auto key : keys)
            {
                auto component = logic->getComponent(key);

                if (!component)
                {
                    continue;
                }

                auto type = component->getComponentType();

                if (type == Component::Type::Input)
                {
                    auto input = logic->getInputBase(key);

                    if (input->getDataType() == Data::Type::Image)
                    {
                        auto imageList = m_attributeMap.value(key).toList();
                        QStringList refList;

                        if (imageList.isEmpty())
                        {
                            auto attribMap = m_attributeMap.value(key).toMap();

                            QString typeString = attribMap["type"].toString();

                            if (typeString.isEmpty())
                            {
                                typeString = "a";
                            }

                            auto attribString = QString::number(attribMap["dim"].toInt()) + "d-" + attribMap["pixel"].toString() + "-" + attribMap["component"].toString();
                            auto imageName = typeString + "-" + attribString;
                            this->addImageInfo(attribString);

                            refList.append(imageName);

                            this->m_imageRefMap.insert(input, refList);
                        }
                        else
                        {

                            for (auto i = 0; i < imageList.count(); ++i)
                            {
                                auto attribMap = imageList.at(i).toMap();

                                QString typeString = attribMap["type"].toString();

                                if (typeString.isEmpty())
                                {
                                    typeString = "a";
                                }

                                auto attribString = QString::number(attribMap["dim"].toInt()) + "d-" + attribMap["pixel"].toString() + "-" + attribMap["component"].toString();
                                auto imageName = typeString + "-" + attribString;

                                if (i == 0)
                                {
                                    this->addImageInfo(attribString);
                                }

                                refList.append(imageName);
                            }

                            this->m_imageRefMap.insert(input, refList);
                        }
                    }
                }
            }
        }

        auto Case::applyAttributes() -> void
        {
            log_trace(Log::Func);

            auto components     = this->m_node->getComponentMap();
            auto logic          = this->m_node->getLogic();
            auto keys           = this->m_attributeMap.keys();

            this->setOutput("");

            if (this->m_node)
            {
                this->m_node->failureFunction = [this](const QString& errorMessage, Node::Object* node){
                    this->setOutput(errorMessage);
                    this->setPassed(!this->m_pass);
                    this->setFinished(true);
                    this->m_testUnit->onCaseFailed(this);
                };

                this->m_node->successFunction = [this]() {
                    this->setPassed(this->m_pass);
                    this->setOutput("passed");
                    this->setFinished(true);
                    this->m_testUnit->onCasePassed(this);
                };
            }

            for (auto input : logic->getInputs())
            {
                input->clearMockData();
            }

            for (auto output : logic->getOutputs())
            {
                output->clear();
            }

            for (auto key : keys)
            {
                auto component = logic->getComponent(key);

                if (!component)
                {
                    continue;
                }

                auto type = component->getComponentType();

                switch (type)
                {
                    case Component::Type::Number:
                    {
                        component->as<Param::Number>()->setValue(m_attributeMap.value(key).toDouble());
                        break;
                    }
                    case Component::Type::String:
                    {
                        component->as<Param::String>()->setValue(m_attributeMap.value(key).toString());
                        break;
                    }
                    case Component::Type::Bool:
                    {
                        component->as<Param::Bool>()->setValue(m_attributeMap.value(key).toBool());
                        break;
                    }
                    case Component::Type::Dir:
                    {
                        component->as<Param::Dir>()->setDir(m_attributeMap.value(key).toString());
                        break;
                    }
                    case Component::Type::Vector:
                    {
                        auto entries = m_attributeMap.value(key).toList();
                        auto vector = component->as<Param::Vector>();

                        vector->setX(entries[0].toDouble());
                        vector->setY(entries[1].toDouble());
                        vector->setZ(entries[2].toDouble());
                        vector->setW(entries[3].toDouble());

                        break;
                    }
                    case Component::Type::Input:
                    {
                        auto input = logic->getInputBase(key);

                        if (input->getDataType() == Data::Type::Image)
                        {
                            if (this->m_imageRefMap.contains(input))
                            {
                                auto imageRefs = this->m_imageRefMap.value(input);
                                auto imageInput = reinterpret_cast<Slot::Input<Data::Image>*>(input);

                                for (auto imageRef : imageRefs)
                                {
                                    imageInput->addMockData(ImageProvider::instance->getImage(imageRef));
                                }
                            }
                        }
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
    }
}
