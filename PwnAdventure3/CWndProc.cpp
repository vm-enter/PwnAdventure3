#include "stdafx.h"

#include "CWndProc.hpp"

CWndProc::CWndProc()
{
}

CWndProc::~CWndProc()
{
}

bool CWndProc::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = static_cast<MSG*>(message);

	if (this->m_handlers[msg->message])
		return this->m_handlers[msg->message](msg->hwnd, msg->wParam, msg->lParam);

	return false;
}

void CWndProc::add_message_handler(unsigned int message, message_handler_t handler_function)
{
	this->m_handlers[message] = handler_function;
}

void CWndProc::remove_message_handler(unsigned int message)
{
	this->m_handlers.erase(message);
}