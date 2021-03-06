#ifndef CONFIGHELPER_H
#define CONFIGHELPER_H

#include <QSettings>
#include <QStandardItemModel>
#include <QList>
#include "connection.h"

class ConfigHelper : public QObject
{
    Q_OBJECT

public:
    ConfigHelper(QObject *parent);
    ~ConfigHelper();

    QStandardItemModel *getModel() const;
    void save();

    void importGuiConfigJson(const QString &file);
    Connection* configJsonToConnection(const QString &file);
    //The parent of con will be this ConfigHelper instance
    void addConnection(Connection *con);
    void deleteRow(int row);
    void updateNameAtRow(int row);
    void updateTimeAtRow(int row);
    Connection *connectionAt(int row);
    void latencyTestAtRow(int row);//perform a latency test and update lag in model
    void startAllAutoStart();//start those connections marked as auto-start

    /* some functions used to communicate with SettingsDialog */
    bool isHideWindowOnStartup() const;
    bool isOnlyOneInstance() const;
    void setGeneralSettings(bool hide, bool oneInstance);

public slots:
    void testAllLags();

signals:
    void connected(const QString &name);
    void disconnected(const QString &name);
    void rowStatusChanged(const int row, const bool running);

private:
    bool hideWindowOnStartup;
    bool onlyOneInstace;
    QSettings *settings;
    QStandardItemModel *model;
    QString configFile;

    void appendConnectionToList(Connection *con);
    void readConfiguration();

    static const QString profilePrefix;

    static QString convertToLagString(const int &lag);

private slots:
    void onConnectionStateChanged(bool running);
    void onConnectionPingFinished(const int lag);
};

#endif // CONFIGHELPER_H
