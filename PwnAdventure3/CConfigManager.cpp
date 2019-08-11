#include "stdafx.h"

#include "CConfigManager.hpp"

#include <direct.h>
#include <qxmlstream.h>

CConfigManager::CConfigManager()
{
	this->m_bLoadingConfig = FALSE;

	this->m_FDR_PROFILES = "profiles";
	this->m_FDR_APPDATA = "appdata";
	this->m_FDR_CONTENTS = "contents";
	this->m_sParentPath = "";
	this->m_sConfigPath = "";
}

CConfigManager::~CConfigManager()
{
}

void CConfigManager::Init()
{
	if (!this->IsDirectoryExists(this->m_FDR_APPDATA))
	{
		_mkdir(this->m_FDR_APPDATA.c_str());
	}

	if (!this->IsDirectoryExists(this->m_FDR_APPDATA + "\\" + this->m_FDR_PROFILES))
	{
		_mkdir((this->m_FDR_APPDATA + "\\" + this->m_FDR_PROFILES).c_str());
	}

	if (!this->IsDirectoryExists(this->m_FDR_APPDATA + "\\" + this->m_FDR_CONTENTS))
	{
		_mkdir((this->m_FDR_APPDATA + "\\" + this->m_FDR_CONTENTS).c_str());
	}
}

void CConfigManager::WriteXmlElement(QXmlStreamWriter &writer)
{
	writer.writeStartElement("settings");

	foreach(auto it, this->m_mCheckBox)
	{
		if (it.second && it.first.size() > 1)
		{
			writer.writeStartElement("checkbox");
			writer.writeTextElement("name", it.first);
			writer.writeTextElement("state", QString::number(it.second->isChecked()));
			writer.writeEndElement();
		}
	}

	foreach(auto it, this->m_mSpinBox)
	{
		if (it.second && it.first.size() > 1)
		{
			writer.writeStartElement("spinbox");
			writer.writeTextElement("name", it.first);
			writer.writeTextElement("val", QString::number(it.second->value()));
			writer.writeEndElement();
		}
	}

	foreach(auto it, this->m_mDoubleSpinBox)
	{
		if (it.second && it.first.size() > 1)
		{
			writer.writeStartElement("doublespinbox");
			writer.writeTextElement("name", it.first);
			writer.writeTextElement("val", QString::number(it.second->value()));
			writer.writeEndElement();
		}
	}

	foreach(auto it, this->m_mComboBox)
	{
		if (it.second && it.first.size() > 1)
		{
			writer.writeStartElement("combobox");
			writer.writeTextElement("name", it.first);
			writer.writeTextElement("index", QString::number(it.second->currentIndex()));
			writer.writeEndElement();
		}
	}

	foreach(auto it, this->m_mLineEdit)
	{
		if (it.second && it.first.size() > 1)
		{
			writer.writeStartElement("lineedit");
			writer.writeTextElement("name", it.first);
			writer.writeTextElement("text", it.second->text());
			writer.writeEndElement();
		}
	}

	foreach(auto it, this->m_mPushButton)
	{
		if (it.second && it.first.size() > 1)
		{
			writer.writeStartElement("pushbutton");
			writer.writeTextElement("name", it.first);
			writer.writeTextElement("state", QString::number(it.second->isChecked()));
			writer.writeEndElement();
		}
	}

	foreach(auto it, this->m_mRadioButton)
	{
		if (it.second && it.first.size() > 1)
		{
			writer.writeStartElement("radiobutton");
			writer.writeTextElement("name", it.first);
			writer.writeTextElement("state", QString::number(it.second->isChecked()));
			writer.writeEndElement();
		}
	}

	foreach(auto it, this->m_mSlider)
	{
		if (it.second && it.first.size() > 1)
		{
			writer.writeStartElement("slider");
			writer.writeTextElement("name", it.first);
			writer.writeTextElement("val", QString::number(it.second->value()));
			writer.writeEndElement();
		}
	}

	foreach(auto it, this->m_mAction)
	{
		if (it.second && it.first.size() > 1)
		{
			writer.writeStartElement("action");
			writer.writeTextElement("name", it.first);
			writer.writeTextElement("isIconVisible", QString::number(it.second->isIconVisibleInMenu()));
			writer.writeEndElement();
		}
	}

	writer.writeEndElement();
}

