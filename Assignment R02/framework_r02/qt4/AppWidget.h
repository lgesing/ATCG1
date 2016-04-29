//=============================================================================
//                                                                            
//       Copyright (C) 2010 by Computer Graphics Group, University of Bonn
//                           cg.cs.uni-bonn.de
//                                                                            
//-----------------------------------------------------------------------------
//   
//	part of RMI1, SS10, Excercise 1 
//  
//
//=============================================================================

#ifndef RAYTRACER_APPWIDGET_h
#define RAYTRACER_APPWIDGET_h

//== INCLUDES =================================================================

#include <QtGui/QMenu>
#include <QtGui/QImage>
#include <QtGui/QMainWindow>

#include "Raytracer.h"
#include "SurfaceList.h"
#include "PhongShader.h"
#include "LambertShader.h"
#include "GlassShader.h"
#include "TextureShader.h"

//== FORWARDS =================================================================



//== CLASS DEFINITION =========================================================


class CAppWidget: public QMainWindow 
{
	Q_OBJECT
public:
	CAppWidget();
	~CAppWidget();

protected:
	void mousePressEvent( QMouseEvent* e );

private slots:
	void slotPopupMenu_RenderScene();
	void slotPopupMenu_DifferenceImage();
	void slotPopupMenu_ShowReferenceImage();
	void slotPopupMenu_Save();

	
private:		
	QImage            m_clQImage;
	QMenu*   	      m_pclPopupMenu;
	QLabel*			  m_pclLabel;
	QLabel*			  m_pclLabelReference;
	QString           m_referenceImageName;

	RAYTRACER::CWhitted      m_clWhittedRaytracer;
	RAYTRACER::CSurfaceList  m_clScene;
	
	RAYTRACER::CPhongShader*   m_pclSphereShader0;
	RAYTRACER::CGlassShader*   m_pclSphereShader2;
	RAYTRACER::CLambertShader*   m_pclSphereShader1;
	RAYTRACER::CTextureShader* m_pclPlaneShader;

	void Scene0();
	void Scene1();
};

//=============================================================================
#endif // RAYTRACER_APPWIDGET_H
//=============================================================================
