package com.example.mike.javabenchmark;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;


/**
 * Created by Mike on 4/10/2015.
 */
public class DbManager extends SQLiteOpenHelper {

    private final static String DATABASE_NAME = "bench.dat";
    private final static int DATABASE_VERSION = 1;
    private static SQLiteDatabase mDb = null;

    private DbManager(Context context) {
        // Pass a custom cursor factory so that query text may be logged
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    public static SQLiteDatabase getDatabase(Context context) {
        return mDb == null ? mDb = new DbManager(context).getWritableDatabase() : mDb;
    }


    @Override
    public void onCreate(SQLiteDatabase db) {
        // Not implemented
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Not implemented
    }


}
