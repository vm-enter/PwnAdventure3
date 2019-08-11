#include "stdafx.h"

#include "CMainTab.hpp"
#include "CConfigManager.hpp"

#include "CMsgHandler.hpp"
#include "CMainHack.hpp"

CMainTab::CMainTab(QScrollArea *parent) : QScrollArea(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *hboxLayout1 = new QHBoxLayout;
	hboxLayout1->addWidget(this->CreateHacksGroupBox());
	mainLayout->addLayout(hboxLayout1);
	mainLayout->setMargin(3);
	mainLayout->addStretch();

	// QScrollArea
	QWidget *innerWidget = new QWidget;
	innerWidget->setLayout(mainLayout);
	this->setWidget(innerWidget);
	this->setWidgetResizable(true);
}

QGroupBox *CMainTab::CreateHacksGroupBox(QWidget * parent)
{
	CConfigManager *pConfig = CConfigManager::getInstance();
	QCheckBox *chkUnlimitedHealth = pConfig->CreateCheckBox("Unlimited Health");
	QCheckBox *chkUnlimitedMana = pConfig->CreateCheckBox("Unlimited Mana");
	QCheckBox *chkUnlimitedItem = pConfig->CreateCheckBox("Unlimited Item");
	QCheckBox *chkIgnoreItemCooldown = pConfig->CreateCheckBox("Ignore Item Cooldown");
	QCheckBox *chkWalkingSpeedHack = pConfig->CreateCheckBox("Walking Speed");
	QCheckBox *chkJumpSpeedHack = pConfig->CreateCheckBox("Jump Speed");

	QSpinBox *valueWalkingSpeed = pConfig->CreateSpinBox("valueWalkingSpeed");
	QSpinBox *valueJumpSpeed = pConfig->CreateSpinBox("valueJumpSpeed");

	QPushButton *pushGetFireBall = new QPushButton("Get Fire Ball");

	valueWalkingSpeed->setRange(0, 9999);
	valueWalkingSpeed->setValue(200);
	valueJumpSpeed->setRange(0, 9999);
	valueJumpSpeed->setValue(420);

	connect(chkUnlimitedHealth, &QCheckBox::toggled, [=](bool checked)
	{
		CMainHack::GetInstance()->ToggleUnlimitedHealth(checked);
	});
	connect(chkUnlimitedMana, &QCheckBox::toggled, [=](bool checked)
	{
		CMainHack::GetInstance()->ToggleUnlimitedMana(checked);
	});
	connect(chkUnlimitedItem, &QCheckBox::toggled, [=](bool checked)
	{
		CMainHack::GetInstance()->ToggleUnlimitedItem(checked);
	});
	connect(chkIgnoreItemCooldown, &QCheckBox::toggled, [=](bool checked)
	{
		CMainHack::GetInstance()->ToggleNoCooldown(checked);
	});
	connect(chkWalkingSpeedHack, &QCheckBox::toggled, [=](bool checked)
	{
		CMainHack::GetInstance()->ToggleWalkingSpeedHack(checked);
	});
	connect(chkJumpSpeedHack, &QCheckBox::toggled, [=](bool checked)
	{
		CMainHack::GetInstance()->ToggleJumpSpeedHack(checked);
	});
	connect(valueWalkingSpeed, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int value)
	{
		CMainHack::GetInstance()->SetWalkingSpeed((float)value);
	});
	connect(valueJumpSpeed, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int value)
	{
		CMainHack::GetInstance()->SetJumpSpeed((float)value);
	});
	connect(pushGetFireBall, &QPushButton::clicked, [=](bool checked)
	{
		CMsgHandler::GetInstance()->PostMsg(WM_GET_FIRE_BALL);
	});

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(chkUnlimitedHealth, 0, 0);
	mainLayout->addWidget(chkUnlimitedMana, 0, 1);
	mainLayout->addWidget(chkUnlimitedItem, 0, 2);
	mainLayout->addWidget(chkIgnoreItemCooldown, 1, 0);

	mainLayout->addWidget(chkWalkingSpeedHack, 2, 0);
	mainLayout->addWidget(valueWalkingSpeed, 2, 1);

	mainLayout->addWidget(chkJumpSpeedHack, 3, 0);
	mainLayout->addWidget(valueJumpSpeed, 3, 1);

	mainLayout->addWidget(pushGetFireBall, 4, 0);

	QGroupBox *groupBox = new QGroupBox("Hacks", parent);
	groupBox->setLayout(mainLayout);
	return groupBox;
}
