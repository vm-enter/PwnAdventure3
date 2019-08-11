#include "stdafx.h"

#include "CBotTab.hpp"
#include "CConfigManager.hpp"

#include "CMsgHandler.hpp"
#include "CAutoHack.hpp"

// extras
#include "Vector3.hpp"

CBotTab::CBotTab(QScrollArea *parent) : QScrollArea(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *hboxLayout1 = new QHBoxLayout;
	hboxLayout1->addWidget(this->CreateGeneralGroupBox());
	hboxLayout1->addWidget(this->CreateTeleportGroupBox());
	mainLayout->addLayout(hboxLayout1);
	mainLayout->setMargin(3);
	mainLayout->addStretch();

	// QScrollArea
	QWidget *innerWidget = new QWidget;
	innerWidget->setLayout(mainLayout);
	this->setWidget(innerWidget);
	this->setWidgetResizable(true);
}

QGroupBox *CBotTab::CreateGeneralGroupBox(QWidget *parent)
{
	CConfigManager *pConfig = CConfigManager::getInstance();
	QCheckBox *chkItemVac = pConfig->CreateCheckBox("Item Vac");
	QCheckBox *chkKamiVac = pConfig->CreateCheckBox("Kami Vac");
	QCheckBox *chkMobVac = pConfig->CreateCheckBox("Mob Vac");
	QLabel *labelMobDistX = new QLabel("X:");
	QLabel *labelMobDistY = new QLabel("Y:");
	QLabel *labelMobDistZ = new QLabel("Z:");
	QSpinBox *valueMobDistX = pConfig->CreateSpinBox("MobDistanceX");
	QSpinBox *valueMobDistY = pConfig->CreateSpinBox("MobDistanceY");
	QSpinBox *valueMobDistZ = pConfig->CreateSpinBox("MobDistanceZ");

	valueMobDistX->setRange(-9999, 9999);
	valueMobDistY->setRange(-9999, 9999);
	valueMobDistZ->setRange(-9999, 9999);

	connect(chkItemVac, &QCheckBox::toggled, [=](bool checked)
	{
		CAutoHack::GetInstance()->ToggleItemVac(checked);
	});
	connect(chkKamiVac, &QCheckBox::toggled, [=](bool checked)
	{
		CAutoHack::GetInstance()->ToggleKamiVac(checked);
	});
	connect(chkMobVac, &QCheckBox::toggled, [=](bool checked)
	{
		CAutoHack::GetInstance()->ToggleMobVac(checked);
	});
	connect(valueMobDistX, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int value)
	{
		CAutoHack::GetInstance()->SetMobDistanceX((float)value);
	});
	connect(valueMobDistY, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int value)
	{
		CAutoHack::GetInstance()->SetMobDistanceY((float)value);
	});
	connect(valueMobDistZ, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int value)
	{
		CAutoHack::GetInstance()->SetMobDistanceZ((float)value);
	});

	QHBoxLayout *hboxLayout1 = new QHBoxLayout;
	QHBoxLayout *hboxLayout2 = new QHBoxLayout;
	QHBoxLayout *hboxLayout3 = new QHBoxLayout;
	QHBoxLayout *hboxLayout4 = new QHBoxLayout;
	hboxLayout1->addWidget(labelMobDistX);
	hboxLayout1->addWidget(valueMobDistX);
	hboxLayout2->addWidget(labelMobDistY);
	hboxLayout2->addWidget(valueMobDistY);
	hboxLayout3->addWidget(labelMobDistZ);
	hboxLayout3->addWidget(valueMobDistZ);
	hboxLayout4->addWidget(chkMobVac);
	hboxLayout4->addWidget(chkKamiVac);

	QVBoxLayout *vboxLayout1 = new QVBoxLayout;
	vboxLayout1->addWidget(chkItemVac);
	vboxLayout1->addLayout(hboxLayout4);
	vboxLayout1->addLayout(hboxLayout1);
	vboxLayout1->addLayout(hboxLayout2);
	vboxLayout1->addLayout(hboxLayout3);

	QGroupBox *groupBox = new QGroupBox("General", parent);
	groupBox->setLayout(vboxLayout1);
	return groupBox;
}

QGroupBox *CBotTab::CreateTeleportGroupBox(QWidget * parent)
{
	CConfigManager *pConfig = CConfigManager::getInstance();
	QPushButton *pushTeleport = new QPushButton("Teleport");
	QPushButton *pushLocate = new QPushButton("Locate");
	QLabel *labelTeleX = new QLabel("X:");
	QLabel *labelTeleY = new QLabel("Y:");
	QLabel *labelTeleZ = new QLabel("Z:");
	this->m_valueTeleX = pConfig->CreateSpinBox("valueTeleX");
	this->m_valueTeleY = pConfig->CreateSpinBox("valueTeleY");
	this->m_valueTeleZ = pConfig->CreateSpinBox("valueTeleZ");

	this->m_valueTeleX->setRange(-999999, 999999);
	this->m_valueTeleY->setRange(-999999, 999999);
	this->m_valueTeleZ->setRange(-999999, 999999);

	QHBoxLayout *hboxLayout1 = new QHBoxLayout;
	QHBoxLayout *hboxLayout2 = new QHBoxLayout;
	QHBoxLayout *hboxLayout3 = new QHBoxLayout;
	hboxLayout1->addWidget(labelTeleX);
	hboxLayout1->addWidget(this->m_valueTeleX);
	hboxLayout2->addWidget(labelTeleY);
	hboxLayout2->addWidget(this->m_valueTeleY);
	hboxLayout3->addWidget(labelTeleZ);
	hboxLayout3->addWidget(this->m_valueTeleZ);

	connect(pushTeleport, &QPushButton::clicked, this, &CBotTab::OnTeleport);
	connect(pushLocate, &QPushButton::clicked, this, &CBotTab::OnLocate);

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(pushTeleport, 0, 0);
	mainLayout->addWidget(pushLocate, 0, 1);
	mainLayout->addWidget(labelTeleX, 1, 0);
	mainLayout->addWidget(this->m_valueTeleX, 1, 1);
	mainLayout->addWidget(labelTeleY, 2, 0);
	mainLayout->addWidget(this->m_valueTeleY, 2, 1);
	mainLayout->addWidget(labelTeleZ, 3, 0);
	mainLayout->addWidget(this->m_valueTeleZ, 3, 1);

	QGroupBox *groupBox = new QGroupBox("Teleport", parent);
	groupBox->setLayout(mainLayout);
	return groupBox;
}

void CBotTab::OnTeleport()
{
	Vector3 vecPos(
		(float)this->m_valueTeleX->value(),
		(float)this->m_valueTeleY->value(),
		(float)this->m_valueTeleZ->value()
	);

	CMsgHandler::GetInstance()->SendMsg(WM_TELEPORT, (WPARAM)&vecPos, NULL);
}

void CBotTab::OnLocate()
{
	Vector3 vecPos;

	CMsgHandler::GetInstance()->SendMsg(WM_GET_USER_POS, NULL, (LPARAM)&vecPos);
	if (vecPos.x != 0
		&& vecPos.y != 0
		&& vecPos.z != 0)
	{
		this->m_valueTeleX->setValue((int)vecPos.x);
		this->m_valueTeleY->setValue((int)vecPos.y);
		this->m_valueTeleZ->setValue((int)vecPos.z);
	}
}