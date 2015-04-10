#pragma once

// Standard Includes
#include <ostream>
#include <string>
#include <vector>

#include <sstream>
#include <algorithm>
#include <cctype>
#include <functional>
#include <locale>


#include "Result.h"

namespace benchmark
{

class ISerialize;

class IDataStore
{
public:

    virtual RESULT Initialize() = 0;

    enum NativeDataTypeEnum
    {
        Int8,
        Uint8,
        Int16,
        Uint16,
        Int32,
        Uint32,
        Int64,
        Uint64,
        Float,
        Double,
        Bool,
        String,
        Bytes
    };


    static const RESULT RESULT_UNABLE_TO_CREATE_STORAGE = RESULT_FAIL_INTERFACE_BASE + 0;
    static const RESULT RESULT_INVALID_KEY              = RESULT_FAIL_INTERFACE_BASE + 1;
    static const RESULT RESULT_INVALID_VALUE_NAME       = RESULT_FAIL_INTERFACE_BASE + 2;
    static const RESULT RESULT_KEY_ALREADY_EXISTS       = RESULT_FAIL_INTERFACE_BASE + 3;
    static const RESULT RESULT_VALUE_ALREADY_EXISTS     = RESULT_FAIL_INTERFACE_BASE + 4;
    static const RESULT RESULT_INVALID_DATABASE_FILE    = RESULT_FAIL_INTERFACE_BASE + 5;
    static const RESULT RESULT_INVALID_KEY_CHARACTERS   = RESULT_FAIL_INTERFACE_BASE + 6;
    static const RESULT RESULT_INVALID_TYPE             = RESULT_FAIL_INTERFACE_BASE + 7;
    static const RESULT RESULT_KEY_NOT_FOUND            = RESULT_FAIL_INTERFACE_BASE + 8;
    static const RESULT RESULT_VALUE_NAME_NOT_FOUND     = RESULT_FAIL_INTERFACE_BASE + 9;

