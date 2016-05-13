#include "gmPythonService.hpp"
#include "gmPythonOutput.hpp"
#include "gmApp.hpp"
#include "gmLog.hpp"
#include "gmPythonObjectNode.hpp"
#include "gmPythonObjectParam.hpp"
#include "gmPythonObjectInput.hpp"
#include "gmPythonObjectOutput.hpp"

#include <QByteArray>

namespace gm
{
    namespace Python
    {
        struct qstring_to_python_str
        {
            static PyObject* convert(QString const& s)
            {
                return boost::python::incref(boost::python::object(s.toStdString()).ptr());
            }
        };

        template<class ListType>
        struct qlist_to_python_list
        {
            static PyObject* convert(ListType const& list)
            {
                boost::python::list pyList;
                for (int i = 0; i < list.size(); ++i)
                {
                    pyList.append( boost::python::object(list[i]) );
                }
                return boost::python::incref( pyList.ptr() );
            }
        };

        BOOST_PYTHON_MODULE(gm)
        {
            using namespace boost::python;

            class_<gm::Python::Object::Image>("image")
            .def("getData", &gm::Python::Object::Image::getData)
            .def("getOrigin", &gm::Python::Object::Image::getOrigin)
            .def("getSpacing", &gm::Python::Object::Image::getSpacing)
            .def("getDimensions", &gm::Python::Object::Image::getDimensions)
            .def("getNumberOfComponents", &gm::Python::Object::Image::getNumberOfComponents)
            .def("setData", &gm::Python::Object::Image::setData)
            .def("setOrigin", &gm::Python::Object::Image::setOrigin)
            .def("setSpacing", &gm::Python::Object::Image::setSpacing)
            .def("setDimensions", &gm::Python::Object::Image::setDimensions)
            .def("setNumberOfComponents", &gm::Python::Object::Image::setNumberOfComponents);

            class_<gm::Python::Object::Param>("param", no_init)
            .def("bool", &gm::Python::Object::Param::getBool)
            .def("string", &gm::Python::Object::Param::getString)
            .def("number", &gm::Python::Object::Param::getNumber)
            .def("files", &gm::Python::Object::Param::getFiles)
            .def("option", &gm::Python::Object::Param::getOption)
            .def("vector", &gm::Python::Object::Param::getVector)
            .def("dir", &gm::Python::Object::Param::getDir);

            class_<gm::Python::Object::Input>("input", no_init)
            .def("vector", &gm::Python::Object::Input::getVector)
            .def("number", &gm::Python::Object::Input::getNumber)
            .def("image", &gm::Python::Object::Input::getImage, return_value_policy<manage_new_object>());

            class_<gm::Python::Object::Output>("output", no_init)
            .def("image", &gm::Python::Object::Output::setImage)
            .def("vector", &gm::Python::Object::Output::setVector)
            .def("number", &gm::Python::Object::Output::setNumber);

            class_<gm::Python::Object::Node>("node", no_init)
            .add_property("param", make_function(&gm::Python::Object::Node::getParam, return_internal_reference<>()))
            .add_property("input", make_function(&gm::Python::Object::Node::getInput, return_internal_reference<>()))
            .add_property("output", make_function(&gm::Python::Object::Node::getOutput, return_internal_reference<>()));
        }

        Service* Service::instance = nullptr;

        Service::Service()
        {
            log_trace(Log::New);

            if (instance)
            {
                throw new std::runtime_error("instance already existing");
            }

            QByteArray ba = Application::instance->getResourceDir().toLatin1();

            this->m_PythonHome = ba.data();
            instance = this;

            boost::python::to_python_converter<QString, qstring_to_python_str>();
            boost::python::to_python_converter<QList<QString>, qlist_to_python_list<QList<QString>>>();
        }

        Service::~Service()
        {
            this->finalizeThreading();
        }

        auto Service::Create() -> Service*
        {
            log_trace(Log::Func);

            return new Service();
        }

        auto Service::parsePythonException() -> std::string
        {
            PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
            PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);

            std::string ret("Unfetchable Python error");

            if(type_ptr != NULL)
            {
                handle<> h_type(type_ptr);
                str type_pstr(h_type);
                extract<std::string> e_type_pstr(type_pstr);
                if(e_type_pstr.check())
                {
                    ret = e_type_pstr();
                }
                else
                {
                    ret = "Unknown exception type";
                }
            }

