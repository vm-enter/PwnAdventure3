#pragma once

#include <qscrollarea.h>
#include <qgroupbox.h>

#include "qsingleton.hpp"

class CBotTab :
	public QScrollArea,
	public QSingleton<CBotTab>
{
	Q_OBJECT

public:
	explicit CBotTab(QScrollArea *parent = 0);

private:
	QGroupBox *CreateGeneralGroupBox(QWidget *parent = 0);
	QGroupBox *CreateTeleportGroupBox(QWidget *parent = 0);

private slots:
	void OnTeleport();
	void OnLocate();

private:
	QSpinBox *m_valueTeleX;
	QSpinBox *m_valueTeleY;
	QSpinBox *m_valueTeleZ;
};