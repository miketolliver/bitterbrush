#ifndef BENCHDATAIO_H
#define BENCHDATAIO_H

//project includes
#include "Result.h"
#include "datastore/DataStore.h"

//qt includes
#include <QObject>



class BenchDataIO : public QObject
{
    Q_OBJECT
public:
    explicit BenchDataIO(QObject *parent = 0);

    RESULT Initialize();


signals:
    void workUpdated();

public slots:
    void doWork();

private:
    static const uint32 VERSION = 1;
    benchmark::IDataStore* mDataStore;
    std::string mRootKey;


};

#endif // BENCHDATAIO_H