            if(value_ptr != NULL)
            {
                handle<> h_val(value_ptr);
                str a(h_val);
                extract<std::string> returned(a);
                if(returned.check())
                {
                    ret +=  ": " + returned();
                }
                else
                {
                    ret += std::string(": Unparseable Python error: ");
                }

            }

            if(traceback_ptr != NULL)
            {
                handle<> h_tb(traceback_ptr);

                object tb(import("traceback"));
                object fmt_tb(tb.attr("format_tb"));
                object tb_list(fmt_tb(h_tb));
                object tb_str(str("\n").join(tb_list));
                extract<std::string> returned(tb_str);

                if(returned.check())
                {
                    ret += ": " + returned();
                }
                else
                {
                    ret += std::string(": Unparseable Python traceback");
                }
            }

            return ret;
        }

        auto Service::startInterpreter() -> void
        {
            Py_NoSiteFlag = false;
            Py_SetPythonHome(m_PythonHome);
            Py_Initialize();

            boost::numpy::initialize();
        }

        auto Service::stopInterpreter() -> void
        {
            Py_Finalize();
        }

        auto Service::startThreadedInterpreter() -> PyThreadState*
        {
            PyEval_AcquireLock();
            PyThreadState* localThreadState = Py_NewInterpreter();

            PyEval_ReleaseThread(localThreadState);
            PyEval_AcquireThread(localThreadState);

            Py_NoSiteFlag = false;
            Py_SetPythonHome(m_PythonHome);
            Py_Initialize();

            boost::numpy::initialize();

            return localThreadState;
        }

        auto Service::stopThreadedInterpreter(PyThreadState* threadState) -> void
        {
            PyEval_ReleaseThread(threadState);
            PyEval_AcquireThread(threadState);

            Py_EndInterpreter(threadState);

            PyEval_ReleaseLock();
        }

        auto Service::prepareForThreading() -> void
        {
            PyImport_AppendInittab("gm", initgm);
            Py_Initialize();
            PyEval_InitThreads();

            this->m_GlobalThreadState = PyEval_SaveThread();
        }

        auto Service::finalizeThreading() -> void
        {
            PyEval_RestoreThread(m_GlobalThreadState);
            Py_Finalize() ;
        }

        auto Service::runSimpleString(std::string script, Object::Node* node) -> std::string
        {
            object main_module((handle<>(borrowed(PyImport_AddModule("__main__")))));
            object main_namespace = main_module.attr("__dict__");

            Output redirector;
            redirector.setBufferSize(1000);

            boost::python::type_info info = boost::python::type_id<Output>();
            const boost::python::converter::registration* reg = boost::python::converter::registry::query(info);

            if (reg == NULL ||(*reg).m_to_python == NULL)
            {
                main_namespace["Output"] = class_<Output>("Output", init<>())
                .def("write", &Output::write);
            }

            boost::python::import("sys").attr("stderr") = redirector;
            boost::python::import("sys").attr("stdout") = redirector;
            boost::python::import("gm");

            main_namespace["node"] = boost::python::object(boost::python::ptr(node));

            handle<> ignored(( PyRun_String(script.c_str(),
                                            Py_file_input,
                                            main_namespace.ptr(),
                                            main_namespace.ptr())));
            
            return redirector.GetOutput();
        }


        auto Service::runSimpleString(std::string script) -> std::string
        {
            object main_module((handle<>(borrowed(PyImport_AddModule("__main__")))));
            object main_namespace = main_module.attr("__dict__");

            Output redirector;
            redirector.setBufferSize(1000);

            boost::python::type_info info = boost::python::type_id<Output>();
            const boost::python::converter::registration* reg = boost::python::converter::registry::query(info);

            if (reg == NULL ||(*reg).m_to_python == NULL)
            {
                main_namespace["Output"] = class_<Output>("Output", init<>())
                .def("write", &Output::write);
            }

            boost::python::import("sys").attr("stderr") = redirector;
            boost::python::import("sys").attr("stdout") = redirector;

            handle<> ignored(( PyRun_String(script.c_str(),
                                            Py_file_input,
                                            main_namespace.ptr(),
                                            main_namespace.ptr())));

            return redirector.GetOutput();
        }
    }
}