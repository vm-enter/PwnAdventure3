#pragma once

#include <qwidget.h>
#include <qxmlstream.h>
#include <map>
#include <string>

#include "qsingleton.hpp"

class CConfigManager : public QSingleton<CConfigManager>
{
public:
	CConfigManager();
	virtual ~CConfigManager();

public:
	void Init();
	void ReadFromXml(__in QXmlStreamReader &reader);
	void WriteXmlElement(__in QXmlStreamWriter &writer);

	void SetLoadingConfigStatus(BOOL bStatus);
	BOOL IsLoadingConfig();

	std::string GetAppDataDirectory();
	std::string GetProfilesDirectory();
	std::string GetContentsDirectory();

	// for qwidget
	QCheckBox *CreateCheckBox(__in const QString &name, __in QWidget *parent = 0);
	QSpinBox *CreateSpinBox(__in const QString &name, __in QWidget *parent = 0);
	QDoubleSpinBox *CreateDoubleSpinBox(__in const QString &name, __in QWidget *parent = 0);
	QLineEdit *CreateLineEdit(__in const QString &name, __in QWidget *parent = 0);
	QComboBox *CreateComboBox(__in const QString &name, __in QWidget *parent = 0);
	QPushButton *CreatePushButton(__in const QString &name, __in bool checkable, __in QWidget *parent = 0);
	QRadioButton *CreateRadioButton(__in const QString &name, __in QWidget *parent = 0);
	QRadioButton *CreateRadioButton2(__in const QString &objectName, __in QWidget *parent = 0);
	QSlider *CreateSlider(__in const QString &name, __in QWidget *parent = 0);
	QAction *CreateActionConfig(__in const QString &name, __in QAction *action, __in QWidget *parent = 0);

private:
	BOOL IsDirectoryExists(__in const std::string &name);

	void ReadXmlCheckBox(__in QXmlStreamReader &reader);
	void ReadXmlSpinBox(__in QXmlStreamReader &reader);
	void ReadXmlDoubleSpinBox(__in QXmlStreamReader &reader);
	void ReadXmlLineEdit(__in QXmlStreamReader &reader);
	void ReadXmlComboBox(__in QXmlStreamReader &reader);
	void ReadXmlPushButton(__in QXmlStreamReader &reader);
	void ReadXmlRadioButton(__in QXmlStreamReader &reader);
	void ReadXmlSlider(__in QXmlStreamReader &reader);
	void ReadXmlAction(__in QXmlStreamReader &reader);

private:
	BOOL m_bLoadingConfig;

	std::map<QString, QCheckBox*> m_mCheckBox;
	std::map<QString, QSpinBox*> m_mSpinBox;
	std::map<QString, QDoubleSpinBox*> m_mDoubleSpinBox;
	std::map<QString, QLineEdit*> m_mLineEdit;
	std::map<QString, QComboBox*> m_mComboBox;
	std::map<QString, QPushButton*> m_mPushButton;
	std::map<QString, QRadioButton*> m_mRadioButton;
	std::map<QString, QSlider*> m_mSlider;
	std::map<QString, QAction*> m_mAction;

	std::string m_FDR_APPDATA;
	std::string m_FDR_PROFILES;
	std::string m_FDR_CONTENTS;
	std::string m_sParentPath;
	std::string m_sConfigPath;
};