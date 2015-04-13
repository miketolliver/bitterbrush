// Standard Includes
#include <map>
#include <sstream>
#include <string>
#include <set>
#include <iostream>
#include <sstream>


#include "datastore/DataStore.h"
#include "datastore/DataStoreSchema.h"
#include "datastore/IDataStore.h"
#include "sqlite/sqlite3.h"

using namespace std;

namespace benchmark
{
class DataStoreImpl : public IDataStore
{
public:

    DataStoreImpl(
            std::string filename );

    virtual RESULT Initialize();

    virtual RESULT StartTransaction();

    virtual RESULT FinishTransaction();

    virtual RESULT AddKey(
            const std::string& parentKey,
            const std::string& key );

    virtual RESULT DeleteKey(
            const std::string& key );

    virtual RESULT DeleteEverythingFromDatastore();

    virtual RESULT AddValueInt8(
            const std::string& key,
            const std::string& valueName,
            const int8         value );

    virtual RESULT AddValueUint8(
            const std::string& key,
            const std::string& valueName,
            const uint8        value );

    virtual RESULT AddValueInt16(
            const std::string& key,
            const std::string& valueName,
            const int16        value );

    virtual RESULT AddValueUint16(
            const std::string& key,
            const std::string& valueName,
            const uint16       value );

    virtual RESULT AddValueInt32(
            const std::string& key,
            const std::string& valueName,
            const int32        value );

    virtual RESULT AddValueUint32(
            const std::string& key,
            const std::string& valueName,
            const uint32       value );

    virtual RESULT AddValueInt64(
            const std::string& key,
            const std::string& valueName,
            const int64        value );

    virtual RESULT AddValueUint64(
            const std::string& key,
            const std::string& valueName,
            const uint64       value );

    virtual RESULT AddValueFloat(
            const std::string& key,
            const std::string& valueName,
            const float        value );

    virtual RESULT AddValueDouble(
            const std::string& key,
            const std::string& valueName,
            const double       value );

    virtual RESULT AddValueBool(
            const std::string& key,
            const std::string& valueName,
            const bool         value );

    virtual RESULT AddValueString(
            const std::string& key,
            const std::string& valueName,
            const std::string& value );

    virtual RESULT AddValueBytes(
            const std::string&   key,
            const std::string&   valueName,
            const uint32         dataSize,
            const unsigned char* value );

    virtual RESULT DeleteValue(
            const std::string& key,
            const std::string& valueName );

    virtual RESULT GetKeyExists(
            const std::string& key,
            bool&              exists );

    virtual RESULT GetValueExists(
            const std::string& key,
            const std::string& valueName,
            bool&              exists );

    virtual RESULT GetKeys(
            const std::string&        key,
            std::vector<std::string>& keys );

    virtual RESULT GetValueNames(
            const std::string&        key,
            std::vector<std::string>& valueNames );

    virtual RESULT GetValueInt8(
            const std::string& key,
            const std::string& valueName,
            int8&              value );

    virtual RESULT GetValueUint8(
            const std::string& key,
            const std::string& valueName,
            uint8&             value );

    virtual RESULT GetValueInt16(
            const std::string& key,
            const std::string& valueName,
            int16&             value );

    virtual RESULT GetValueUint16(
            const std::string& key,
            const std::string& valueName,
            uint16&            value );

    virtual RESULT GetValueInt32(
            const std::string& key,
            const std::string& valueName,
            int32&             value );

    virtual RESULT GetValueUint32(
            const std::string& key,
            const std::string& valueName,
            uint32&            value );

    virtual RESULT GetValueInt64(
            const std::string& key,
            const std::string& valueName,
            int64&             value );

    virtual RESULT GetValueUint64(
            const std::string& key,
            const std::string& valueName,
            uint64&            value );

    virtual RESULT GetValueFloat(
            const std::string& key,
            const std::string& valueName,
            float&             value );

    virtual RESULT GetValueDouble(
            const std::string& key,
            const std::string& valueName,
            double&            value );

    virtual RESULT GetValueBool(
            const std::string& key,
            const std::string& valueName,
            bool&              value );

    virtual RESULT GetValueString(
            const std::string& key,
            const std::string& valueName,
            std::string&       value );

    virtual RESULT GetValueBytes(
            const std::string& key,
            const std::string& valueName,
            uint32&            dataSize,
            unsigned char**    value );

    virtual RESULT GetValueType(
            const std::string&  key,
            const std::string&  valueName,
            NativeDataTypeEnum& valueType,
            std::string&        valueTypeString );

    virtual RESULT CopyValue(
            const std::string& keyFrom,
            const std::string& valueNameFrom,
            const std::string& keyTo );

    virtual RESULT SetValueInt8(
            const std::string& key,
            const std::string& valueName,
            const int8         value );

    virtual RESULT SetValueUint8(
            const std::string& key,
            const std::string& valueName,
            const uint8        value );

    virtual RESULT SetValueInt16(
            const std::string& key,
            const std::string& valueName,
            const int16        value );

    virtual RESULT SetValueUint16(
            const std::string& key,
            const std::string& valueName,
            const uint16       value );

    virtual RESULT SetValueInt32(
            const std::string& key,
            const std::string& valueName,
            const int32        value );

    virtual RESULT SetValueUint32(
            const std::string& key,
            const std::string& valueName,
            const uint32       value );

    virtual RESULT SetValueInt64(
            const std::string& key,
            const std::string& valueName,
            const int64        value );

    virtual RESULT SetValueUint64(
            const std::string& key,
            const std::string& valueName,
            const uint64       value );

    virtual RESULT SetValueFloat(
            const std::string& key,
            const std::string& valueName,
            const float        value );

    virtual RESULT SetValueDouble(
            const std::string& key,
            const std::string& valueName,
            const double       value );

    virtual RESULT SetValueBool(
            const std::string& key,
            const std::string& valueName,
            const bool         value );

    virtual RESULT SetValueString(
            const std::string& key,
            const std::string& valueName,
            const std::string  value );

    virtual RESULT SetValueBytes(
            const std::string&   key,
            const std::string&   valueName,
            const uint32         dataSize,
            const unsigned char* value );

    virtual RESULT ExportKey(
            const std::string& key,
            std::ostream&      stream );

    virtual RESULT ImportKey(
            const std::string& destkey,
            std::istream&      stream );

    virtual RESULT ExportToXml(
            const std::string& key,
            std::string& xml )
    { 
        return ExportToXml( key, 0, xml );
    }

private:

        RESULT ExportToXml(
            const std::string& key,
            uint32 level,
            std::string& xml );

protected:

    ~DataStoreImpl();

private:

