#pragma  once

#include "gmViewerExport.hpp"
#include <vtkGenericOpenGLRenderWindow.h>
#include <qopenglframebufferobject.h>
#include <QOpenGLFunctions>

class QVTKFramebufferObjectRenderer;

class GM_VIEWER_EXPORT vtkInternalOpenGLRenderWindow : public vtkGenericOpenGLRenderWindow
{
public:
	static vtkInternalOpenGLRenderWindow* New();
	vtkTypeMacro(vtkInternalOpenGLRenderWindow, vtkGenericOpenGLRenderWindow)

	virtual void OpenGLInitState();
	virtual void Render();
	void OpenGLEndState();
	void InternalRender();
	void SetFramebufferObject(QOpenGLFramebufferObject *fbo);

	QVTKFramebufferObjectRenderer *QtParentRenderer;

protected:
	vtkInternalOpenGLRenderWindow();
	~vtkInternalOpenGLRenderWindow();
	
};
