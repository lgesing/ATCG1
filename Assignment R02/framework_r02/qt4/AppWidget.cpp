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

//=============================================================================
//
//  CLASS CAppWidget - IMPLEMENTATION
//
//=============================================================================


//== INCLUDES =================================================================
#include <QtGui/QImage>
#include <QtGui/QLabel>
#include <QtGui/QFileDialog>
#include <QtGui/QMouseEvent>
#include <QtGui/QHBoxLayout>
#include <QImageReader>
#include <QMessageBox>

#include "AppWidget.h"

#include "PointLight.h"
#include "DirectionalLight.h"
#include "Plane.h"
#include "Sphere.h"

//== STATIC CONST ========================================================== 

static const int I_SCENE = 1;
static const int I_MAX_DEPTH = 10;
static const int I_IMAGE_SIZE_X = 512;
static const int I_IMAGE_SIZE_Y = 512;

//== IMPLEMENTATION ========================================================== 

using namespace RAYTRACER;

CAppWidget::CAppWidget()
	: m_pclSphereShader0(0)
	, m_pclSphereShader1(0)
	, m_pclSphereShader2(0)
{
	m_pclPopupMenu = new QMenu(this);
	connect( m_pclPopupMenu->addAction("&Render scene"), SIGNAL(triggered()), this, SLOT(slotPopupMenu_RenderScene()));
	m_pclPopupMenu->addSeparator();
	connect( m_pclPopupMenu->addAction("&Difference image..."), SIGNAL(triggered()), this, SLOT(slotPopupMenu_DifferenceImage()));
	connect( m_pclPopupMenu->addAction("Show reference &image..."), SIGNAL(triggered()), this, SLOT(slotPopupMenu_ShowReferenceImage()));
	connect( m_pclPopupMenu->addAction("&Save result..."), SIGNAL(triggered()), this, SLOT(slotPopupMenu_Save()));

	//Global settings
	m_clWhittedRaytracer.GetCamera().Reset();
	m_clWhittedRaytracer.SetBackgroundColor( ColorType(	0.078, 0.361, 0.753) );
	m_clWhittedRaytracer.SetAmbientColor( ColorType(0.5) );

	m_clQImage = QImage( I_IMAGE_SIZE_X, I_IMAGE_SIZE_Y, QImage::Format_RGB32 );
	m_pclLabel = new QLabel();
	m_pclLabel->setPixmap(QPixmap::fromImage(m_clQImage));
	m_pclLabel->setScaledContents(true);

	QFile referenceImageFile("reference_image.bmp");
	if (!referenceImageFile.exists()) {
		referenceImageFile.setFileName("../reference_image.bmp");
	}
	if (!referenceImageFile.exists()) {
		QString fileName = QFileDialog::getOpenFileName(this, tr("Open reference image"), "./", tr("Image Files (*.png *.jpg *.bmp)"));
		referenceImageFile.setFileName(fileName);
	}
	m_referenceImageName = referenceImageFile.fileName();
	m_pclLabelReference = new QLabel();
	m_pclLabelReference->setPixmap(QPixmap(m_referenceImageName));
	m_pclLabelReference->setScaledContents(true);

	QWidget* centralWidget = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout(centralWidget);
	layout->addWidget(m_pclLabelReference);
	layout->addWidget(m_pclLabel);
	this->setCentralWidget(centralWidget);
	
	//Load scene
	switch (I_SCENE)
	{
	case 0: Scene0();
		    break;
	case 1: Scene1();
		    break;
	default: Scene0();
		    break;
	}
}

//-----------------------------------------------------------------------------

CAppWidget::~CAppWidget()
{
	delete m_pclPlaneShader;
	delete m_pclSphereShader0;
	delete m_pclSphereShader1;
	delete m_pclSphereShader2;
}

//-----------------------------------------------------------------------------