    /**
     * @brief Start a mass of transactions
     *
     * @return RESULT_OK if transaction started correctly
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT StartTransaction() = 0;

    /**
     * @brief Finish a mass of transactions
     *
     * @return RESULT_OK if transaction finished correctly
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT FinishTransaction() = 0;

    /**
     * @brief Creates a key in parentKey
     *
     * @param[in] parentKey This is the key in which the new key will be created.
     *                      It must exist already, or an error will occur.
     * @param[in] key       This is the key that will be created under parentKey.
     *
     * @return RESULT_OK if the key was created successfully
     * @return RESULT_KEY_NOT_FOUND if the parentKey doesn't exist
     * @return RESULT_KEY_ALREADY_EXISTS if the key to create already exists in the parentKey
     * @return RESULT_INVALID_KEY if the key to create is invalid
     * @return RESULT_INVALID_KEY_CHARACTERS if the key name contains invalid characters
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT AddKey(
            const std::string& parentKey,
            const std::string& key ) = 0;

    /**
     * @brief Deletes the key and any keys/values below it
     *
     * @param[in] key The key to be deleted.
     *
     * @return RESULT_OK if the key was deleted successfully OR the key doesn't exist
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_INVALID_KEY_CHARACTERS if the key name contains invalid characters
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT DeleteKey(
            const std::string& key ) = 0;

    /**
     * @brief Deletes ALL the keys and ALL the values from the datastore
     *
     * @return RESULT_OK if the datastore data was deleted successfully
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT DeleteEverythingFromDatastore() = 0;

    /**
     * @brief Adds the valueName and value to the key
     *
     * @param[in] key       This is the key in which the new value will be created.
     *                      It must exist already, or an error will occur.
     * @param[in] valueName This is the valueName that will be created under key.
     * @param[in] value     This is the value the valueName will be created with
     *
     * @return RESULT_OK if the value was added successfully
     * @return RESULT_KEY_NOT_FOUND if the key doesn't exist
     * @return RESULT_VALUE_ALREADY_EXISTS if the valueName to create already exists in the parentKey
     * @return RESULT_INVALID_VALUE_NAME if the valueName has invalid characters
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_INVALID_KEY_CHARACTERS if the key name contains invalid characters
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT AddValueInt8(
            const std::string& key,
            const std::string& valueName,
            const int8         value ) = 0;

    virtual RESULT AddValueUint8(
            const std::string& key,
            const std::string& valueName,
            const uint8        value ) = 0;

    virtual RESULT AddValueInt16(
            const std::string& key,
            const std::string& valueName,
            const int16        value ) = 0;

    virtual RESULT AddValueUint16(
            const std::string& key,
            const std::string& valueName,
            const uint16       value ) = 0;

    virtual RESULT  AddValueInt32(
            const std::string& key,
            const std::string& valueName,
            const int32        value ) = 0;

    virtual RESULT  AddValueUint32(
            const std::string& key,
            const std::string& valueName,
            const uint32       value ) = 0;

    virtual RESULT  AddValueInt64(
            const std::string& key,
            const std::string& valueName,
            const int64        value ) = 0;

    virtual RESULT  AddValueUint64(
            const std::string& key,
            const std::string& valueName,
            const uint64       value ) = 0;

    virtual RESULT  AddValueFloat(
            const std::string& key,
            const std::string& valueName,
            const float        value ) = 0;

    virtual RESULT  AddValueDouble(
            const std::string& key,
            const std::string& valueName,
            const double       value ) = 0;

    virtual RESULT  AddValueBool(
            const std::string& key,
            const std::string& valueName,
            const bool         value ) = 0;

    virtual RESULT  AddValueString(
            const std::string& key,
            const std::string& valueName,
            const std::string& value ) = 0;

    virtual RESULT  AddValueBytes(
            const std::string&   key,
            const std::string&   valueName,
            const uint32         dataSize,
            const unsigned char* data ) = 0;

    /**
     * @brief Deletes a valueName from a key
     *
     * @param[in] key       This is the key from which the value will be deleted.
     * @param[in] valueName This is the valueName that will be deleted from the key
     *
     * @return RESULT_OK if the key was created successfully OR the key/value name doesn't exist
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT  DeleteValue(
            const std::string& key,
            const std::string& valueName ) = 0;

    /**
     * @brief Checks to see if a key exists
     *
     * @param[in]  key    This is the key to look for
     * @param[out] bool   TRUE if the key exists, else FALSE
     *
     * @return RESULT_OK if there were no errors
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT  GetKeyExists(
            const std::string& key,
            bool&              exists ) = 0;

    /**
     * @brief Checks to see if a value exists
     *
     * @param[in]  key        This is the key to look for the value name in
     * @param[in]  valueName  This is the value name to look for
     * @param[out] bool       TRUE if the value name exists, else FALSE
     *
     * @return RESULT_OK if there were no errors
     * @return RESULT_KEY_NOT_FOUND if the key doesn't exist
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT  GetValueExists(
            const std::string& key,
            const std::string& valueName,
            bool&              exists ) = 0;

    /**
     * @brief Returns a vector of keys that exist in the key
     *
     * @param[in]  key    This is the key to look for other keys in
     * @param[out] keys   This is the returned vector of keys
     *
     * @return RESULT_OK if the keys were found and are being returned
     * @return RESULT_KEY_NOT_FOUND if the key doesn't exist
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT  GetKeys(
            const std::string&        key,
            std::vector<std::string>& keys ) = 0;

    /**
     * @brief Returns a vector of value names that exist in the key
     *
     * @param[in]  key    This is the key to look for other keys in
     * @param[out] values This is the returned vector of value names
     *
     * @return RESULT_OK if the valueNames were found and are being returned
     * @return RESULT_KEY_NOT_FOUND if the key doesn't exist
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT  GetValueNames(
            const std::string&        key,
            std::vector<std::string>& valueNames ) = 0;

    /**
     * @brief Returns the value of the valueName in the given key
     *
     * @param[in]  key        This is the key to look for valueName
     * @param[in]  valueName  This is the name of the value to return
     * @param[out] value      This is the returned value for valueName in key
     *
     * @return RESULT_OK if the valueName was found and is being returned
     * @return RESULT_KEY_NOT_FOUND if the key doesn't exist
     * @return RESULT_VALUE_NAME_NOT_FOUND if the valueName doesn't exist at the key
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT  GetValueInt8(
            const std::string& key,
            const std::string& valueName,
            int8&              value ) = 0;

    virtual RESULT  GetValueUint8(
            const std::string& key,
            const std::string& valueName,
            uint8&             value ) = 0;

    virtual RESULT  GetValueInt16(
            const std::string& key,
            const std::string& valueName,
            int16&             value ) = 0;

    virtual RESULT  GetValueUint16(
            const std::string& key,
            const std::string& valueName,
            uint16&            value ) = 0;

    virtual RESULT  GetValueInt32(
            const std::string& key,
            const std::string& valueName,
            int32&             value ) = 0;

    virtual RESULT  GetValueUint32(
            const std::string& key,
            const std::string& valueName,
            uint32&            value ) = 0;

    virtual RESULT  GetValueInt64(
            const std::string& key,
            const std::string& valueName,
            int64&             value ) = 0;

    virtual RESULT  GetValueUint64(
            const std::string& key,
            const std::string& valueName,
            uint64&            value ) = 0;

    virtual RESULT  GetValueFloat(
            const std::string& key,
            const std::string& valueName,
            float&             value ) = 0;

    virtual RESULT  GetValueDouble(
            const std::string& key,
            const std::string& valueName,
            double&            value ) = 0;

    virtual RESULT  GetValueBool(
            const std::string& key,
            const std::string& valueName,
            bool&              value ) = 0;

    virtual RESULT  GetValueString(
            const std::string& key,
            const std::string& valueName,
            std::string&       value ) = 0;

    // use delete [] to handle the data returned
    virtual RESULT  GetValueBytes(
            const std::string& key,
            const std::string& valueName,
            uint32&            dataSize,
            unsigned char**    data ) = 0;

    /**
     * @brief Returns the native data type of the valueName in the given key
     *
     * @param[in]  key        This is the key to look for valueName
     * @param[in]  valueName  This is the name of the value to return
     * @param[out] valueType  This is the returned data type for valueName in key
     *
     * @return RESULT_OK if the valueName data type was found and is being returned
     * @return RESULT_KEY_NOT_FOUND if the key doesn't exist
     * @return RESULT_VALUE_NAME_NOT_FOUND if the valueName doesn't exist at the key
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT  GetValueType(
            const std::string&  key,
            const std::string&  valueName,
            NativeDataTypeEnum& valueType,
            std::string&        valueTypeString ) = 0;

    /**
     * @brief Copies the valueName and its value to the given key
     *
     * @param[in]  keyFrom        This is the key that valueNameFrom should be in
     * @param[in]  valueNameFrom  This is the name of the value to copy
     * @param[in]  keyTo          This is the key that the valueNameFrom will be copied to
     *
     * @return RESULT_OK if value is copied to the key correctly
     * @return RESULT_KEY_NOT_FOUND if either key doesn't exist
     * @return RESULT_VALUE_NAME_NOT_FOUND if the valueName doesn't exist at keyFrom
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT  CopyValue(
            const std::string& keyFrom,
            const std::string& valueNameFrom,
            const std::string& keyTo ) = 0;

    /**
     * @brief Sets the value of the valueName in the given key
     *
     * @param[in]  key        This is the key that valueName should be in
     * @param[in]  valueName  This is the name of the value to set
     * @param[in]  value      This is the new value for valueName in key
     *
     * @return RESULT_OK if valueName was found and set
     * @return RESULT_KEY_NOT_FOUND if the key doesn't exist
     * @return RESULT_VALUE_NAME_NOT_FOUND if the valueName doesn't exist at the key
     * @return RESULT_NOT_INITIALIZED if the interface has not been initialized
     * @return RESULT_FAIL if there was any other kind of error
     */
    virtual RESULT  SetValueInt8(
            const std::string& key,
            const std::string& valueName,
            const int8         value ) = 0;

