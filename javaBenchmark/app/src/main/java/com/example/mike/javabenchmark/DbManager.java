package com.example.mike.javabenchmark;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;


/**
 * Created by Mike on 4/10/2015.
 */
public class DbManager extends SQLiteOpenHelper {

    private final static String DATABASE_NAME = "bench.dat";
    private final static int DATABASE_VERSION = 1;
    private final static String SCHEMA_V1 = "CREATE TABLE schema_version (" +
            "    id                  INTEGER         DEFAULT 1 PRIMARY KEY ," +
            "    version             INTEGER," +
            "    CHECK               (id = 1)" +
            ");";
    /*
    private final static String CREATE_KEYS = "CREATE TABLE keys (" +
            "    id                  INTEGER         PRIMARY KEY AUTOINCREMENT," +
            "    parent_id           INTEGER," +
            "    key                 TEXT            UNIQUE NOT NULL" +
            "    );";
    private final static String CREATE_KEY_INDEX = "CREATE INDEX idx_key_name ON keys (key);";
    */
    private final static String CREATE_VALUE = "CREATE TABLE value (" +
            "    id                  INTEGER         PRIMARY KEY AUTOINCREMENT," +
            //"    key_id              INTEGER         NOT NULL," +
            "    value_name          TEXT            NOT NULL," +
            "    type                TEXT            NOT NULL," +
            "    text_value          TEXT," +
            "    blob_value          BLOB," +
            //"    FOREIGN KEY         (key_id)        REFERENCES keys(id)," +
            "    CHECK               (length(text_value) > 0 OR length(blob_value) > 0)" +
           // "    CONSTRAINT uc_id_nameID UNIQUE (key_id, value_name)" +
            "    );";
    private final static String CREATE_VALUE_INDEX = "CREATE INDEX value_name ON value (value_name);";
    private final static String INSERT1 = "INSERT INTO schema_version VALUES (1, 100);";


    private final String mRootKey = "ROOT";


    private static SQLiteDatabase mDb = null;

    public DbManager(Context context) {
        // Pass a custom cursor factory so that query text may be logged
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    /*public static SQLiteDatabase getDatabase(Context context) {
        return mDb == null ? mDb = new DbManager(context).getWritableDatabase() : mDb;
    }*/

    public boolean AddKey(String keyName){

        SQLiteDatabase db=this.getWritableDatabase();
        String sql =  "INSERT INTO keys (key, parent_id) " +
            "SELECT '" + "" + "/" + keyName +
            "' AS key, keys.id AS parent_id FROM keys WHERE key = '';";

        db.execSQL(sql);
        return true;
    }

    public String GetValueString(String valueName){

        String key = mRootKey;
        SQLiteDatabase db=this.getReadableDatabase();


        //String sqlSelect = "SELECT text_value FROM keys, value WHERE (keys.id = value.key_id AND keys.key = ? AND value.value_name = ?);";
        String sqlSelect = "SELECT text_value FROM value WHERE value_name = ?;";

        //Cursor cur = db.rawQuery(sqlSelect, new String[]{key, valueName});
        Cursor cur = db.rawQuery(sqlSelect, new String[]{valueName});
        //Log.d("BENCH_DB", "GET value sql: " + sqlSelect);
        cur.moveToFirst();
        String res = "";
        if( cur.getCount() > 0 ) {
            res = cur.getString(cur.getColumnIndex("text_value"));
            //Log.d("BENCH_DB", "GetValueString for key="+key+", valueName="+valueName+". Result="+res );
        }else{
            //Log.d("BENCH_DB", "GetValueString for key="+key+", valueName="+valueName+" returned 0 results." );
        }

        return res;
    }

    public boolean AddValueString(String valueName, String value)
    {
        String key = mRootKey;
        SQLiteDatabase db=this.getWritableDatabase();
        String sql = "INSERT INTO value (value_name, type, text_value) "+
            "VALUES ('" + valueName + "', 'String', '" + value + "');";

        /*String sql = "INSERT INTO value (key_id, value_name, type, text_value) "+
            "SELECT keys.id AS key_id, '" + valueName + "' AS value_name, '" +
            "String" + "' AS type, '" + value + "' AS text_value FROM keys WHERE key = '" + key + "';";
            */

        //Log.d("BENCH_DB", "Add value sql: " + sql);

        db.execSQL(sql);
        return true;
    }

    public boolean SetValueString(String valueName, String value){
        String key = mRootKey;
        SQLiteDatabase db=this.getWritableDatabase();

        /*String sql = "UPDATE value SET text_value = '" + value + "' WHERE value.id IN " +
        "(SELECT value.id FROM value, keys WHERE ( keys.id = value.key_id AND keys.key ='" +
        key + "' AND value_name = '" + valueName + "' AND type = '" + "String" + "'));"; */

        String sql = "UPDATE value SET text_value = '" + value + "' WHERE value_name = '"+ valueName+"'";
        //Log.d("BENCH_DB", "Set value sql: " + sql);
        db.execSQL(sql);

        return true;
    }

    public boolean DeleteValue(String valueName){

        String key = mRootKey;
        SQLiteDatabase db=this.getWritableDatabase();

        /*String sql = "DELETE FROM value WHERE value.key_id IN " +
        "(SELECT value.key_id FROM value, keys WHERE ( keys.id = value.key_id AND keys.key ='" +
        key + "' AND value_name = '" + valueName + "' ))" +
        " AND value.value_name = '" + valueName + "';"; */

        String sql = "DELETE FROM value WHERE value_name = '"+valueName +"';";
        //Log.d("BENCH_DB", "Delete value sql: " + sql);
        db.execSQL(sql);

        return true;
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        Log.d("BENCH_DB", "Creating database");
        db.execSQL(SCHEMA_V1);
        Log.d("BENCH_DB", "Create: " + SCHEMA_V1);
        //db.execSQL(CREATE_KEYS);
        //Log.d("BENCH_DB", "Create: " + CREATE_KEYS);
        //db.execSQL(CREATE_KEY_INDEX);
        //Log.d("BENCH_DB", "Create: " + CREATE_KEY_INDEX);
        db.execSQL(CREATE_VALUE);
        Log.d("BENCH_DB", "Create: " + CREATE_VALUE);
        db.execSQL(CREATE_VALUE_INDEX);
        Log.d("BENCH_DB", "Create: " + CREATE_VALUE_INDEX);
        db.execSQL(INSERT1);
        Log.d("BENCH_DB", "Create: " + INSERT1);

        //Log.d("BENCH_DB", "Adding root key");
        //String sql =  "INSERT INTO keys (key, parent_id) SELECT '"+ mRootKey +"' AS key, keys.id AS parent_id FROM keys WHERE key = '';";

        //db.execSQL(sql);
        //Log.d("BENCH_DB", "Add root: " + sql);


        Log.d("BENCH_DB", "Finished onCreate");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Not implemented
    }


}