void CConfigManager::SetLoadingConfigStatus(BOOL bStatus)
{
	this->m_bLoadingConfig = bStatus;
}

BOOL CConfigManager::IsLoadingConfig()
{
	return this->m_bLoadingConfig;
}

std::string CConfigManager::GetAppDataDirectory()
{
	return this->m_FDR_APPDATA;
}

std::string CConfigManager::GetProfilesDirectory()
{
	return this->m_FDR_APPDATA + "\\" + this->m_FDR_PROFILES;
}

std::string CConfigManager::GetContentsDirectory()
{
	return this->m_FDR_APPDATA + "\\" + this->m_FDR_CONTENTS;
}

BOOL CConfigManager::IsDirectoryExists(__in const std::string &name)
{
	DWORD dwFileType = GetFileAttributesA(name.c_str());

	if (dwFileType == INVALID_FILE_ATTRIBUTES)
		return FALSE;

	if (dwFileType & FILE_ATTRIBUTE_DIRECTORY)
		return TRUE;

	return FALSE;
}

void CConfigManager::ReadFromXml(__in QXmlStreamReader &reader)
{
	this->m_bLoadingConfig = TRUE;

	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "settings")
		{
			// element item end
			break;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "checkbox")
				this->ReadXmlCheckBox(reader);
			else if (reader.name() == "spinbox")
				this->ReadXmlSpinBox(reader);
			else if (reader.name() == "doublespinbox")
				this->ReadXmlDoubleSpinBox(reader);
			else if (reader.name() == "lineedit")
				this->ReadXmlLineEdit(reader);
			else if (reader.name() == "combobox")
				this->ReadXmlComboBox(reader);
			else if (reader.name() == "pushbutton")
				this->ReadXmlPushButton(reader);
			else if (reader.name() == "radiobutton")
				this->ReadXmlRadioButton(reader);
			else if (reader.name() == "slider")
				this->ReadXmlSlider(reader);
			else if (reader.name() == "action")
				this->ReadXmlAction(reader);
		}
	}

	this->m_bLoadingConfig = FALSE;
}

void CConfigManager::ReadXmlCheckBox(__in QXmlStreamReader &reader)
{
	QString name = QString();
	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "checkbox")
		{
			// element item end
			break;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "name")
				name = reader.readElementText();
			else if (reader.name() == "state" && name.length() > 1 && this->m_mCheckBox[name])
				this->m_mCheckBox[name]->setChecked(reader.readElementText().toInt());
		}
	}
}

void CConfigManager::ReadXmlSpinBox(__in QXmlStreamReader &reader)
{
	QString name = QString();
	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "spinbox")
		{
			// element item end
			break;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "name")
				name = reader.readElementText();
			else if (reader.name() == "val" && name.length() > 1 && this->m_mSpinBox[name])
				this->m_mSpinBox[name]->setValue(reader.readElementText().toInt());
		}
	}
}

void CConfigManager::ReadXmlDoubleSpinBox(__in QXmlStreamReader &reader)
{
	QString name = QString();
	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "doublespinbox")
		{
			// element item end
			break;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "name")
				name = reader.readElementText();
			else if (reader.name() == "val" && name.length() > 1 && this->m_mSpinBox[name])
				this->m_mDoubleSpinBox[name]->setValue(reader.readElementText().toDouble());
		}
	}
}

void CConfigManager::ReadXmlLineEdit(__in QXmlStreamReader &reader)
{
	QString name = QString();
	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "lineedit")
		{
			// element item end
			break;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "name")
				name = reader.readElementText();
			else if (reader.name() == "text" && name.length() > 1 && this->m_mLineEdit[name])
				this->m_mLineEdit[name]->setText(reader.readElementText());
		}
	}
}

void CConfigManager::ReadXmlComboBox(__in QXmlStreamReader &reader)
{
	QString name = QString();
	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "combobox")
		{
			// element item end
			break;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "name")
				name = reader.readElementText();
			else if (reader.name() == "index" && name.length() > 1 && this->m_mComboBox[name])
				this->m_mComboBox[name]->setCurrentIndex(reader.readElementText().toInt());
		}
	}
}

