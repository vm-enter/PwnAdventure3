/*
###############################################################################
#                                                                             #
# The MIT License                                                             #
#                                                                             #
# Copyright (C) 2017 by Juergen Skrotzky (JorgenVikingGod@gmail.com)          #
#               >> https://github.com/Jorgen-VikingGod                        #
#                                                                             #
# Sources: https://github.com/Jorgen-VikingGod/Qt-Frameless-Window-DarkStyle  #
#                                                                             #
###############################################################################
*/

#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QEvent>
#include <QtWidgets>

namespace Ui {
	class FramelessWindow;
}

class MouseButtonSignaler : public QObject
{
	Q_OBJECT

public:
	MouseButtonSignaler(QObject * parent = 0) : QObject(parent) {}
	void installOn(QWidget * widget) { widget->installEventFilter(this); }

protected:
	virtual bool eventFilter(QObject * obj, QEvent * ev) Q_DECL_OVERRIDE
	{
		if ((ev->type() == QEvent::MouseButtonPress
			|| ev->type() == QEvent::MouseButtonRelease
			|| ev->type() == QEvent::MouseButtonDblClick)
			&& obj->isWidgetType()) {
			emit mouseButtonEvent(static_cast<QWidget*>(obj),
				static_cast<QMouseEvent*>(ev));
		}
		return false;
	}
signals:
	void mouseButtonEvent(QWidget *, QMouseEvent *);
};

class CFramelessWindow : public QWidget
{
	Q_OBJECT

public:
	typedef void(*on_showCallback_t)(CFramelessWindow *, QShowEvent *);
	typedef void(*on_closeCallback_t)(CFramelessWindow *, QCloseEvent *);

	explicit CFramelessWindow(QWidget *parent = 0);
	void setContent(QWidget *w);

	void setVisibleMinimizeButton(bool bVisible);
	void setVisibleMaximizeButton(bool bVisible);
	void setVisibleRestoreButton(bool bVisible);
	void setVisibleIcon(bool bVisible);
	void setDialog(QDialog *d);
	void setShowCallback(on_showCallback_t on_showCallback);
	void setCloseCallback(on_closeCallback_t on_closeCallback);
	QDialog *dialog();

private:
	void styleWindow(bool bActive, bool bNoState);

signals:
	void windowIconLeftClicked();
	void windowIconRightClicked();
	void windowIconDblClick();

public slots:
	void setWindowTitle(const QString &text);
	void setWindowIcon(const QIcon &ico);
	void on_retranslateUi();

private slots:
	void on_applicationStateChanged(Qt::ApplicationState state);
	void on_minimizeButton_clicked();
	void on_restoreButton_clicked();
	void on_maximizeButton_clicked();
	void on_closeButton_clicked();
	void on_windowTitlebar_doubleClicked();

protected:
	virtual void showEvent(QShowEvent *event);
	virtual void closeEvent(QCloseEvent* event);
	virtual void changeEvent(QEvent *event);

private:
	Ui::FramelessWindow *ui;
	QDialog *m_dialog;
	bool m_isDialog;

	on_showCallback_t showCallback;
	on_closeCallback_t closeCallback;

protected:
	QHBoxLayout contentLayout;
};

#endif // FRAMELESSWINDOW_H
