#include "benchdataio.h"


#include <QDir>
#include <time.h>

BenchDataIO::BenchDataIO(QObject *parent) :
    QObject(parent),
    mRootKey( "ROOT" )
{
}


RESULT BenchDataIO::Initialize(){

    QDir dir;
    //dir.mkpath("data/test");
    QString lPath = QDir::currentPath() + "/data/" + "qt4bench.dat";

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
    RESULT result = RESULT_OK;

    /*result = mDataStore->GetValueUint32( mRootKey, "VERSION", lDsVersion );
    if( benchmark::Failed( result ) )
    {
        qDebug("Unable to read version info ");
    }else{
        qDebug("Datastore version: %d", lDsVersion);
    } */


    //number of iterations per task.
    int lLoop = 500;


    clock_t t1 = clock();

    //
    // first, add a bunch of values
    //
    for(int i=0; i<lLoop; ++i){
        char lbuf[64];
        sprintf(lbuf, "VALUE%d", i);
        std::string lValueName = std::string(lbuf);
        std::string lValue = "Just some dummy text. Just some dummy text. ";
        result = mDataStore->AddValueString(mRootKey, lValueName, lValue);
        if( benchmark::Failed(result) ){
            qDebug("Task1 failure. Value name: %s, result: %d", lValueName.c_str(), result);
        }
    }
    clock_t t2 = clock();
    float time1ms = (float)(t2-t1) * (1000.0f/(float)CLOCKS_PER_SEC);
    qDebug("Task1: %f ms\n", time1ms );


    //
    // second, update the values
    //
    for(int i=0; i<lLoop; ++i){
        char lbuf[64];
        sprintf(lbuf, "VALUE%d", i);
        std::string lValueName = std::string(lbuf);

        std::string lValue = "Just some DIFFERENT dummy text... "+lValueName;
        result = mDataStore->SetValueString(mRootKey, lValueName, lValue);
        if( benchmark::Failed(result) ){
            qDebug("Task2 failure, result: %d", result);
        }
    }
    clock_t t3= clock();
    float time2ms = (float)(t3-t2) * (1000.0f/(float)CLOCKS_PER_SEC);
    qDebug("Task2: %f ms\n", time2ms );



    //
    // third, query the values
    //
    std::string lValue;
    for(int i=0; i<lLoop; ++i){
        char lbuf[64];
        sprintf(lbuf, "VALUE%d", i);
        std::string lValueName = std::string(lbuf);
        result = mDataStore->GetValueString(mRootKey, lValueName, lValue);
        if( benchmark::Failed(result) ){
            qDebug("Task3 failure, result: %d", result);
        }
        //qDebug("Query the value of %s, result: %s\n", lValueName.c_str(), lValue.c_str());
    }
    clock_t t4= clock();
    float time3ms = (float)(t4-t3) * (1000.0f/(float)CLOCKS_PER_SEC);
    qDebug("Task3: %f ms\n", time3ms );
    qDebug("Query the value, result: %s\n", lValue.c_str());


    //
    // lastly, remove the values.
    //
    for(int i=0; i<lLoop; ++i){
        char lbuf[64];
        sprintf(lbuf, "VALUE%d", i);
        std::string lValueName = std::string(lbuf);
        result = mDataStore->DeleteValue(mRootKey, lValueName);
        if( benchmark::Failed(result) ){
            qDebug("Task4 failure, result: %d", result);
        }
    }
    clock_t t5= clock();


    float time4ms = (float)(t5-t4) * (1000.0f/(float)CLOCKS_PER_SEC);
    qDebug("Task4: %f ms\n", time4ms );

    emit workUpdated();

}











