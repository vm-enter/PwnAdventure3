#pragma once

#include <qscrollarea.h>
#include <qgroupbox.h>

#include "qsingleton.hpp"

class CMainTab : 
	public QScrollArea, 
	public QSingleton<CMainTab>
{
	Q_OBJECT

public:
	explicit CMainTab(QScrollArea *parent = 0);
	
private:
	QGroupBox *CreateHacksGroupBox(QWidget *parent = 0);
};