/*
	Checkerboard plane with metallic spheres
*/
void
CAppWidget::Scene0()
{
	m_clWhittedRaytracer.GetCamera().SetEye( VectorType3(0, 0.5, 2.5) );
//Lights
	CDirectionalLight* pcl_dir_light0 = new CDirectionalLight( VectorType3(1, 1, 2), ColorType(0.5) );
	CDirectionalLight* pcl_dir_light1 = new CDirectionalLight( VectorType3(-1, 1, 1), ColorType(0.5) );
	m_clWhittedRaytracer.AddLight( pcl_dir_light0 );
	m_clWhittedRaytracer.AddLight( pcl_dir_light1 );

//Shader
	//Metal
	m_pclSphereShader0 = new CPhongShader( ColorType(0.035, 0.0325, 0.025), ColorType(0.8), ColorType(0), 1, ColorType(0.5, 0.45, 0.35), ColorType(1), 120 );
	m_pclSphereShader1 = 0;
	//Checkerboard pattern
	m_pclPlaneShader  = new CTextureShader( ColorType(0.1), ColorType(0.25), ColorType(0), 1, VectorType2(1, 1));
	QImage cl_texture(2, 2, QImage::Format_RGB32);
	ColorType col_plane(1, 0.75, 0.33);
	cl_texture.setPixel(0, 0, col_plane.GetPacked());cl_texture.setPixel(1, 0, 0xFFFFFF);
	cl_texture.setPixel(1, 1, col_plane.GetPacked());cl_texture.setPixel(0, 1, 0xFFFFFF);
	m_pclPlaneShader->SetTexture( cl_texture );

	
//Spheres
	CSphere* pcl_sphere = new CSphere( VectorType3(0.272166, 0.272166, 0.544331), 0.166667 );
	pcl_sphere->SetShader(m_pclSphereShader0);
	m_clScene.AddSurface( pcl_sphere );

	pcl_sphere = new CSphere( VectorType3(0.643951, 0.172546, 0), 0.166667 );
	pcl_sphere->SetShader(m_pclSphereShader0);
	m_clScene.AddSurface( pcl_sphere );

	pcl_sphere = new CSphere( VectorType3(0.172546, 0.643951, 0 ), 0.166667 );
	pcl_sphere->SetShader(m_pclSphereShader0);
	m_clScene.AddSurface( pcl_sphere );
	
	pcl_sphere = new CSphere( VectorType3(-0.371785, 0.0996195, 0.544331), 0.166667 );
	pcl_sphere->SetShader(m_pclSphereShader0);
	m_clScene.AddSurface( pcl_sphere );

	pcl_sphere = new CSphere( VectorType3(-0.471405, 0.471405, 0 ), 0.166667 );
	pcl_sphere->SetShader(m_pclSphereShader0);
	m_clScene.AddSurface( pcl_sphere );

	pcl_sphere = new CSphere( VectorType3(-0.643951, -0.172546, 0 ), 0.166667 );
	pcl_sphere->SetShader(m_pclSphereShader0);
	m_clScene.AddSurface( pcl_sphere );

	pcl_sphere = new CSphere( VectorType3(0.0996195, -0.371785, 0.544331 ), 0.166667 );
	pcl_sphere->SetShader(m_pclSphereShader0);
	m_clScene.AddSurface( pcl_sphere );

	pcl_sphere = new CSphere( VectorType3(-0.172546, -0.643951, 0 ), 0.166667 );
	pcl_sphere->SetShader(m_pclSphereShader0);
	m_clScene.AddSurface( pcl_sphere );

	pcl_sphere = new CSphere( VectorType3(0.471405, -0.471405, 0 ), 0.166667 );
	pcl_sphere->SetShader(m_pclSphereShader0);
	m_clScene.AddSurface( pcl_sphere );

	pcl_sphere = new CSphere( VectorType3(0, 0, 0), 0.5 );
	pcl_sphere->SetShader(m_pclSphereShader0);
	m_clScene.AddSurface( pcl_sphere );

//Plane
	CPlane* pcl_plane = new CPlane( VectorType3(0, 1, 0), VectorType3( 0, -0.8, 0) );
	pcl_plane->SetShader( m_pclPlaneShader );
	m_clScene.AddSurface( pcl_plane );
}


//-----------------------------------------------------------------------------

