#include "benchdataio.h"
#include <QDir>


BenchDataIO::BenchDataIO(QObject *parent) :
    QObject(parent),
    mRootKey( "ROOT" )
{
}


RESULT BenchDataIO::Initialize(){

    QDir dir;
    dir.mkpath("data/test");
    QString lPath = QDir::currentPath() + "/data/test/" + "bench.dat";

    RESULT result = benchmark::DataStore::CreateInstance( lPath.toStdString(), &mDataStore );
    if( benchmark::Failed( result )  ){
        qDebug("Unable to create/access datastore at %s", lPath.toStdString().c_str());
    }else{
        qDebug("Successfully accessed datastore at %s", lPath.toStdString().c_str());
    }

    result = mDataStore->Initialize();
    if( benchmark::Failed( result )  ){
        qDebug("Unable to initialize datastore ");
    }else{
        qDebug("Successfully initialized datastore ");
    }

    bool exists = false;
    result = mDataStore->GetKeyExists(mRootKey, exists);
    if( benchmark::Failed( result )  ){
        qDebug("Unable to read datastore ");
    }

    if( !exists )
    {
        result = mDataStore->AddKey( "", mRootKey );
        if( benchmark::Failed( result ) )
        {
            qDebug("Unable to add root key to datastore ");
        }

        result = mDataStore->AddValueUint32( mRootKey, "VERSION", VERSION );
        if( benchmark::Failed( result ) )
        {
            qDebug("Unable to add version info ");
        }
    }

    uint32 lDsVersion = 0;
    result = mDataStore->GetValueUint32( mRootKey, "VERSION", lDsVersion );
    if( benchmark::Failed( result ) )
    {
        qDebug("Unable to read version info ");
    }else{
        qDebug("Datastore version: %d", lDsVersion);
    }


    return RESULT_OK;
}


void BenchDataIO::doWork(){



    uint32 lDsVersion = 0;
    RESULT result = mDataStore->GetValueUint32( mRootKey, "VERSION", lDsVersion );
    if( benchmark::Failed( result ) )
    {
        qDebug("Unable to read version info ");
    }else{
        qDebug("Datastore version: %d", lDsVersion);
    }


    emit workUpdated();

}
