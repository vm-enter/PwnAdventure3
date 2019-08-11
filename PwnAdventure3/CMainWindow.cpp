#include "stdafx.h"

#include "CMainWindow.hpp"
#include "CWndProc.hpp"
#include "CFramelessWindow.hpp"
#include "CDarkStyle.hpp"
#include "CConfigManager.hpp"

#include "CMainTab.hpp"
#include "CBotTab.hpp"

CMainWindow::CMainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
	CConfigManager::getInstance()->Init();

	this->setMinimumSize(400, 300);
	this->setObjectName("mainwindow");
	this->setupMenuBar();
	this->setupStatusBar();
	this->setupTabWidget();

	this->setCentralWidget(this->m_tabWidget);
}

void CMainWindow::OnShowCallback(CFramelessWindow *window, QShowEvent *event)
{
	// load settings
	QSettings settings;

	// window settings
	QVariant size = settings.value("windowsize");
	if (size.isValid())
		window->resize(size.toSize());

	// window pos
	QVariant pos = settings.value("windowpos");
	if (pos.isValid())
		window->move(pos.toPoint());
}

void CMainWindow::OnCloseCallback(CFramelessWindow *window, QCloseEvent *event)
{
	if (QMessageBox::question(window, window->windowTitle(), tr("Are you sure you want to quit?"),
		QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
	{
		QSettings settings;
		settings.setValue("windowsize", window->size());
		settings.setValue("windowpos", window->pos());
		event->accept();

		TerminateProcess(GetCurrentProcess(), 0);
	}
	else
	{
		event->ignore();
	}
}

void CMainWindow::setupApp(QApplication *app)
{
	// style our application with custom dark style
	app->setStyle(new CDarkStyle);

	// install native window proc
	app->installNativeEventFilter(this->m_pWndProc = CWndProc::getInstance());
	this->createMessageHandler();

	// create frameless window (and set windowState or title)
	this->m_titleWnd = new CFramelessWindow();
	this->m_titleWnd->setShowCallback((CFramelessWindow::on_showCallback_t)OnShowCallback);
	this->m_titleWnd->setCloseCallback((CFramelessWindow::on_closeCallback_t)OnCloseCallback);
	this->m_titleWnd->setWindowTitle("PwnNewbie 3");
	this->m_titleWnd->setVisibleMaximizeButton(false);
	//	this->m_titleWnd->setWindowIcon(QIcon(":/Resources/images/icons8-Xbox Filled-50.png"));

	// add the mainwindow to our custom frameless window
	this->m_titleWnd->setContent(this);

	DWORD dwProcessId = GetCurrentProcessId();
	this->m_sBaseTitle = "PwnNewbie 3 | PID : " + QString("%1 (%2)")
		.arg(dwProcessId, 8, 16, QChar('0')).toUpper()
		.arg(dwProcessId);

	this->setWindowTitle(this->m_sBaseTitle);
}

HWND CMainWindow::GetMainWindow()
{
	return (HWND)this->m_titleWnd->winId();
}

void CMainWindow::setupMenuBar()
{
	QMenu *fileMenu = new QMenu(tr("&File"));
	QMenu *editMenu = new QMenu(tr("&Edit"));
	QMenu *helpMenu = new QMenu(tr("&Help"));
	this->menuBar()->addMenu(fileMenu);
	this->menuBar()->addMenu(editMenu);
	this->menuBar()->addMenu(helpMenu);

	// add actions
	fileMenu->addAction(QIcon::fromTheme("file-open", QIcon(":/images/Open Folder-64.png")), tr("&Open"), this, SLOT(OnLoad()), QKeySequence::Open);
	fileMenu->addAction(QIcon::fromTheme("file-save", QIcon(":/images/Save-64.png")), tr("&Save"), this, SLOT(OnSave()), QKeySequence::Save);
	fileMenu->addAction(QIcon::fromTheme("file-saveas", QIcon(":/images/Save as-64.png")), tr("&Save As..."), this, SLOT(OnSaveAs()), QKeySequence::SaveAs);
	fileMenu->addSeparator();
	fileMenu->addAction(QIcon::fromTheme("file-quit", QIcon(":/images/Close Window-64.png")), tr("&Quit"), this, SLOT(close()), Qt::CTRL + Qt::Key_Q);
	helpMenu->addAction(QIcon::fromTheme("help-about", QIcon(":/images/About-64.png")), tr("&About"), this, SLOT(OnAbout()));
	helpMenu->addAction(this->style()->standardIcon(QStyle::SP_TitleBarMenuButton), tr("About &Qt"), qApp, SLOT(aboutQt()));
}

void CMainWindow::setupStatusBar()
{
	this->setStatusBar(new QStatusBar());
}

void CMainWindow::setupTabWidget()
{
	this->m_tabWidget = new QTabWidget();
	this->m_tabWidget->setTabPosition(QTabWidget::TabPosition::North);
	this->m_tabWidget->addTab(CMainTab::getInstance(), "Main");
	this->m_tabWidget->addTab(CBotTab::getInstance(), "Bot");
}

void CMainWindow::createMessageHandler()
{
}

void CMainWindow::show()
{
	this->m_titleWnd->show();
}

bool CMainWindow::close()
{
	return this->m_titleWnd->close();
}

void CMainWindow::setWindowTitle(const QString &title)
{
	this->m_titleWnd->setWindowTitle(title);
}

QString CMainWindow::windowTitle() const
{
	return this->m_titleWnd->windowTitle();
}

void CMainWindow::setStatusMessage(const QString & msg, int timeout)
{
	this->statusBar()->showMessage(msg, timeout);
}

void CMainWindow::OnAbout()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle(tr("About"));
	msgBox.setText(
		"<b>Xxx</b><br>" \
		"<br>" \
		"Special Thanks : <a href='https://icons8.com/#'>icons8</a> for free icons.");
	msgBox.setTextFormat(Qt::RichText);
	msgBox.exec();
}

void CMainWindow::OnLoad()
{
	QSettings settings;
	QString sFileName;

	sFileName = QFileDialog::getOpenFileName(this, QString(), QString::fromStdString(CConfigManager::getInstance()->GetProfilesDirectory()), tr("Profiles (*.xml)"));
	if (sFileName.isEmpty())
	{
		//QMessageBox::warning(this, QString(), tr("Unknown error occurred."), QMessageBox::Ok);
		return;
	}

	QFile file(sFileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(this, QString(), file.errorString(), QMessageBox::Ok);
		return;
	}

	// config
	QXmlStreamReader reader(&file);
	while (!reader.atEnd() && !reader.hasError())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (token == QXmlStreamReader::StartElement)
		{
			if (reader.name() == "settings")
			{
				CConfigManager::getInstance()->ReadFromXml(reader);
				break;
			}
		}
	}

	this->setTitleProfileName(sFileName);
	file.close();
}

