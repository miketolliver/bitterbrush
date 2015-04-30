package com.example.mike.javabenchmark;

import java.io.File;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

import android.app.Activity;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.os.storage.StorageManager;
import android.util.Log;

/**
 * Created by Mike on 4/30/2015.
 */
public class LockableDatabase {

    public static interface DbCallback<T> {
        T doDbWork(SQLiteDatabase db) throws WrappedException; //, UnavailableStorageException;
    }

    public static interface SchemaDefinition {
        int getVersion();
        void doDbUpgrade(SQLiteDatabase db);
    }

    public static class WrappedException extends RuntimeException {
        private static final long serialVersionUID = 8184421232587399369L;
        public WrappedException(final Exception cause) {
            super(cause);
        }
    }

    private String mStorageProviderId;

    private SQLiteDatabase mDb;
    private final String mDbName = "Benchmarkdb";

    private final Lock mReadLock;
    private final Lock mWriteLock;

    {
        final ReadWriteLock lock = new ReentrantReadWriteLock(true);
        mReadLock = lock.readLock();
        mWriteLock = lock.writeLock();
    }

    //private final StorageListener mStorageListener = new StorageListener();
    private Activity mApplication;
    private ThreadLocal<Boolean> inTransaction = new ThreadLocal<Boolean>();
    private SchemaDefinition mSchemaDefinition;
    private String uUid;

    public LockableDatabase(final Activity application, final String uUid, final SchemaDefinition schemaDefinition) {
        this.mApplication = application;
        this.uUid = uUid;
        this.mSchemaDefinition = schemaDefinition;
    }

    public void setStorageProviderId(String mStorageProviderId) {
        this.mStorageProviderId = mStorageProviderId;
    }

    public String getStorageProviderId() {
        return mStorageProviderId;
    }

    protected void lockRead() {
        mReadLock.lock();
    }

    protected void unlockRead() {
        mReadLock.unlock();
    }
    protected void lockWrite() {
        mWriteLock.lock();
    }
    protected void unlockWrite() {
        mWriteLock.unlock();
    }


    public <T> T execute(final boolean transactional, final DbCallback<T> callback) {
        lockRead();
        final boolean doTransaction = transactional && inTransaction.get() == null;
        try {
            final boolean debug = true;
            if (doTransaction) {
                inTransaction.set(Boolean.TRUE);
                mDb.beginTransaction();
            }
            try {
                final T result = callback.doDbWork(mDb);
                if (doTransaction) {
                    mDb.setTransactionSuccessful();
                }
                return result;
            } finally {
                if (doTransaction) {
                    final long begin;
                    if (debug) {
                        begin = System.currentTimeMillis();
                    } else {
                        begin = 0l;
                    }
                    // not doing endTransaction in the same 'finally' block of unlockRead() because endTransaction() may throw an exception
                    mDb.endTransaction();
                    if (debug) {
                        Log.v("DB_LOG", "LockableDatabase: Transaction ended, took " + Long.toString(System.currentTimeMillis() - begin) + "ms / " + new Exception().getStackTrace()[1].toString());
                    }
                }
            }
        } finally {
            if (doTransaction) {
                inTransaction.set(null);
            }
            unlockRead();
        }
    }


    public void open() {
        lockWrite();
        try {
            openOrCreateDataspace(mApplication);
        } finally {
            unlockWrite();
        }
    }

    protected void openOrCreateDataspace(final Activity application) {
        lockWrite();
        try {
            try {
                mDb = application.openOrCreateDatabase(mDbName, Context.MODE_PRIVATE, null);
            } catch (SQLiteException e) {
                // try to gracefully handle DB corruption - see issue 2537
                Log.w("DB_LOG", "Unable to open DB " + mDbName + " - NOT removing file and NOT retrying", e);
            }
            if (mDb.getVersion() != mSchemaDefinition.getVersion()) {
                mSchemaDefinition.doDbUpgrade(mDb);
            }
        } finally {
            unlockWrite();
        }
    }



}
