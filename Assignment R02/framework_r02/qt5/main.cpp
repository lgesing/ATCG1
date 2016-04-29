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

#include <QtWidgets/QApplication>
#include "AppWidget.h"


int main( int argc, char **argv )
{
    QApplication::setColorSpec( QApplication::CustomColor );
	QApplication a( argc, argv );


	CAppWidget *p_widget = new CAppWidget();

	p_widget->setWindowTitle( QString("ATCG I - Exercise 8 - Turner-Whitted-style raytracer") );
	p_widget->resize( 600, 600 );
	p_widget->show();

	a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
