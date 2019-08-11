#pragma once

#include <qmainwindow.h>
#include <qtabwidget.h>

#include "qsingleton.hpp"

class CWndProc;
class CFramelessWindow;

class CMainWindow :
	public QMainWindow,
	public QSingleton<CMainWindow>
{
	Q_OBJECT

public:
	explicit CMainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);

	void setupApp(QApplication *app);
	HWND GetMainWindow();

private:
	void setupMenuBar();
	void setupStatusBar();
	void setupTabWidget();
	void setTitleProfileName(const QString &text);

	void createMessageHandler();

public slots:
	void setStatusMessage(const QString &msg, int timeout = 0);

	// override
	void show();
	bool close();
	void setWindowTitle(const QString &title);
	QString windowTitle() const;

private slots:
	void OnAbout();
	void OnLoad();
	void OnSave();
	void OnSaveAs();

private:
	CFramelessWindow*	m_titleWnd;
	CWndProc*			m_pWndProc;
	QTabWidget*			m_tabWidget;
	QString				m_sXmlFileName;
	QString				m_sBaseTitle;

	static void OnShowCallback(CFramelessWindow *window, QShowEvent *event);
	static void OnCloseCallback(CFramelessWindow *window, QCloseEvent *event);
};