    RESULT AddValueHelper(
            std::string          key,
            std::string          valueName,
            std::string          type,
            std::string          value,
            const unsigned char* data = 0,
            uint32               dataSize = 0,
            bool                 create = true );

    RESULT GetValueHelper(
            std::string  key,
            std::string  valueName,
            std::string  type,
            std::string& value );

    RESULT GetBlobValueHelper(
            std::string     key,
            std::string     valueName,
            unsigned char** data,
            uint32&         dataSize );

    bool ValidKeyString(
            std::string str );

    bool ValidParentKeyString(
            std::string str );

    bool        m_initialized;
    std::string m_filename;

    // Database connection
    sqlite3* m_database;

    // Maps
    typedef std::map<std::string, NativeDataTypeEnum> StringToDataTypeMap;
    StringToDataTypeMap m_strToDataTypeMap;
};

//-----------------------------------------------------------------------------
// StartTransaction
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::StartTransaction()
{
// For now, commenting this out because it leaves the window open for
// datastore corruption.  Not being in the MEMORY journal_mode does
// make things slower though.  On a 2x2 with 1280x800 projectors, the
// saving of calibration data took 1 second using MEMORY, and without it
// takes 4 seconds.  But at this time we can't take the chance of this
// corrupting the datastore.
//
//#define DO_MEMORY_JOURNAL_MODE

#ifdef DO_MEMORY_JOURNAL_MODE
    std::stringstream sql;

    sql << "PRAGMA journal_mode=MEMORY;";

    int sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );

    if ( sqlResult != SQLITE_OK )
    {
        return RESULT_OK;
    }
#endif

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// FinishTransaction
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::FinishTransaction()
{
#ifdef DO_MEMORY_JOURNAL_MODE
    std::stringstream sql;

    sql << "PRAGMA journal_mode=DELETE;";

    int sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );

    if ( sqlResult != SQLITE_OK )
    {
        return RESULT_FAIL;
    }
#endif

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// ValidKeyString
//-----------------------------------------------------------------------------
bool DataStoreImpl::ValidKeyString(
        std::string str )
{
    for ( size_t i = 0; i < str.size(); i++ )
    {
        if ( str[i] == '/' || str[i] == '\'' || str[i] == '\"' )
        {
            return false;
        }
    }

    return true;
}

//-----------------------------------------------------------------------------
// ValidParentKeyString
//-----------------------------------------------------------------------------
bool DataStoreImpl::ValidParentKeyString(
        std::string str )
{
    for ( size_t i = 0; i < str.size(); i++ )
    {
        if ( str[i] == '\'' || str[i] == '\"' )
        {
            return false;
        }
    }

    return true;
}

//-----------------------------------------------------------------------------
// AddValueHelper
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueHelper(
        std::string          key,
        std::string          valueName,
        std::string          type,
        std::string          value,
        const unsigned char* data,
        uint32               dataSize,
        bool                 create )
{
    // Upper case the key and value anme
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );
    std::string valueNameUpper;
    utf8::ToUpper( valueName, valueNameUpper );

    // Make sure the key and value name have only valid characters
    if ( !ValidParentKeyString( keyUpper ) )
    {
        std::cout << "DATASTORE Err: validparentkeystring failed.\n"<< std::flush;
        return RESULT_FAIL;
    }
    if ( !ValidKeyString( valueNameUpper ) )
    {
        std::cout << "DATASTORE Err: ValidKeyString failed.\n"<< std::flush;
        return RESULT_FAIL;
    }

    // Check that the parent key exists
    bool exists;
    GetKeyExists( keyUpper, exists );
    if ( !exists )
    {
        std::cout << "DATASTORE Err: GetKeyExists failed.\n"<< std::flush;
        return RESULT_FAIL;
    }

    std::stringstream sql;

    // Insert value into the value table
    if ( !data )
    {
        // A double quote " character can cause problems in SQL.  So
        // we will substitute ' for " in the value string
        std::string value2 = value;

        for ( std::string::size_type i = 0; i < value2.length(); ++i )
        {
            if ( value2.at( i ) == '\"' )
            {
                value2.at( i ) = '\'';
            }
        }

        bool exists;
        GetValueExists( keyUpper, valueNameUpper, exists );

        if ( create )
        {
            if ( exists )
            {
                std::cout << "DATASTORE Err: key already exists failed.\n"<< std::flush;
                return RESULT_FAIL;
            }

            sql << "INSERT INTO value (key_id, value_name, type, text_value) "
            "SELECT keys.id AS key_id, '" << valueNameUpper.c_str() << "' AS value_name, '" <<
            type << "' AS type, \"" << value2 << "\" AS text_value FROM keys WHERE key = '" << keyUpper << "';";
        }
        else // update
        {
            if ( !exists )
            {
                std::cout << "DATASTORE Err: key does not exist failed.\n";
                return RESULT_FAIL;
            }

            // Check that the types match
            IDataStore::NativeDataTypeEnum valueType;
            std::string                    valueTypeString;
            GetValueType( keyUpper, valueNameUpper, valueType, valueTypeString );
            if ( valueTypeString != type )
            {
                std::cout << "DATASTORE Err: type failed.\n"<< std::flush;
                return RESULT_FAIL;
            }

            sql << "UPDATE value SET text_value = \"" << value2 << "\" WHERE value.id IN "
            "(SELECT value.id FROM value, keys WHERE ( keys.id = value.key_id AND keys.key ='"
                << keyUpper << "' AND value_name = '" << valueNameUpper << "' AND type = '" << type << "'));";
        }

        // Insert the new value into the value table
        int sqlResult = sqlite3_exec(
                m_database,
                sql.str().c_str(),
                0,
                0,
                0 );

        if ( sqlResult != SQLITE_OK )
        {
            std::cout << "DATASTORE Err: sqlResult failed: "<< sqlResult << ".\n" << std::flush;
            return RESULT_FAIL;
        }
    }
    else
    {
        if ( create )
        {
            sql << "INSERT INTO value (key_id, value_name, type, blob_value) "
            "SELECT keys.id AS key_id, '" << valueNameUpper.c_str() << "' AS value_name, '" <<
            type << "' AS type, ? AS blob_value FROM keys WHERE key = '" << keyUpper << "';";
        }
        else // update
        {
            // Should never get to this path
            return RESULT_FAIL;
        }

        sqlite3_stmt* insertStatment = 0;

        int sqlResult;
        if ( (sqlResult = sqlite3_prepare_v2( m_database, sql.str().c_str(), -1, &insertStatment, NULL )) != SQLITE_OK )
        {
            return RESULT_FAIL;
        }

        sqlResult = sqlite3_bind_blob( insertStatment, 1, data, dataSize, NULL );

        if ( SQLITE_DONE != sqlite3_step( insertStatment ) )
        {
            return RESULT_FAIL;
        }

        sqlite3_finalize( insertStatment );
    }

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueHelper
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueHelper(
        std::string  key,
        std::string  valueName,
        std::string  type,
        std::string& value )
{
    // Upper case the key and value name
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );
    std::string valueNameUpper;
    utf8::ToUpper( valueName, valueNameUpper );