void CConfigManager::ReadXmlPushButton(__in QXmlStreamReader &reader)
{
	QString name = QString();
	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "pushbutton")
		{
			// element item end
			break;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "name")
				name = reader.readElementText();
			else if (reader.name() == "state" && name.length() > 1 && this->m_mPushButton[name])
				this->m_mPushButton[name]->setChecked(reader.readElementText().toInt());
		}
	}
}

void CConfigManager::ReadXmlRadioButton(__in QXmlStreamReader &reader)
{
	QString name = QString();
	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "radiobutton")
		{
			// element item end
			break;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "name")
				name = reader.readElementText();
			else if (reader.name() == "state" && name.length() > 1 && this->m_mRadioButton[name])
				this->m_mRadioButton[name]->setChecked(reader.readElementText().toInt());
		}
	}
}

void CConfigManager::ReadXmlSlider(__in QXmlStreamReader &reader)
{
	QString name = QString();
	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "slider")
		{
			// element item end
			break;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "name")
				name = reader.readElementText();
			else if (reader.name() == "val" && name.length() > 1 && this->m_mSlider[name])
				this->m_mSlider[name]->setValue(reader.readElementText().toInt());
		}
	}
}

void CConfigManager::ReadXmlAction(__in QXmlStreamReader &reader)
{
	QString name = QString();
	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "action")
		{
			// element item end
			break;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "name")
				name = reader.readElementText();
			else if (reader.name() == "isIconVisible" && name.length() > 1 && this->m_mAction[name])
				this->m_mAction[name]->setIconVisibleInMenu(reader.readElementText().toInt());
		}
	}
}

QCheckBox *CConfigManager::CreateCheckBox(__in const QString &name, __in QWidget *parent)
{
	QCheckBox *checkBox = new QCheckBox(name, parent);
	this->m_mCheckBox[name] = checkBox;
	return checkBox;
}

QSpinBox *CConfigManager::CreateSpinBox(__in const QString &name, __in QWidget *parent)
{
	QSpinBox *spinBox = new QSpinBox(parent);
	this->m_mSpinBox[name] = spinBox;
	return spinBox;
}

QDoubleSpinBox *CConfigManager::CreateDoubleSpinBox(__in const QString &name, __in QWidget *parent)
{
	QDoubleSpinBox *spinBox = new QDoubleSpinBox(parent);
	this->m_mDoubleSpinBox[name] = spinBox;
	return spinBox;
}

QLineEdit *CConfigManager::CreateLineEdit(__in const QString &name, __in QWidget *parent)
{
	QLineEdit *lineEdit = new QLineEdit(parent);
	this->m_mLineEdit[name] = lineEdit;
	return lineEdit;
}

QComboBox *CConfigManager::CreateComboBox(__in const QString &name, __in QWidget *parent)
{
	QComboBox *comboBox = new QComboBox(parent);
	this->m_mComboBox[name] = comboBox;
	return comboBox;
}

QPushButton *CConfigManager::CreatePushButton(__in const QString &name, __in bool checkable, __in QWidget *parent)
{
	QPushButton *pushButton = new QPushButton(name, parent);
	pushButton->setCheckable(checkable);
	this->m_mPushButton[name] = pushButton;
	return pushButton;
}

QRadioButton *CConfigManager::CreateRadioButton(__in const QString &name, __in QWidget *parent)
{
	QRadioButton *radioButton = new QRadioButton(name, parent);
	this->m_mRadioButton[name] = radioButton;
	return radioButton;
}

QRadioButton * CConfigManager::CreateRadioButton2(const QString & objectName, QWidget * parent)
{
	QRadioButton *radioButton = new QRadioButton(parent);
	this->m_mRadioButton[objectName] = radioButton;
	return radioButton;
}

QSlider *CConfigManager::CreateSlider(__in const QString &name, __in QWidget *parent)
{
	QSlider *slider = new QSlider(parent);
	this->m_mSlider[name] = slider;
	return slider;
}

QAction *CConfigManager::CreateActionConfig(__in const QString &name, __in QAction *action, __in QWidget *parent)
{
	this->m_mAction[name] = action;
	return action;
}