#pragma  once

#include "gmViewerExport.hpp"

#include "QVTKInternalOpenglRenderWindow.h"
#include "QVTKQuickItem.h"

#include <QQuickFramebufferObject>
#include <vtkFrameBufferObject2.h>

class GM_VIEWER_EXPORT QVTKFramebufferObjectRenderer : public QQuickFramebufferObject::Renderer
{
	
public:
	bool m_neverRendered;
	bool m_readyToRender;
	vtkInternalOpenGLRenderWindow *m_vtkRenderWindow;
	vtkFrameBufferObject2* m_vtkFBO;

	QVTKQuickItem *m_vtkQuickItem;

public:
	QVTKFramebufferObjectRenderer(vtkInternalOpenGLRenderWindow *rw);
	~QVTKFramebufferObjectRenderer();

	virtual void synchronize(QQuickFramebufferObject * item);
	virtual void render();

	QOpenGLFramebufferObject *createFramebufferObject(const QSize &size);

	friend class vtkInternalOpenGLRenderWindow;
};