    // Make sure the key and value name have only valid characters
    if ( !ValidParentKeyString( keyUpper ) )
    {
        return RESULT_FAIL;
    }
    if ( !ValidKeyString( valueNameUpper ) )
    {
        return RESULT_FAIL;
    }

    // Check that the parent key exists
    bool exists;
    GetKeyExists( keyUpper, exists );
    if ( !exists )
    {
        return RESULT_FAIL;
    }

    // Check that the value exists
    GetValueExists( keyUpper, valueNameUpper, exists );
    if ( !exists )
    {
        return RESULT_FAIL;
    }

    // Check that the types match or we're asking for string
    IDataStore::NativeDataTypeEnum valueType;
    std::string                    valueTypeString;
    GetValueType( keyUpper, valueNameUpper, valueType, valueTypeString );
    if ( type != "String" && valueTypeString != type )
    {
        return RESULT_FAIL;
    }

    std::stringstream sql;

    sql << "SELECT text_value FROM keys, value WHERE (keys.id = value.key_id AND keys.key = '" << keyUpper <<
    "' AND value.value_name = '" << valueNameUpper << "');";

    sqlite3_stmt* resultStatment = 0;

    int         sqliteResult;
    const char* tail;

    sqliteResult = sqliteResult = sqlite3_prepare_v2(
            m_database,
            sql.str().c_str(),
            -1,
            &resultStatment,
            &tail );

    if ( sqliteResult != SQLITE_OK )
    {
        return RESULT_FAIL;
    }

    // Get the records
    if ( (sqliteResult = sqlite3_step( resultStatment )) != SQLITE_ROW )
    {
        return RESULT_FAIL;
    }

    value = ( (const char*) sqlite3_column_text( resultStatment, 0 ) );

    sqlite3_finalize( resultStatment );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetBlobValueHelper
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetBlobValueHelper(
        std::string     key,
        std::string     valueName,
        unsigned char** data,
        uint32&         dataSize )
{
    // Upper case the key and value name
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );
    std::string valueNameUpper;
    utf8::ToUpper( valueName, valueNameUpper );

    // Check that the parent key exists
    bool exists;
    GetKeyExists( keyUpper, exists );
    if ( !exists )
    {
        return RESULT_FAIL;
    }

    std::stringstream sql;

    sql << "SELECT blob_value FROM keys, value WHERE (keys.id = value.key_id AND keys.key = '" << keyUpper <<
    "' AND value.value_name = '"
        << valueNameUpper << "');";

    sqlite3_stmt* resultStatment = 0;

    int         sqliteResult;
    const char* tail;

    sqliteResult = sqliteResult = sqlite3_prepare_v2(
            m_database,
            sql.str().c_str(),
            -1,
            &resultStatment,
            &tail );

    if ( sqliteResult != SQLITE_OK )
    {
        return RESULT_FAIL;
    }

    // Get the records
    if ( (sqliteResult = sqlite3_step( resultStatment )) != SQLITE_ROW )
    {
        return RESULT_FAIL;
    }

    const char* tempData = ( (const char*) sqlite3_column_blob( resultStatment, 0 ) );
    dataSize = sqlite3_column_bytes( resultStatment, 0 );

    *data = new unsigned char[dataSize];
    memcpy( *data, tempData, dataSize );

    sqlite3_finalize( resultStatment );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
DataStoreImpl::DataStoreImpl(
        std::string filename ) :
    m_initialized( false ),
    m_filename( filename ),
    m_database( 0 )
{
    // Setup a map to convert between string types and type enum
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Bool" ), IDataStore::Bool ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Int8" ), IDataStore::Int8 ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Uint8" ), IDataStore::Uint8 ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Int16" ), IDataStore::Int16 ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Uint16" ), IDataStore::Uint16 ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Int32" ), IDataStore::Int32 ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Uint32" ), IDataStore::Uint32 ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Int64" ), IDataStore::Int64 ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Uint64" ), IDataStore::Uint64 ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Float" ), IDataStore::Float ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Double" ), IDataStore::Double ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "Bytes" ), IDataStore::Bytes ) );
    m_strToDataTypeMap.insert( StringToDataTypeMap::value_type( std::string( "String" ), IDataStore::String ) );
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
DataStoreImpl::~DataStoreImpl()
{
    if ( m_database )
    {
        stringstream sql;

        sql << "VACUUM;";

        int sqlResult = sqlite3_exec(
                m_database,
                sql.str().c_str(),
                0,
                0,
                0 );

        sqlite3_close( m_database );
    }
}