    virtual RESULT  SetValueUint8(
            const std::string& key,
            const std::string& valueName,
            const uint8        value ) = 0;

    virtual RESULT  SetValueInt16(
            const std::string& key,
            const std::string& valueName,
            const int16        value ) = 0;

    virtual RESULT  SetValueUint16(
            const std::string& key,
            const std::string& valueName,
            const uint16       value ) = 0;

    virtual RESULT  SetValueInt32(
            const std::string& key,
            const std::string& valueName,
            const int32        value ) = 0;

    virtual RESULT  SetValueUint32(
            const std::string& key,
            const std::string& valueName,
            const uint32       value ) = 0;

    virtual RESULT  SetValueInt64(
            const std::string& key,
            const std::string& valueName,
            const int64        value ) = 0;

    virtual RESULT  SetValueUint64(
            const std::string& key,
            const std::string& valueName,
            const uint64       value ) = 0;

    virtual RESULT  SetValueFloat(
            const std::string& key,
            const std::string& valueName,
            const float        value ) = 0;

    virtual RESULT  SetValueDouble(
            const std::string& key,
            const std::string& valueName,
            const double       value ) = 0;

    virtual RESULT  SetValueBool(
            const std::string& key,
            const std::string& valueName,
            const bool         value ) = 0;

    virtual RESULT  SetValueString(
            const std::string& key,
            const std::string& valueName,
            const std::string  value ) = 0;