void CMainWindow::OnSave()
{
	if (this->m_sXmlFileName.isEmpty())
	{
		// no file exists, try to save as...
		this->OnSaveAs();
		return;
	}

	QFile file(this->m_sXmlFileName);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(this, QString(), file.errorString(), QMessageBox::Ok);
		return;
	}

	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	writer.setAutoFormattingIndent(4);
	writer.writeStartDocument();

	// write elements
	writer.writeStartElement("PwnAdventure3");
	CConfigManager::getInstance()->WriteXmlElement(writer);
	writer.writeEndElement();

	this->setTitleProfileName(this->m_sXmlFileName);
	file.close();

	QMessageBox::information(this, QString(), tr("Done."), QMessageBox::Ok);
}

void CMainWindow::OnSaveAs()
{
	QString sFileName = QFileDialog::getSaveFileName(this, QString(), QString::fromLocal8Bit(CConfigManager::getInstance()->GetProfilesDirectory().c_str()), tr("Xml Files (*.xml)"));
	if (sFileName.isEmpty())
	{
		// QMessageBox::warning(this, QString(), tr("Unknown error occurred."), QMessageBox::Ok);
		return;
	}

	this->m_sXmlFileName = sFileName;
	this->OnSave();
}

void CMainWindow::setTitleProfileName(const QString &text)
{
	// set window title with profile name.
	std::string strFile = text.toStdString();
	int pos = strFile.find_last_of("/") + 1;
	strFile = strFile.substr(pos, strFile.length());

	this->m_sXmlFileName = text;
	this->setWindowTitle(this->m_sBaseTitle + " | Profile: " + QString::fromStdString(strFile));
}