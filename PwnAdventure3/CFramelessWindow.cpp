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
#include "stdafx.h"

#include <QGraphicsDropShadowEffect>
#include "CFramelessWindow.hpp"
#include "ui_framelesswindow.h"

CFramelessWindow::CFramelessWindow(QWidget *parent) : QWidget(parent), ui(new Ui::FramelessWindow)
{
	// for dialog
	this->m_dialog = nullptr;
	this->m_isDialog = false;

	// called from close event
	this->closeCallback = nullptr;
	// called from show event
	this->showCallback = nullptr;

	ui->setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
	// append minimize button flag in case of windows,
	// for correct windows native handling of minimize function
#if defined(Q_OS_WIN)
	setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
#endif
	setAttribute(Qt::WA_TranslucentBackground);

	ui->restoreButton->setVisible(false);

	// add window shadow
	if (QSysInfo::productType().toLower() != "windows"
		|| (QSysInfo::productType().toLower() == "windows" && QSysInfo::productVersion().toInt() > 7)) {

		//shadow under window title text
		QGraphicsDropShadowEffect *textShadow = new QGraphicsDropShadowEffect;
		textShadow->setBlurRadius(4.0);
		textShadow->setColor(QColor(0, 0, 0));
		textShadow->setOffset(0.0);
		ui->titleText->setGraphicsEffect(textShadow);

		//window shadow
		QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
		windowShadow->setBlurRadius(9.0);
		windowShadow->setColor(palette().color(QPalette::Highlight));
		windowShadow->setOffset(0.0);
		ui->windowFrame->setGraphicsEffect(windowShadow);
	}

	// watch mouse clicks on icon label and fire own signals
	MouseButtonSignaler signaler;
	signaler.installOn(ui->icon);
	QObject::connect(&signaler, &MouseButtonSignaler::mouseButtonEvent, [this](QWidget*, QMouseEvent * event) {
		if (event->type() == QEvent::MouseButtonPress) {
			QMouseEvent *mouse = static_cast<QMouseEvent*>(event);
			if (mouse->button() == Qt::LeftButton) {
				emit windowIconLeftClicked();
			}
			else if (mouse->button() == Qt::RightButton) {
				emit windowIconRightClicked();
			}
		}
		else if (event->type() == QEvent::MouseButtonDblClick) {
			emit windowIconDblClick();
		}
	});

	QObject::connect(qApp, &QGuiApplication::applicationStateChanged, this, &CFramelessWindow::on_applicationStateChanged);

	//
	ui->maximizeButton->setEnabled(false);
	emit this->on_retranslateUi();
}

void CFramelessWindow::showEvent(QShowEvent *event)
{
	if (this->showCallback)
		this->showCallback(this, event);
}

void CFramelessWindow::closeEvent(QCloseEvent* event)
{
	// user-callback
	if (this->closeCallback)
		this->closeCallback(this, event);

	if (this->m_isDialog)
		return this->m_dialog->reject();
}

void CFramelessWindow::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::WindowStateChange) {
		if (windowState().testFlag(Qt::WindowNoState)) {
			on_restoreButton_clicked();
			event->ignore();
		}
		else if (windowState().testFlag(Qt::WindowMaximized)) {
			on_maximizeButton_clicked();
			event->ignore();
		}
	}
	event->accept();
}

void CFramelessWindow::setContent(QWidget *w)
{
	contentLayout.setMargin(0);
	contentLayout.addWidget(w);
	ui->windowContent->setLayout(&contentLayout);
}

void CFramelessWindow::setVisibleMinimizeButton(bool bVisible)
{
	this->ui->minimizeButton->setVisible(bVisible);
}

void CFramelessWindow::setVisibleMaximizeButton(bool bVisible)
{
	this->ui->maximizeButton->setVisible(bVisible);
}

void CFramelessWindow::setVisibleRestoreButton(bool bVisible)
{
	this->ui->restoreButton->setVisible(bVisible);
}

void CFramelessWindow::setVisibleIcon(bool bVisible)
{
	this->ui->icon->setVisible(bVisible);
}

void CFramelessWindow::setDialog(QDialog *d)
{
	if (!d) return;
	this->m_dialog = d;
	this->m_isDialog = true;
}

void CFramelessWindow::setShowCallback(on_showCallback_t on_showCallback)
{
	this->showCallback = on_showCallback;
}

void CFramelessWindow::setCloseCallback(on_closeCallback_t on_closeCallback)
{
	this->closeCallback = on_closeCallback;
}

QDialog *CFramelessWindow::dialog()
{
	return this->m_dialog;
}

void CFramelessWindow::on_retranslateUi()
{

}

void CFramelessWindow::setWindowTitle(const QString &text)
{
	ui->titleText->setText(text);
}