//-----------------------------------------------------------------------------
// Initialize
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::Initialize()
{
    if ( m_initialized )
    {
        return RESULT_FAIL;
    }

    // Attempt to open existing database
    int sqlResult = sqlite3_open_v2(
            m_filename.c_str(),
            &m_database,
            SQLITE_OPEN_READWRITE,
            NULL );

    // If unable to open database, create database
    if ( sqlResult != SQLITE_OK )
    {
        char* debugError;

        // Create new database file
        sqlResult = sqlite3_open_v2(
                m_filename.c_str(),
                &m_database,
                SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
                NULL );

        if ( sqlResult != SQLITE_OK )
        {
            sqlite3_close( m_database );
            return RESULT_FAIL;
        }

        // Create all tables and initial data
        sqlResult = sqlite3_exec(
                m_database,
                schemaSqlVersion1,
                0,
                0,
                &debugError );

        if ( sqlResult != SQLITE_OK )
        {
            sqlite3_close( m_database );
            return RESULT_FAIL;
        }
    }
    else
    {
        // Check version number. The sqlite_open_v2 function does NOT seem to
        // fail if passed a path to a non database file. So doing this check
        // must fail if the version query fails.

        std::stringstream sql;

        sql << "SELECT version FROM schema_version;";

        sqlite3_stmt* resultStatment = 0;

        int         sqliteResult;
        const char* tail;

        sqliteResult = sqliteResult = sqlite3_prepare_v2(
                m_database,
                sql.str().c_str(),
                -1,
                &resultStatment,
                &tail );

        if ( sqliteResult != SQLITE_OK )
        {
            sqlite3_close( m_database );
            return RESULT_FAIL;
        }

        // Get the records
        if ( (sqliteResult = sqlite3_step( resultStatment )) != SQLITE_ROW )
        {
            sqlite3_close( m_database );
            return RESULT_FAIL;
        }

        int32 version = ( sqlite3_column_int( resultStatment, 0 ) );

        sqlite3_finalize( resultStatment );

        if ( version != 100 )
        {
            sqlite3_close( m_database );
            return RESULT_FAIL;
        }

        // In future versions, check the schema version and perform a
        // database schema upgrade and data conversion if necessarry.
    }

    // Enable foreign key constraint enforcement. This prevents code from
    // accidentally deleting a key, while there are values relating to it.

    stringstream sql;
    sql.str( "" );
    sql << "PRAGMA foreign_keys = TRUE;";

    sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );
    sql.str( "" );
    sql << "PRAGMA synchronous = OFF;";

    sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );

    sql.str( "" );
    sql << "PRAGMA temp_store = MEMORY;";

    sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );

    // Check for corrupted database
    char* debugError;

    // First check our "value" table
    sql.str( "" );
    sql << "Select * FROM value;";

    sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            &debugError );

    if ( sqlResult != SQLITE_OK )
    {
        sqlite3_close( m_database );
        return RESULT_FAIL;
    }

    // Now check our "keys" table
    sql.str( "" );
    sql << "Select * FROM keys;";

    sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            &debugError );

    if ( sqlResult != SQLITE_OK )
    {
        sqlite3_close( m_database );

        return RESULT_FAIL;
    }

    m_initialized = true;

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// AddKey
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddKey(
        const std::string& parentKey,
        const std::string& key )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Upper case the key and parent key
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );
    std::string parentKeyUpper;
    utf8::ToUpper( parentKey, parentKeyUpper );

    // Make sure the parent key and key have only valid characters
    if ( !ValidParentKeyString( parentKeyUpper ) )
    {
        return RESULT_FAIL;
    }
    if ( !ValidKeyString( keyUpper ) )
    {
        return RESULT_FAIL;
    }

    std::stringstream sql;

    if ( parentKey.empty() )
    {
        sql << "INSERT INTO keys (key, parent_id) "
        "SELECT '" << keyUpper.c_str() << "' AS key, 0 AS parent_id;";
    }
    else
    {
        // Check that the parent key exists
        bool exists;
        GetKeyExists( parentKeyUpper, exists );
        if ( !exists )
        {
            return RESULT_FAIL;
        }

        // Remove trailing '/' if it exists so that we don't end up with a double '//'
        if ( parentKeyUpper[parentKeyUpper.size() - 1] == '/' )
        {
            parentKeyUpper = parentKeyUpper.substr( 0, parentKeyUpper.size() - 1 );
        }

        sql << "INSERT INTO keys (key, parent_id) "
        "SELECT '" << parentKeyUpper << "/" << keyUpper.c_str() <<
        "' AS key, keys.id AS parent_id FROM keys WHERE key = '" <<
        parentKeyUpper << "';";
    }

    int sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );

    if ( sqlResult != SQLITE_OK )
    {
        return RESULT_FAIL;
    }

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// DeleteKey
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::DeleteKey(
        const std::string& key )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Upper case the key
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );

    // Make sure the key has only valid characters
    if ( !ValidParentKeyString( keyUpper ) )
    {
        return RESULT_FAIL;
    }

    // Explicit check for blank key name (which would delete the ENTIRE datastore)
    if ( keyUpper.length() == 0 )
    {
        return RESULT_FAIL;
    }

    bool exists;
    GetKeyExists( keyUpper, exists );
    if ( !exists )
    {
        return RESULT_FAIL;
    }

    std::stringstream sql;
    sql <<
    "DELETE FROM value WHERE key_id IN "
    "(SELECT id FROM keys WHERE( substr(key, 1, " << keyUpper.length() << ") = '" << keyUpper << "'));"
    "DELETE FROM keys WHERE( substr(keys.key, 1, " << keyUpper.length() << ") = '" << keyUpper << "');"
    ;

    int sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );

    if ( sqlResult != SQLITE_OK )
    {
        return RESULT_FAIL;
    }

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// DeleteEverythingFromDatastore
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::DeleteEverythingFromDatastore()
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string allKeys;
    allKeys = "";

    std::stringstream sql;
    sql << "delete from value ; delete from keys ;";
    int sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );

    if ( sqlResult != SQLITE_OK )
    {
        return RESULT_FAIL;
    }

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// AddValueInt8
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueInt8(
        const std::string& key,
        const std::string& valueName,
        const int8         value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Using int8 (a char really), would put the wrong string out, so convert to int16
    int16 value16 = value;

    stringstream strInt;
    strInt << value16;
    RESULT result = AddValueHelper( key, valueName, "Int8", strInt.str().c_str() );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueUint8
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueUint8(
        const std::string& key,
        const std::string& valueName,
        const uint8        value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Using uint8 (a uchar really), would put the wrong string out, so convert to uint16
    uint16 value16 = value;

    stringstream strInt;
    strInt << value16;
    RESULT result = AddValueHelper( key, valueName, "Uint8", strInt.str().c_str() );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueInt16
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueInt16(
        const std::string& key,
        const std::string& valueName,
        const int16        value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Int16", strInt.str().c_str() );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueUint16
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueUint16(
        const std::string& key,
        const std::string& valueName,
        const uint16       value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Uint16", strInt.str().c_str() );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueInt32
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueInt32(
        const std::string& key,
        const std::string& valueName,
        const int32        value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Int32", strInt.str().c_str() );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueUint32
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueUint32(
        const std::string& key,
        const std::string& valueName,
        const uint32       value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Uint32", strInt.str().c_str() );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueInt64
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueInt64(
        const std::string& key,
        const std::string& valueName,
        const int64        value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Int64", strInt.str().c_str() );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueUint64
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueUint64(
        const std::string& key,
        const std::string& valueName,
        const uint64       value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Uint64", strInt.str().c_str() );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueFloat
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueFloat(
        const std::string& key,
        const std::string& valueName,
        const float        value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Float", strInt.str().c_str() );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueDouble
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueDouble(
        const std::string& key,
        const std::string& valueName,
        const double       value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Double", strInt.str().c_str() );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueBool
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueBool(
        const std::string& key,
        const std::string& valueName,
        const bool         value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    RESULT result = AddValueHelper( key, valueName, "Bool", value ? "T" : "F" );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueString
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueString(
        const std::string& key,
        const std::string& valueName,
        const std::string& value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    RESULT result = AddValueHelper( key, valueName, "String", value );

    return result;
}

//-----------------------------------------------------------------------------
// AddValueBytes
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::AddValueBytes(
        const std::string&   key,
        const std::string&   valueName,
        const uint32         dataSize,
        const unsigned char* data )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    RESULT result = AddValueHelper( key, valueName, "Bytes", "", (const unsigned char*)data, dataSize );

    return result;
}

//-----------------------------------------------------------------------------
// DeleteValue
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::DeleteValue(
        const std::string& key,
        const std::string& valueName )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Upper case the key and value name
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );
    std::string valueNameUpper;
    utf8::ToUpper( valueName, valueNameUpper );

    // Make sure the parent key and key have only valid characters
    if ( !ValidParentKeyString( keyUpper ) )
    {
        return RESULT_FAIL;
    }
    if ( !ValidKeyString( valueNameUpper ) )
    {
        return RESULT_FAIL;
    }

    std::stringstream sql;

    sqlite3_stmt* resultStatment = 0;

    int sqliteResult;

    sql << "DELETE FROM value WHERE value.key_id IN "
    "(SELECT value.key_id FROM value, keys WHERE ( keys.id = value.key_id AND keys.key ='"
        << keyUpper << "' AND value_name = '" << valueNameUpper << "' ))"
    " AND value.value_name = '" << valueNameUpper << "';";

    sqliteResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );

    if ( sqliteResult )
    {
        return RESULT_FAIL;
    }

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetKeyExists
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetKeyExists(
        const std::string& key,
        bool&              exists )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    exists = false;

    // Upper case the key and value anme
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );

    // Make sure the key has only valid characters
    if ( !ValidParentKeyString( keyUpper ) )
    {
        return RESULT_FAIL;
    }
    std::stringstream sql;

    // Lookup the id of the specified key
    sql << "SELECT id FROM KEYS WHERE (key = '" << keyUpper << "');";

    sqlite3_stmt* resultStatment = 0;

    int         sqliteResult;
    const char* tail;

    sqliteResult = sqliteResult = sqlite3_prepare_v2(
            m_database,
            sql.str().c_str(),
            -1,
            &resultStatment,
            &tail );

    // Key wasn't found
    if ( sqliteResult != SQLITE_OK )
    {
        return RESULT_OK;
    }

    // Get the record
    sqliteResult = sqlite3_step( resultStatment );

    sqlite3_finalize( resultStatment );

    if ( sqliteResult != SQLITE_ROW )
    {
        return RESULT_OK;
    }

    exists = true;

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueExists
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueExists(
        const std::string& key,
        const std::string& valueName,
        bool&              exists )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Upper case the key and value anme
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );
    std::string valueNameUpper;
    utf8::ToUpper( valueName, valueNameUpper );

    // Make sure the parent key and key have only valid characters
    if ( !ValidParentKeyString( keyUpper ) )
    {
        return RESULT_FAIL;
    }
    if ( !ValidKeyString( valueNameUpper ) )
    {
        return RESULT_FAIL;
    }

    // Check that the parent key exists
    GetKeyExists( keyUpper, exists );
    if ( !exists )
    {
        return RESULT_FAIL;
    }

    exists = false;

    std::stringstream sql;

    sqlite3_stmt* resultStatment = 0;

    int         sqliteResult;
    const char* tail;

    sql << "SELECT value.id FROM value, keys WHERE (key_id = keys.id AND keys.key ='"
        << keyUpper << "' AND value_name = '" << valueNameUpper << "' );";

    resultStatment = 0;

    sqliteResult = sqliteResult = sqlite3_prepare_v2(
            m_database,
            sql.str().c_str(),
            -1,
            &resultStatment,
            &tail );

    // value wasn't found
    if ( sqliteResult != SQLITE_OK )
    {
        return RESULT_OK;
    }

    // get the value
    sqliteResult = sqlite3_step( resultStatment );

    sqlite3_finalize( resultStatment );

    if ( sqliteResult != SQLITE_ROW )
    {
        return RESULT_OK;
    }

    exists = true;

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetKeys
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetKeys(
        const std::string&        key,
        std::vector<std::string>& keys )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Upper case the key
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );

    // Make sure the key has only valid characters
    if ( !ValidParentKeyString( keyUpper ) )
    {
        return RESULT_FAIL;
    }
    std::stringstream sql;

    // Lookup the id of the specified key
    if ( key.empty() )
    {
        sql << "SELECT keys.key FROM keys WHERE ( keys.parent_id = 0 );";
    }
    else
    {
        sql << "SELECT keys.key FROM keys, keys as keys2 WHERE ( keys.parent_id = keys2.id AND keys2.key = '" <<
        keyUpper << "');";
    }

    sqlite3_stmt* resultStatment = 0;

    int         sqliteResult;
    const char* tail;

    sqliteResult = sqliteResult = sqlite3_prepare_v2(
            m_database,
            sql.str().c_str(),
            -1,
            &resultStatment,
            &tail );

    // Key wasn't found
    if ( sqliteResult != SQLITE_OK )
    {
        return RESULT_OK;
    }

    // Get the records
    while ( (sqliteResult = sqlite3_step( resultStatment )) == SQLITE_ROW )
    {
        std::string key( (const char*) sqlite3_column_text( resultStatment, 0 ) );

        keys.push_back( key );
    }

    sqlite3_finalize( resultStatment );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueNames
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueNames(
        const std::string&        key,
        std::vector<std::string>& valueNames )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Upper case the key
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );

    // Make sure the key has only valid characters
    if ( !ValidParentKeyString( keyUpper ) )
    {
        return RESULT_FAIL;
    }
    std::stringstream sql;

    sqlite3_stmt* resultStatment = 0;

    int         sqliteResult;
    const char* tail;

    sql << "SELECT value_name FROM keys, value WHERE (key_id = keys.id AND keys.key = '" << keyUpper << "');";

    resultStatment = 0;

    sqliteResult = sqliteResult = sqlite3_prepare_v2(
            m_database,
            sql.str().c_str(),
            -1,
            &resultStatment,
            &tail );

    // value wasn't found
    if ( sqliteResult != SQLITE_OK )
    {
        return RESULT_OK;
    }

    // get the value names
    while ( (sqliteResult = sqlite3_step( resultStatment )) == SQLITE_ROW )
    {
        std::string valueName( (const char*) sqlite3_column_text( resultStatment, 0 ) );
        valueNames.push_back( valueName );
    }

    sqlite3_finalize( resultStatment );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueInt8
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueInt8(
        const std::string& key,
        const std::string& valueName,
        int8&              value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Int8", strValue );
    if ( result )
    {
        return result;
    }

    value = (int8) atoi( strValue.c_str() );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueUint8
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueUint8(
        const std::string& key,
        const std::string& valueName,
        uint8&             value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Uint8", strValue );
    if ( result )
    {
        return result;
    }

    value = (uint8) atoi( strValue.c_str() );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueInt16
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueInt16(
        const std::string& key,
        const std::string& valueName,
        int16&             value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Int16", strValue );
    if ( result )
    {
        return result;
    }

    value = utf8::lexical_cast<int16>( strValue );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueUint16
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueUint16(
        const std::string& key,
        const std::string& valueName,
        uint16&            value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Uint16", strValue );
    if ( result )
    {
        return result;
    }

    value = utf8::lexical_cast<uint16>( strValue );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueInt32
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueInt32(
        const std::string& key,
        const std::string& valueName,
        int32&             value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Int32", strValue );
    if ( result )
    {
        return result;
    }

    value = utf8::lexical_cast<int32>( strValue );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueUint32
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueUint32(
        const std::string& key,
        const std::string& valueName,
        uint32&            value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Uint32", strValue );
    if ( result )
    {
        return result;
    }

    value = utf8::lexical_cast<uint32>( strValue );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueInt64
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueInt64(
        const std::string& key,
        const std::string& valueName,
        int64&             value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Int64", strValue );
    if ( result )
    {
        return result;
    }

    value = utf8::lexical_cast<int64>( strValue );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueUint64
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueUint64(
        const std::string& key,
        const std::string& valueName,
        uint64&            value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Uint64", strValue );
    if ( result )
    {
        return result;
    }

    value = utf8::lexical_cast<uint64>( strValue );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueFloat
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueFloat(
        const std::string& key,
        const std::string& valueName,
        float&             value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Float", strValue );
    if ( result )
    {
        return result;
    }

    value = utf8::lexical_cast<float>( strValue );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueDouble
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueDouble(
        const std::string& key,
        const std::string& valueName,
        double&            value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Double", strValue );
    if ( result )
    {
        return result;
    }

    value = utf8::lexical_cast<double>( strValue );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueBool
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueBool(
        const std::string& key,
        const std::string& valueName,
        bool&              value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "Bool", strValue );
    if ( result )
    {
        return result;
    }

    value = strValue == "T" ? true : false;

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueString
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueString(
        const std::string& key,
        const std::string& valueName,
        std::string&       value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    std::string strValue;
    RESULT      result = GetValueHelper( key, valueName, "String", strValue );
    if ( result )
    {
        return result;
    }

    value = strValue;

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueBytes
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueBytes(
        const std::string& key,
        const std::string& valueName,
        uint32&            dataSize,
        unsigned char**    data )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    RESULT result = GetBlobValueHelper( key, valueName, data, dataSize );
    if ( result )
    {
        return result;
    }

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// GetValueType
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::GetValueType(
        const std::string&  key,
        const std::string&  valueName,
        NativeDataTypeEnum& valueType,
        std::string&        valueTypeString )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Upper case the key and value name
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );
    std::string valueNameUpper;
    utf8::ToUpper( valueName, valueNameUpper );

    // Make sure the key and value name have only valid characters
    if ( !ValidParentKeyString( keyUpper ) )
    {
        return RESULT_FAIL;
    }
    if ( !ValidKeyString( valueNameUpper ) )
    {
        return RESULT_FAIL;
    }

    // Check that the parent key exists
    bool exists;
    GetKeyExists( keyUpper, exists );
    if ( !exists )
    {
        return RESULT_FAIL;
    }

    // Check that the value exists
    GetValueExists( keyUpper, valueNameUpper, exists );
    if ( !exists )
    {
        return RESULT_FAIL;
    }

    std::stringstream sql;

    sql << "SELECT type FROM value, keys WHERE ( value.value_name = '" << valueNameUpper << "' AND "
    "keys.id = value.key_id AND keys.key = '" << keyUpper << "');";

    sqlite3_stmt* resultStatment = 0;

    int         sqliteResult;
    const char* tail;

    sqliteResult = sqliteResult = sqlite3_prepare_v2(
            m_database,
            sql.str().c_str(),
            -1,
            &resultStatment,
            &tail );

    // Key wasn't found
    if ( sqliteResult != SQLITE_OK )
    {
        return RESULT_OK;
    }

    // Get the records
    if ( (sqliteResult = sqlite3_step( resultStatment )) != SQLITE_ROW )
    {
        return RESULT_FAIL;
    }

    valueTypeString = ( (const char*) sqlite3_column_text( resultStatment, 0 ) );

    sqlite3_finalize( resultStatment );

    StringToDataTypeMap::iterator it = m_strToDataTypeMap.find( valueTypeString );
    if ( it == m_strToDataTypeMap.end() )
    {
        return RESULT_FAIL;
    }

    valueType = it->second;

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// CopyValue
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::CopyValue(
        const std::string& keyFrom,
        const std::string& valueNameFrom,
        const std::string& keyTo )
{
    RESULT result = RESULT_OK;

    NativeDataTypeEnum valueType;
    std::string        valueTypeString;

    result = GetValueType( keyFrom, valueNameFrom, valueType, valueTypeString );
    if ( result != RESULT_OK )
    {
        return result;
    }

    if ( valueType == IDataStore::Bytes )
    {
        uint32         dataSize;
        unsigned char* data;

        result = GetValueBytes( keyFrom, valueNameFrom, dataSize, &data );
        if ( result != RESULT_OK )
        {
            return result;
        }

        result = AddValueHelper( keyTo, valueNameFrom, valueTypeString, "", data, dataSize );

        delete[] data;

        if ( result != RESULT_OK )
        {
            return result;
        }
    }
    else
    {
        std::string strValue;

        result = GetValueHelper( keyFrom, valueNameFrom, valueTypeString, strValue );
        if ( result != RESULT_OK )
        {
            return result;
        }

        result = AddValueHelper( keyTo, valueNameFrom, valueTypeString, strValue.c_str() );
        if ( result != RESULT_OK )
        {
            return result;
        }
    }

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// SetValueInt8
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueInt8(
        const std::string& key,
        const std::string& valueName,
        const int8         value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Using int8 (a char really), would put the wrong string out, so convert to int16
    int16 value16 = value;

    stringstream strInt;
    strInt << value16;
    RESULT result = AddValueHelper( key, valueName, "Int8", strInt.str().c_str(), 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueUint8
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueUint8(
        const std::string& key,
        const std::string& valueName,
        const uint8        value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    // Using uint8 (a uchar really), would put the wrong string out, so convert to uint16
    uint16 value16 = value;

    stringstream strInt;
    strInt << value16;
    RESULT result = AddValueHelper( key, valueName, "Uint8", strInt.str().c_str(), 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueInt16
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueInt16(
        const std::string& key,
        const std::string& valueName,
        const int16        value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Int16", strInt.str().c_str(), 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueUint16
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueUint16(
        const std::string& key,
        const std::string& valueName,
        const uint16       value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Uint16", strInt.str().c_str(), 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueInt32
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueInt32(
        const std::string& key,
        const std::string& valueName,
        const int32        value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Int32", strInt.str().c_str(), 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueUint32
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueUint32(
        const std::string& key,
        const std::string& valueName,
        const uint32       value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Uint32", strInt.str().c_str(), 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueInt64
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueInt64(
        const std::string& key,
        const std::string& valueName,
        const int64        value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Int64", strInt.str().c_str(), 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueUint64
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueUint64(
        const std::string& key,
        const std::string& valueName,
        const uint64       value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Uint64", strInt.str().c_str(), 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueFloat
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueFloat(
        const std::string& key,
        const std::string& valueName,
        const float        value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Float", strInt.str().c_str(), 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueDouble
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueDouble(
        const std::string& key,
        const std::string& valueName,
        const double       value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Double", strInt.str().c_str(), 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueBool
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueBool(
        const std::string& key,
        const std::string& valueName,
        const bool         value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    stringstream strInt;
    strInt << value;
    RESULT result = AddValueHelper( key, valueName, "Bool", value ? "T" : "F", 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueString
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueString(
        const std::string& key,
        const std::string& valueName,
        const std::string  value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    RESULT result = AddValueHelper( key, valueName, "String", value, 0, 0, false );

    return result;
}

//-----------------------------------------------------------------------------
// SetValueBytes
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::SetValueBytes(
        const std::string&   key,
        const std::string&   valueName,
        const uint32         dataSize,
        const unsigned char* value )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    RESULT result;

    result = DeleteValue( key, valueName );
    if ( result != RESULT_OK )
    {
        return result;
    }

    result = AddValueBytes( key, valueName, dataSize, value );
    if ( result != RESULT_OK )
    {
        return result;
    }

    return RESULT_OK;
}

string hexString(
        unsigned char* bytes,
        int            n )
{
    char   lookup[] = "0123456789abcdef";
    string s        = "";

    for ( int i = 0; i < n; i++ )
    {
        s += lookup[ bytes[ i ] >> 4 ];
        s += lookup[ bytes[ i ] & 0x0f ];
    }

    return s;
}

//-----------------------------------------------------------------------------
// ExportKey
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::ExportKey(
        const std::string& key,
        std::ostream&      stream )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    if ( key.empty() )
    {
        return RESULT_FAIL;
    }

    // Make sure the key has only valid characters
    if ( !ValidParentKeyString( key ) )
    {
        return RESULT_FAIL;
    }

    // Upper case the key
    std::string keyUpper;
    utf8::ToUpper( key, keyUpper );

    // Query all value record that are ancestors of the input key, and join with keys table
    // to get the actual parent key as well.
    std::stringstream sql;

    sql << "SELECT keys.key, value.type, value.value_name, value.text_value, value.blob_value FROM keys, value "
        << "WHERE ( substr( keys.key, 1, " << keyUpper.length() << " ) = '" << keyUpper <<
    "' AND keys.id = value.key_id);";

    sqlite3_stmt* resultStatment = 0;

    int         sqliteResult;
    const char* tail;

    sqliteResult = sqliteResult = sqlite3_prepare_v2(
            m_database,
            sql.str().c_str(),
            -1,
            &resultStatment,
            &tail );

    if ( sqliteResult != SQLITE_OK )
    {
        return RESULT_OK;
    }

    // Walk each record records
    while ( (sqliteResult = sqlite3_step( resultStatment )) == SQLITE_ROW )
    {
        std::string keyResult( (const char*) sqlite3_column_text( resultStatment, 0 ) );
        std::string valueType( (const char*) sqlite3_column_text( resultStatment, 1 ) );
        std::string valueName( (const char*) sqlite3_column_text( resultStatment, 2 ) );

        // Strip off the base key so that we only write the relative key.
        keyResult = keyResult.substr( key.length() );

        stream << keyResult << "|";
        stream << valueType << "|";
        stream << valueName << "|";

        std::string value;
        if ( valueType != "Bytes" )
        {
            value = ( (const char*) sqlite3_column_text( resultStatment, 3 ) );
            stream << value << "!";
        }
        else
        {
            // Get the binary data
            const char* tempData = ( (const char*) sqlite3_column_blob( resultStatment, 4 ) );
            uint32      dataSize = sqlite3_column_bytes( resultStatment, 4 );

            // Write data size
            stream << dataSize << "|";

            // Write data
            stream.write( tempData, dataSize );

            // Write end of record delimeter
            stream << "!";
        }
    }

    sqlite3_finalize( resultStatment );

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// UniqueKeySet
//
// This is a helper class used to create a unique set of keys.
// When a key is added, the AddKey method is called recursively to ensure
// that all parent keys also exist in the set.
//
//
//-----------------------------------------------------------------------------
class UniqueKeySet : public std::set<std::string>
{
public:

    void AddKey(
            const std::string& key )
    {
        if ( find( key ) != end() )
        {
            // The key exists
            return;
        }
        else
        {
            // The key has a parent, so add the parent
            if ( key.find_last_of( "/" ) != string::npos )
            {
                string subKey = key;
                subKey.erase( subKey.find_last_of( "/" ) );
                AddKey( subKey );
            }

            insert( key );
        }
    }
};

//-----------------------------------------------------------------------------
// ImportKey
//-----------------------------------------------------------------------------
RESULT DataStoreImpl::ImportKey(
        const std::string& destKey,
        std::istream&      stream )
{
    if ( !m_initialized )
    {
        return RESULT_FAIL;
    }

    if ( destKey.empty() )
    {
        return RESULT_FAIL;
    }

    // Make sure the dest key has only valid characters
    if ( !ValidParentKeyString( destKey ) )
    {
        return RESULT_FAIL;
    }

    // Fail if destination key exists
    bool exists;
    GetKeyExists( destKey, exists );
    if ( exists )
    {
        return RESULT_FAIL;
    }

    // Upper case the dest key
    std::string destKeyUpper;
    utf8::ToUpper( destKey, destKeyUpper );

    StartTransaction();

    // Add all keys to the key set, which creates entries for all sub keys
    // and produces a set of all unique keys needed as parents for values.
    // We do this so that we can add all the keys to th ekeys tables first,
    // because the keys need to exist before we can add values to the keys.
    UniqueKeySet keySet;

    std::string key;
    std::string valueType;
    std::string valueName;
    std::string value;

    bool ok = !stream.eof() && !stream.fail() && !stream.bad();
    while ( ok )
    {
        if ( !getline( stream, key, '|' ).good() )
        {
            break;
        }
        getline( stream, valueType, '|' );
        getline( stream, valueName, '|' );

        // If the value type is bytes, then we read the number of bytes to skip.
        // We skip the data plus two delimeters: the leading '|' and a trailing '!'
        if ( valueType == "Bytes" )
        {
            // Read data size
            int dataSize;
            stream >> dataSize;
            stream.seekg( dataSize + 2, ios_base::cur );
        }
        else
        {
            getline( stream, value, '!' );
        }

        // Add the key to the set. This function is recursive, and ensures that
        // all parent sub keys either exist in the set or are added to the set.
        string newKey = destKeyUpper + key;
        keySet.AddKey( newKey );

        ok = !stream.eof() && !stream.fail() && !stream.bad();
    }

    std::stringstream sql;

    sql << "BEGIN;\n";

    UniqueKeySet::const_iterator it = keySet.begin();

    while ( it != keySet.end() )
    {
        string parentKey;
        string newKey = *it;

        if ( newKey.find_last_of( "/" ) != string::npos )
        {
            parentKey = newKey;
            parentKey.erase( parentKey.find_last_of( "/" ) );

            newKey.erase( 0, newKey.find_last_of( "/" ) + 1 );
        }

        if ( parentKey.empty() )
        {
            sql << "INSERT INTO keys (key, parent_id) "
                << "SELECT '" << newKey.c_str()
                << "' AS key, 0 AS parent_id WHERE NOT EXISTS (SELECT id FROM keys WHERE key = '"
                << newKey.c_str() << "');\n";
        }
        else
        {
            sql << "INSERT INTO keys (key, parent_id) "
                << "SELECT '" << parentKey << "/" << newKey.c_str()
                << "' AS key, keys.id AS parent_id FROM keys WHERE key = '"
                << parentKey << "' AND NOT EXISTS (SELECT id FROM keys WHERE key = '"
                <<  parentKey << "/" << newKey.c_str() << "');\n";
        }

        it++;
    }

    // Write keys to the journal
    int sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );

    sql.str( "" );

    if ( sqlResult != SQLITE_OK )
    {
        return RESULT_FAIL;
    }

    // Rewind to beginning of stream
    stream.clear();
    stream.seekg( 0, ios_base::beg );

    std::string textValue;

    // Create SQL to add values
    while ( 1 )
    {
        getline( stream, key, '|' );

        if ( stream.eof() )
        {
            break;
        }

        getline( stream, valueType, '|' );
        getline( stream, valueName, '|' );

        if ( valueType != "Bytes" )
        {
            getline( stream, textValue, '!' );

            sql << "INSERT INTO value (key_id, value_name, type, text_value) "
                << "SELECT keys.id AS key_id, '" << valueName.c_str() << "' AS value_name, '"
                << valueType << "' AS type, \"" << textValue << "\" AS text_value FROM keys WHERE key = '"
                << destKeyUpper << key << "';";

            // Write keys to the journal
            int sqlResult = sqlite3_exec(
                    m_database,
                    sql.str().c_str(),
                    0,
                    0,
                    0 );

            if ( sqlResult != SQLITE_OK )
            {
                return RESULT_FAIL;
            }

            sql.str( "" );
        }
        else
        {
            // Read data size
            int dataSize;
            stream >> dataSize;

            // Seek past the '|' delimeter
            stream.seekg( 1, ios_base::cur );

            // Read data
            char* data = new char[dataSize];
            stream.read( data, dataSize );

            // Seek past the '!' delimeter to the next record
            stream.seekg( 1, ios_base::cur );

            sql << "INSERT INTO value (key_id, value_name, type, blob_value) "
                << "SELECT keys.id AS key_id, '" << valueName.c_str() << "' AS value_name, '"
                << valueType << "' AS type, ?1 AS blob_value FROM keys WHERE key = '" << destKeyUpper << key << "';";

            sqlite3_stmt* insertStatment = 0;

            if ( (sqlResult =
                     sqlite3_prepare_v2( m_database, sql.str().c_str(), -1, &insertStatment, NULL )) != SQLITE_OK )
            {
                return RESULT_FAIL;
            }

            // Bind the actual binary data to the record
            sqlResult = sqlite3_bind_blob( insertStatment, 1, data, dataSize, NULL );

            // Execute the INSERT
            if ( SQLITE_DONE != sqlite3_step( insertStatment ) )
            {
                return RESULT_FAIL;
            }

            sqlite3_finalize( insertStatment );

            delete [] data;

            sql.str( "" );
        }
    }

    sql.str( "" );
    sql << "END;\n";

    sqlResult = sqlite3_exec(
            m_database,
            sql.str().c_str(),
            0,
            0,
            0 );

    if ( sqlResult != SQLITE_OK )
    {
        return RESULT_FAIL;
    }

    FinishTransaction();

    return RESULT_OK;
}

RESULT DataStoreImpl::ExportToXml(
        const std::string& key,
        const uint32 level,
        std::string& xml )
{
    if ( level == 0 )
    {
        xml += "<?xml version=\"1.0\"?>\r\n";
    }

    static std::string indent("    ");
    std::string currentIndent;
    for ( uint32 i=0; i<level; ++i )
    {
        currentIndent += indent;
    }

    bool exists;
    GetKeyExists( key, exists );

    std::string displayKey = "/" + key;
    displayKey = displayKey.substr( displayKey.rfind('/') + 1, string::npos );
    if ( displayKey[0] < 'A' || displayKey[0] > 'Z' )
    {
        displayKey = "N" + displayKey;
    }

    if ( exists )
    {
        xml += currentIndent + "<" + displayKey + ">\r\n";

        std::vector< std::string > valueNames;
        this->GetValueNames( key, valueNames );

        for ( size_t i=0; i<valueNames.size(); ++i )
        {
            std::string displayName = valueNames[i];
            if ( displayName[0] < 'A' || displayName[0] > 'Z' )
            {
                displayName = "N" + displayName;
            }

            xml += currentIndent + indent + "<" + displayName + ">";

            std::string valueString;
            GetValueString( key, valueNames[i], valueString );
            xml += valueString;
            

            xml += currentIndent + indent + "</" + displayName + ">\r\n";
        }

        std::vector< std::string > childKeys;
        this->GetKeys( key, childKeys );

        for ( size_t i=0; i<childKeys.size(); ++i )
        {
            ExportToXml( childKeys[i], level + 1, xml );
        }

        xml += currentIndent + "</" + displayKey + ">\r\n";
    }

    return RESULT_OK;
}

//-----------------------------------------------------------------------------
// CreateInstance
//-----------------------------------------------------------------------------

RESULT DataStore::CreateInstance(
        std::string  filename,
        IDataStore** dataStore )
{
    if ( dataStore == 0 )
    {
        return RESULT_FAIL;
    }

    *dataStore = new DataStoreImpl( filename );

    if ( !( dataStore ) )
    {
        return RESULT_FAIL;
    }

    return RESULT_OK;
}

}