/*
	Checkerboard plane with refractive sphere
*/
void
CAppWidget::Scene1()
{
	m_clWhittedRaytracer.GetCamera().SetEye( VectorType3(0, 0, 4) );
//Lights
	CDirectionalLight* pcl_dir_light0 = new CDirectionalLight( VectorType3(1, 1, 2), ColorType(0.75) );
	m_clWhittedRaytracer.AddLight( pcl_dir_light0 );

// Shader
	//Glass
	m_pclSphereShader2 = new CGlassShader();
	//diffuse red plastic
	m_pclSphereShader1 = new CLambertShader( ColorType(0.35, 0.032, 0.025), ColorType(0.8, 0.05, 0.06) );
	//Checkerboard 
	m_pclPlaneShader  = new CTextureShader( ColorType(0.1), ColorType(0.25), ColorType(0), 1, VectorType2(1, 1));
	QImage cl_texture(2, 2, QImage::Format_RGB32);
	ColorType col_plane(1, 0.75, 0.33);
	cl_texture.setPixel(0, 0, col_plane.GetPacked());cl_texture.setPixel(1, 0, 0xFFFFFF);
	cl_texture.setPixel(1, 1, col_plane.GetPacked());cl_texture.setPixel(0, 1, 0xFFFFFF);
	m_pclPlaneShader->SetTexture( cl_texture );


//Spheres
	CSphere* pcl_sphere = new CSphere( VectorType3(0, 0, 1.2), 0.5);
	pcl_sphere->SetShader(m_pclSphereShader2);
	m_clScene.AddSurface( pcl_sphere );
	
	pcl_sphere = new CSphere( VectorType3(-0.75, 0.5, 0.2), 0.5);
	pcl_sphere->SetShader(m_pclSphereShader1);
	m_clScene.AddSurface( pcl_sphere );

//Plane
	CPlane* pcl_plane = new CPlane( VectorType3(0, 0, 1), VectorType3( 0, 0, -0.5) );
	pcl_plane->SetShader( m_pclPlaneShader );
	m_clScene.AddSurface( pcl_plane );
}


//-----------------------------------------------------------------------------

void
CAppWidget::slotPopupMenu_RenderScene(){
	QProgressDialog cl_qprogress( "Render...", "Cancel", 0, m_clQImage.height(), this);
	cl_qprogress.setMinimumDuration(10);
	m_clWhittedRaytracer.Render( &m_clScene, I_MAX_DEPTH, m_clQImage, &cl_qprogress );
	m_pclLabel->setPixmap(QPixmap::fromImage(m_clQImage));
}


//-----------------------------------------------------------------------------

void
CAppWidget::slotPopupMenu_DifferenceImage(){
	m_pclLabel->setPixmap(QPixmap::fromImage(m_clQImage));
	QImage imRendering = m_pclLabel->pixmap()->toImage();
	QImage imReference = QPixmap(m_referenceImageName).toImage();
	if (imRendering.width() != imReference.width() || imRendering.height() != imReference.height()) {
		QMessageBox msgBox(this);
		msgBox.setText(tr("Reference image and rendering must have the same size!"));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return;
	}
	QImage imDiff(imRendering.size(), imRendering.format());
	for (int x = 0; x < imRendering.width(); x++) {
		for (int y = 0; y < imReference.height(); y++) {
			QRgb ref = imReference.pixel(x, y);
			QRgb ren = imRendering.pixel(x, y);
			imDiff.setPixel(x, y, qRgb(abs(qRed(ref) - qRed(ren)), \
									   abs(qGreen(ref) - qGreen(ren)), \
									   abs(qBlue(ref) - qBlue(ren))));
		}
	}
	m_pclLabelReference->setPixmap(QPixmap::fromImage(imDiff));
}


//-----------------------------------------------------------------------------

void
CAppWidget::slotPopupMenu_ShowReferenceImage(){
	m_pclLabelReference->setPixmap(QPixmap(m_referenceImageName));
}


//-----------------------------------------------------------------------------


void 
CAppWidget::slotPopupMenu_Save(){
	QString s_filename = QFileDialog::getSaveFileName(this,"Save Dialog", QString::Null(), "Bitmap (*.bmp)");
	if (s_filename.isEmpty()) return;
	m_clQImage.save( s_filename, "BMP" );			
	}

//-----------------------------------------------------------------------------

void 
CAppWidget::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::RightButton)
	{
		m_pclPopupMenu->exec(QCursor::pos());
	}
}

//-----------------------------------------------------------------------------

