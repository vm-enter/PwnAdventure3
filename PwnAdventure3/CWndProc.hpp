#pragma once

#include <qabstractnativeeventfilter.h>

#include <functional>
#include <map>

#include "qsingleton.hpp"

typedef std::function<int(HWND, WPARAM, LPARAM)> message_handler_t;

class CWndProc : public QAbstractNativeEventFilter, public QSingleton<CWndProc>
{
public:
	CWndProc();
	~CWndProc();

	void add_message_handler(unsigned int message, message_handler_t handler_function);
	void remove_message_handler(unsigned int message);

protected:
	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;

private:
	std::map<unsigned int, message_handler_t> m_handlers;
};