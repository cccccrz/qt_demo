#include "core.h"

bool IsProcessExist(const QString &appname)
{
#ifdef Q_OS_WIN
    QProcess p;
    p.start("tasklist");
    p.waitForFinished();
    QString app_list = p.readAllStandardOutput();
    return app_list.contains(appname + ".exe", Qt::CaseInsensitive);
#else
    bool rv = false;
    QString sCmd = QString("ps -C '%1' | grep -v PID | wc -l").arg(appname);
    FILE* fp = popen(sCmd.toLatin1().data(), "r");
    if (!fp) return false;

    char cResult[16] = {0};
    char* pResult = NULL;
    pResult  = fgets(cResult, sizeof(cResult), fp);
    if (!pResult) {
        pclose(fp);
        return false;
    }

    if (atoi(cResult) > 1)
        rv = true;
    pclose(fp);
    return rv;
#endif
}

int ProcessCount(const QString &appname)
{
#ifdef Q_OS_WIN
    QProcess p;
    p.start("tasklist");
    p.waitForFinished();
    QString app_list = p.readAllStandardOutput();
    return app_list.count(appname + ".exe", Qt::CaseInsensitive);
#else
    bool rv = false;
    QString sCmd = QString("ps -C '%1' | grep -v PID | wc -l").arg(appname);
    FILE* fp = popen(sCmd.toLatin1().data(), "r");
    if (!fp) return false;

    char cResult[16] = {0};
    char* pResult = NULL;
    pResult  = fgets(cResult, sizeof(cResult), fp);
    if (!pResult) {
        pclose(fp);
        return 0;
    }

    rv = atoi(cResult);

    pclose(fp);
    return rv;
#endif
}

bool StartProcess(const QString &appname, const QStringList &args)
{
#ifdef Q_OS_WIN
    return QProcess::startDetached(QString("\"%1.exe\"").arg(appname), args);
#else
    return QProcess::startDetached(QString("%1/%2").arg(qApp->applicationDirPath().arg(appname)), args);
#endif
}

bool KillProcess(const QString &appname)
{
#ifdef Q_OS_WIN
    return QProcess::startDetached(QString("taskkill /im %1.exe /f").arg(appname));
#else
    QProcess p;
    p.start(QString("ps -ef | grep %1 | grep -v grep | awk '{print $2}'").arg(appname));
    p.waitForFinished();
    int pid = p.readAllStandardOutput().toInt();
    if (pid > 0) {
        return QProcess::startDetached(QString("kill -9 %1").arg(pid));
    } else {
        return QProcess::startDetached(QString(pkill "%1").arg(appname)));
    }
#endif
}
