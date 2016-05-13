#include "gmPythonLogic.hpp"

#include "gmPythonNodeObject.hpp"
#include "gmPythonNodeNumber.hpp"
#include "gmPythonNodeInput.hpp"
#include "gmPythonNodeOutput.hpp"
#include "gmPythonNodeVector.hpp"
#include "gmPythonNodeString.hpp"
#include "gmPythonNodeBool.hpp"
#include "gmPythonNodeDir.hpp"
#include "gmPythonNodeOption.hpp"
#include "gmPythonNodeFiles.hpp"

#include "gmSlotConstraints.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace Python
    {
        Logic::Logic(Node::Object* node) : gm::Logic::Base("python", node->getName())
        {
            log_trace(Log::New);

            auto inputs     = node->getInputs();
            auto outputs    = node->getOutputs();
            auto params     = node->getParams();

            for (auto input : inputs)
            {
                setupInput(input);
            }

            for (auto param : params)
            {
                auto name = param->getName();
                switch (param->getComponentType())
                {
                    case gm::Component::Type::Bool:
                        setupBoolParam(reinterpret_cast<Node::Bool*>(param));
                        break;
                    case gm::Component::Type::String:
                        setupStringParam(reinterpret_cast<Node::String*>(param));
                        break;
                    case gm::Component::Type::Number:
                        setupNumberParam(reinterpret_cast<Node::Number*>(param));
                        break;
                    case gm::Component::Type::Vector:
                        setupVectorParam(reinterpret_cast<Node::Vector*>(param));
                        break;
                    case gm::Component::Type::Dir:
                        setupDirParam(reinterpret_cast<Node::Dir*>(param));
                        break;
                    case gm::Component::Type::Files:
                        setupFilesParam(reinterpret_cast<Node::Files*>(param));
                        break;
                    case gm::Component::Type::Option:
                        setupOptionParam(reinterpret_cast<Node::Option*>(param));
                        break;
                    default: break;
                }
            }

            for (auto output : outputs)
            {
                setupOutput(output);
            }

            this->setForceExecution(node->getForceExecution());
            this->setDocLink(node->getDocLink());
            this->setRunnable(node->isRunnable());
            this->setUseTimer(true);
        }

        auto Logic::setupInput(Node::Input* input) -> void
        {
            auto dataConnection = input->isRequired() ? Data::Connection::Required : Data::Connection::Optional;

            switch (gm::Data::TypeFromIndex(input->getDataTypeID()))
            {
                case Data::Type::Image:
                    this->add(new Slot::Input<Data::Image>(input->getName(), input->getConstraints(), dataConnection));
                    break;
                case Data::Type::Number:
                    this->add(new Slot::Input<Data::Number>(input->getName(), dataConnection));
                    break;
                case Data::Type::Vector:
                    this->add(new Slot::Input<Data::Vector>(input->getName(), dataConnection));
                    break;
                case Data::Type::Pointset:
                    this->add(new Slot::Input<Data::Pointset>(input->getName(), dataConnection));
                    break;
            }
        }

        auto Logic::setupOutput(Node::Output* output) -> void
        {
            switch (gm::Data::TypeFromIndex(output->getDataTypeID()))
            {
                case Data::Type::Image:
                    this->add(new Slot::Output<Data::Image>(output->getName(), output->getConstraints()));
                    break;
                case Data::Type::Number:
                    this->add(new Slot::Output<Data::Number>(output->getName()));
                    break;
                case Data::Type::Vector:
                    this->add(new Slot::Output<Data::Vector>(output->getName()));
                    break;
                case Data::Type::Pointset:
                    this->add(new Slot::Output<Data::Pointset>(output->getName()));
                    break;
            }
        }

        auto Logic::setupBoolParam(Node::Bool* component) -> void
        {
            this->add(new Param::Bool(component->getName(), component->getValue()));
        }

        auto Logic::setupNumberParam(Node::Number* component) -> void
        {
            this->add(new Param::Number(component->getName(), component->getValue(), component->getMin(), component->getMax()));
        }

        auto Logic::setupStringParam(Node::String* component) -> void
        {
            this->add(new Param::String(component->getName(), component->getValue(), ""));
        }

        auto Logic::setupVectorParam(Node::Vector* component) -> void
        {
            this->add(new Param::Vector(component->getName(), component->getLabels(), component->getValues()));
        }

        auto Logic::setupOptionParam(Node::Option* component) -> void
        {
            this->add(new Param::Option(component->getName(), component->getOptions()));
        }

        auto Logic::setupDirParam(Node::Dir* component) -> void
        {
            this->add(new Param::Dir(component->getName(), component->getTitle()));
        }

        auto Logic::setupFilesParam(Node::Files* component) -> void
        {
            this->add(new Param::Files(component->getName(), component->getTitle(), component->getFilter()));
        }

        auto Logic::run() -> void
        {
            log_info("yodelborsten");
        }

        Logic::~Logic()
        {
            log_trace(Log::Del);
        }
    }
}