void CFramelessWindow::setWindowIcon(const QIcon &ico)
{
	ui->icon->setPixmap(ico.pixmap(16, 16));
}

void CFramelessWindow::styleWindow(bool bActive, bool bNoState)
{
	if (bActive) {
		if (bNoState) {
			layout()->setMargin(15);
			ui->windowTitlebar->setStyleSheet("#windowTitlebar{border: 0px none palette(shadow); border-top-left-radius:5px; border-top-right-radius:5px; background-color:palette(shadow); height:20px;}");
			ui->windowFrame->setStyleSheet("#windowFrame{border:1px solid palette(highlight); border-radius:5px 5px 5px 5px; background-color:palette(Window);}");
			QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
			if (oldShadow)
				delete oldShadow;
			/*
			QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
			windowShadow->setBlurRadius(9.0);
			windowShadow->setColor(palette().color(QPalette::Highlight));
			windowShadow->setOffset(0.0);
			ui->windowFrame->setGraphicsEffect(windowShadow); */
			ui->windowFrame->setGraphicsEffect(nullptr);
		}
		else {
			layout()->setMargin(0);
			ui->windowTitlebar->setStyleSheet("#windowTitlebar{border: 0px none palette(shadow); border-top-left-radius:0px; border-top-right-radius:0px; background-color:palette(shadow); height:20px;}");
			ui->windowFrame->setStyleSheet("#windowFrame{border:1px solid palette(dark); border-radius:0px 0px 0px 0px; background-color:palette(Window);}");
			QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
			if (oldShadow)
				delete oldShadow;
			ui->windowFrame->setGraphicsEffect(nullptr);
		} // if (bNoState) else maximize
	}
	else {
		if (bNoState) {
			layout()->setMargin(15);
			ui->windowTitlebar->setStyleSheet("#windowTitlebar{border: 0px none palette(shadow); border-top-left-radius:5px; border-top-right-radius:5px; background-color:palette(dark); height:20px;}");
			ui->windowFrame->setStyleSheet("#windowFrame{border:1px solid #000000; border-radius:5px 5px 5px 5px; background-color:palette(Window);}");
			QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
			if (oldShadow)
				delete oldShadow;
			/*
			QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
			windowShadow->setBlurRadius(9.0);
			windowShadow->setColor(palette().color(QPalette::Shadow));
			windowShadow->setOffset(0.0);
			ui->windowFrame->setGraphicsEffect(windowShadow); */
			ui->windowFrame->setGraphicsEffect(nullptr);
		}
		else {
			layout()->setMargin(0);
			ui->windowTitlebar->setStyleSheet("#titlebarWidget{border: 0px none palette(shadow); border-top-left-radius:0px; border-top-right-radius:0px; background-color:palette(dark); height:20px;}");
			ui->windowFrame->setStyleSheet("#windowFrame{border:1px solid palette(shadow); border-radius:0px 0px 0px 0px; background-color:palette(Window);}");
			QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
			if (oldShadow)
				delete oldShadow;
			ui->windowFrame->setGraphicsEffect(nullptr);
		} // if (bNoState) { else maximize
	} // if (bActive) { else no focus
}

void CFramelessWindow::on_applicationStateChanged(Qt::ApplicationState state)
{
	if (windowState().testFlag(Qt::WindowNoState)) {
		if (state == Qt::ApplicationActive) {
			styleWindow(true, true);
		}
		else {
			styleWindow(false, true);
		}
	}
	else if (windowState().testFlag(Qt::WindowMaximized)) {
		if (state == Qt::ApplicationActive) {
			styleWindow(true, false);
		}
		else {
			styleWindow(false, false);
		}
	}
}

void CFramelessWindow::on_minimizeButton_clicked()
{
	setWindowState(Qt::WindowMinimized);
}

void CFramelessWindow::on_restoreButton_clicked()
{
	layout()->setMargin(15);
	ui->restoreButton->setVisible(false);
	ui->maximizeButton->setVisible(true);
	setWindowState(Qt::WindowNoState);
	styleWindow(true, true);
}
void CFramelessWindow::on_maximizeButton_clicked()
{
	layout()->setMargin(0);
	ui->restoreButton->setVisible(true);
	ui->maximizeButton->setVisible(false);
	setWindowState(Qt::WindowMaximized);
	styleWindow(true, false);
}
void CFramelessWindow::on_closeButton_clicked()
{
	close();
}

void CFramelessWindow::on_windowTitlebar_doubleClicked()
{
	/*
	if (windowState().testFlag(Qt::WindowNoState)) {
	on_maximizeButton_clicked();
	}
	else if (windowState().testFlag(Qt::WindowMaximized)) {
	on_restoreButton_clicked();
	}
	*/
}