    virtual RESULT  SetValueBytes(
            const std::string&   key,
            const std::string&   valueName,
            const uint32         dataSize,
            const unsigned char* value ) = 0;

    virtual RESULT  ExportKey(
            const std::string& key,
            std::ostream&      stream ) = 0;

    virtual RESULT  ImportKey(
            const std::string& destkey,
            std::istream&      stream ) = 0;

    virtual RESULT  ExportToXml(
            const std::string& key,
            std::string& cml ) = 0;

protected:

    virtual ~IDataStore()
    {
    }
};


struct utf8
{
    static std::wstring widen(
            const std::string& str );
    static std::string format(
            const char* formatstring,
            ... );
    static std::string replace(
            const std::string& srcStr,
            const std::        string& searchStr,
            const std::        string& replacementStr );

    //
    //Template function to convert any numerical type
    //into a stl string.
    //
    template<typename From>
    static std::string string_cast(
            From value )
    {
        std::ostringstream os;
                           os << value;
        return os.         str();
    }

    //
    //Template function to convert any string that contains
    //a numerical value into its intrinsic value.
    //
    template< typename To >
    static To lexical_cast(
            const std::string& str )
    {
        std::istringstream is( str );
        To                 value;
        is >> value;
        return value;
    }

    static void ToUpper(
            const std::string& in,
            std::string&       out )
    {
        out = in;
        std::transform(
                out.begin(),
                out.end(),
                out.begin(),
                ( int ( * )(  int ) ) std::toupper );
    }

    static uint32 Ipv4ToUint32(
            const std::string& in )
    {
        uint32 out;
        int    octet[4];
        sscanf( in.c_str(), "%d.%d.%d.%d", &octet[0], &octet[1], &octet[2], &octet[3] );
        out = octet[0] << 24 | octet[1] << 16 | octet[2] << 8 | octet[3];
        return out;
    }

    static std::string Uint32ToIpv4String(
            uint32 value )
    {
        unsigned char* octet = (unsigned char*)&value;
        std::ostringstream os;

        uint32 octet3 = octet[3];
        uint32 octet2 = octet[2];
        uint32 octet1 = octet[1];
        uint32 octet0 = octet[0];

        os << octet3 << "." << octet2 << "." << octet1 << "." << octet0;

        return os.str();
    }

    // trim from start
    static inline std::string &ltrim(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
            return s;
    }

    // trim from end
    static inline std::string &rtrim(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
    }

    // trim from both ends
    static inline std::string &trim(std::string &s) {
            return ltrim(rtrim(s));
    }
};

} // namespace
