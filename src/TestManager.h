#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QObject>
#include <QVariantList>
//#include <thread>
//#include <condition_variable>
//#include <memory>

#include "Utils.h"

class BaseComparator;

class TestManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList resultModel READ resultModel NOTIFY resultModelChanged)

public:
    TestManager();

    Q_INVOKABLE void startTest(const QString& leftPath, const QString& rightPath);
    Q_INVOKABLE void compareFolders(const QString& leftPath, const QString& rightPath);
    Q_INVOKABLE void changeSelectionMethod(int idx);

    QVariantList resultModel() const
    {
        return m_result;
    }
signals:
    void resultModelChanged();

private:
    std::shared_ptr<BaseComparator> m_comporator = nullptr;
    Utils m_utils;
    QString m_leftPath, m_rightPath;
    QVariantList m_result;

//    std::unique_ptr <std::thread> *m_worker = nullptr;
//    std::condition_variable m_flag;
//    bool m_newData = false;
//    std::mutex m_locker;
};

#endif // TESTMANAGER_H
