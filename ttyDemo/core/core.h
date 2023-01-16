#ifndef CORE_H
#define CORE_H

#include "core_global.h"
#include <QtCore>

CORE_EXPORT bool IsProcessExist(const QString& appname);
CORE_EXPORT int ProcessCount(const QString& appname);
CORE_EXPORT bool StartProcess(const QString& appname, const QStringList& args);
CORE_EXPORT bool KillProcess(const QString& appname);

#endif // CORE_H
