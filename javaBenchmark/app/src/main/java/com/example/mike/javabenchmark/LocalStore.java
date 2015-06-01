package com.example.mike.javabenchmark;

import android.app.Activity;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.util.Log;

import com.example.mike.javabenchmark.LockableDatabase.DbCallback;
import com.example.mike.javabenchmark.LockableDatabase.WrappedException;
import com.example.mike.javabenchmark.LockableDatabase.SchemaDefinition;

import java.io.File;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.UUID;


/**
 * Created by Mike
 */
public class LocalStore { // implements Serializable {


    /*
     * a String containing the columns getMessages expects to work with
     * in the correct order.
     */
    static private String GET_MESSAGES_COLS =
            "subject, sender_list, date, uid, flags, messages.id, to_list, cc_list, " +
                    "bcc_list, reply_to_list, attachment_count, internal_date, messages.message_id, " +
                    "folder_id, text_content, preview, threads.id, threads.root, deleted, read, flagged, answered, " +
                    "forwarded, stored_date, burn_expire_time, public_key_algorithm, signature_verified ";
    static private String GET_FOLDER_COLS = "folders.id, name, SUM(read=0), visible_limit, last_updated, status, push_state, last_pushed, SUM(flagged), integrate, top_group, poll_class, push_class, display_class";
    private static final String[] UID_CHECK_PROJECTION = { "uid" };
    private static final int UID_CHECK_BATCH_SIZE = 500;
    private static final int FLAG_UPDATE_BATCH_SIZE = 500;
    private static final int THREAD_FLAG_UPDATE_BATCH_SIZE = 500;
    public static final int DB_VERSION = 59;
    protected String uUid = null;
    private final Activity mApplication;
    private LockableDatabase database;
    private ContentResolver mContentResolver;

    private static final Message[] EMPTY_MESSAGE_ARRAY = new Message[0];
    private static final String[] EMPTY_STRING_ARRAY = new String[0];
    private static final Flag[] EMPTY_FLAG_ARRAY = new Flag[0];


    public LocalStore(final Activity application) throws MessagingException {
        database = new LockableDatabase(application, "fakeUUID", new StoreSchemaDefinition());

        mApplication = application;
        mContentResolver = application.getContentResolver();
        database.setStorageProviderId("defaultprovider");
        //uUid = account.getUuid();

        Log.d("BENCH", "LocalStore created, opening database.");
        database.open();
        Log.d("BENCH", "Database opened.");
    }


    private class StoreSchemaDefinition implements LockableDatabase.SchemaDefinition {
        @Override
        public int getVersion() {
            return DB_VERSION;
        }

        @Override
        public void doDbUpgrade(final SQLiteDatabase db) {
            Log.i("DB_LOG", String.format("Upgrading database from version %d to version %d",
                    db.getVersion(), DB_VERSION));

            db.beginTransaction();
            try
            {
                try
                {
                    if (db.getVersion() < 29) {

                        db.execSQL("DROP TABLE IF EXISTS folders");
                        db.execSQL("CREATE TABLE folders (id INTEGER PRIMARY KEY, name TEXT, "
                                + "last_updated INTEGER, unread_count INTEGER, visible_limit INTEGER, status TEXT, "
                                + "push_state TEXT, last_pushed INTEGER, flagged_count INTEGER default 0, "
                                + "integrate INTEGER, top_group INTEGER, poll_class TEXT, push_class TEXT, display_class TEXT"
                                + ")");

                        db.execSQL("CREATE INDEX IF NOT EXISTS folder_name ON folders (name)");
                        db.execSQL("DROP TABLE IF EXISTS messages");
                        db.execSQL("CREATE TABLE messages (" +
                                "id INTEGER PRIMARY KEY, " +
                                "deleted INTEGER default 0, " +
                                "folder_id INTEGER, " +
                                "uid TEXT, " +
                                "subject TEXT, " +
                                "date INTEGER, " +
                                "flags TEXT, " +
                                "sender_list TEXT, " +
                                "to_list TEXT, " +
                                "cc_list TEXT, " +
                                "bcc_list TEXT, " +
                                "reply_to_list TEXT, " +
                                "html_content TEXT, " +
                                "text_content TEXT, " +
                                "attachment_count INTEGER, " +
                                "attachment_image_count INTEGER default 0, " +
                                "attachment_contact_count INTEGER default 0, " +
                                "internal_date INTEGER, " +
                                "message_id TEXT, " +
                                "preview TEXT, " +
                                "mime_type TEXT, "+
                                "normalized_subject_hash INTEGER, " +
                                "empty INTEGER, " +
                                "read INTEGER default 0, " +
                                "flagged INTEGER default 0, " +
                                "answered INTEGER default 0, " +
                                "forwarded INTEGER default 0," +
                                "encryption_keys TEXT, " +
                                "encrypted_content TEXT, " +
                                "pgp_content_uri TEXT, " +
                                "burn_ttl INTEGER default 0, " +
                                "burn_expire_time INTEGER, " +
                                "stored_date INTEGER, " +
                                "public_key_algorithm INTEGER default 0, " +
                                "signature_verified INTEGER default 0" +
                                ")");

                        db.execSQL("DROP TABLE IF EXISTS headers");
                        db.execSQL("CREATE TABLE headers (id INTEGER PRIMARY KEY, message_id INTEGER, name TEXT, value TEXT)");
                        db.execSQL("CREATE INDEX IF NOT EXISTS header_folder ON headers (message_id)");

                        db.execSQL("CREATE INDEX IF NOT EXISTS msg_uid ON messages (uid, folder_id)");
                        db.execSQL("DROP INDEX IF EXISTS msg_folder_id");
                        db.execSQL("DROP INDEX IF EXISTS msg_folder_id_date");
                        db.execSQL("CREATE INDEX IF NOT EXISTS msg_folder_id_deleted_date ON messages (folder_id,deleted,internal_date)");

                        db.execSQL("DROP INDEX IF EXISTS msg_empty");
                        db.execSQL("CREATE INDEX IF NOT EXISTS msg_empty ON messages (empty)");

                        db.execSQL("DROP INDEX IF EXISTS msg_read");
                        db.execSQL("CREATE INDEX IF NOT EXISTS msg_read ON messages (read)");

                        db.execSQL("DROP INDEX IF EXISTS msg_flagged");
                        db.execSQL("CREATE INDEX IF NOT EXISTS msg_flagged ON messages (flagged)");

                        db.execSQL("DROP INDEX IF EXISTS msg_stored_date");
                        db.execSQL("CREATE INDEX IF NOT EXISTS msg_stored_date ON messages (stored_date)");

                        db.execSQL("DROP INDEX IF EXISTS msg_burn_expire_time");
                        db.execSQL("CREATE INDEX IF NOT EXISTS msg_burn_expire_time ON messages (burn_expire_time)");

                        db.execSQL("DROP TABLE IF EXISTS threads");
                        db.execSQL("CREATE TABLE threads (" +
                                "id INTEGER PRIMARY KEY, " +
                                "message_id INTEGER, " +
                                "root INTEGER, " +
                                "parent INTEGER" +
                                ")");

                        db.execSQL("DROP INDEX IF EXISTS threads_message_id");
                        db.execSQL("CREATE INDEX IF NOT EXISTS threads_message_id ON threads (message_id)");

                        db.execSQL("DROP INDEX IF EXISTS threads_root");
                        db.execSQL("CREATE INDEX IF NOT EXISTS threads_root ON threads (root)");

                        db.execSQL("DROP INDEX IF EXISTS threads_parent");
                        db.execSQL("CREATE INDEX IF NOT EXISTS threads_parent ON threads (parent)");

                        db.execSQL("DROP TRIGGER IF EXISTS set_thread_root");
                        db.execSQL("CREATE TRIGGER set_thread_root " +
                                "AFTER INSERT ON threads " +
                                "BEGIN " +
                                "UPDATE threads SET root=id WHERE root IS NULL AND ROWID = NEW.ROWID; " +
                                "END");

                        db.execSQL("DROP TABLE IF EXISTS attachments");
                        db.execSQL("CREATE TABLE attachments (id INTEGER PRIMARY KEY, message_id INTEGER,"
                                + "store_data TEXT, content_uri TEXT, size INTEGER, name TEXT,"
                                + "mime_type TEXT, content_id TEXT, content_disposition TEXT,"
                                + "re_encrypted INTEGER default 0)");

                        db.execSQL("DROP INDEX IF EXISTS attachments_message_id");
                        db.execSQL("CREATE INDEX IF NOT EXISTS attachments_message_id ON attachments (message_id)");

                        db.execSQL("DROP TABLE IF EXISTS pending_commands");
                        db.execSQL("CREATE TABLE pending_commands " +
                                "(id INTEGER PRIMARY KEY, command TEXT, arguments TEXT)");

                        db.execSQL("DROP TRIGGER IF EXISTS delete_folder");
                        db.execSQL("CREATE TRIGGER delete_folder BEFORE DELETE ON folders BEGIN DELETE FROM messages WHERE old.id = folder_id; END;");

                        db.execSQL("DROP TRIGGER IF EXISTS delete_message");
                        db.execSQL("CREATE TRIGGER delete_message BEFORE DELETE ON messages BEGIN DELETE FROM attachments WHERE old.id = message_id; "
                                + "DELETE FROM headers where old.id = message_id; END;");

                        db.execSQL("DROP TABLE IF EXISTS contacts");
                        db.execSQL("CREATE TABLE contacts (" +
                                "id INTEGER PRIMARY KEY, " +
                                "email TEXT, " +
                                "first_name TEXT, " +
                                "last_name TEXT " + ")");
                        db.execSQL("CREATE INDEX IF NOT EXISTS contacts_email ON contacts (email)");
                    }
                } catch (SQLiteException e) {
                    e.printStackTrace();
                    Log.e("DB_LOG", "Exception while upgrading database. Resetting the DB to v0");
                    db.setVersion(0);
                    throw new Error("Database upgrade failed! Resetting your DB version to 0 to force a full schema recreation.");
                }

                db.setVersion(DB_VERSION);
                db.setTransactionSuccessful();
            } finally {
                db.endTransaction();
            }

            if (db.getVersion() != DB_VERSION) {
                throw new Error("Database upgrade failed!");
            }
        }
    }


    public int getSize(){
        return 11;
    }

    public void compact() throws MessagingException {
        if (true)
            //Log.i("DB_LOG", "Before compaction size = " + getSize());

        database.execute(false, new DbCallback<Void>() {
            @Override
            public Void doDbWork(final SQLiteDatabase db) throws WrappedException {
                db.execSQL("VACUUM");
                return null;
            }
        });
        if (true) {
            Log.i("DB_LOG", "After compaction size = " + getSize());
        }
    }


    public void clear() throws MessagingException {
        if (true)
            //Log.i("DB_LOG", "Before prune size = " + getSize());

        if (true) {
            //Log.i("DB_LOG", "After prune / before compaction size = " + getSize());

            Log.i("DB_LOG", "Before clear folder count = " + getFolderCount());
            Log.i("DB_LOG", "Before clear message count = " + getMessageCount());

            //Log.i("DB_LOG", "After prune / before clear size = " + getSize());
        }
        // don't delete messages that are Local, since there is no copy on the server.
        // Don't delete deleted messages.  They are essentially placeholders for UIDs of messages that have
        // been deleted locally.  They take up insignificant space
        database.execute(false, new DbCallback<Void>() {
            @Override
            public Void doDbWork(final SQLiteDatabase db) {
                // Delete entries from 'threads' table
                db.execSQL("DELETE FROM threads WHERE message_id IN " +
                        "(SELECT id FROM messages WHERE deleted = 0 AND uid NOT LIKE 'Local%')");

                // Set 'root' and 'parent' of remaining entries in 'thread' table to 'NULL' to make
                // sure the thread structure is in a valid state (this may destroy existing valid
                // thread trees, but is much faster than adjusting the tree by removing messages
                // one by one).
                db.execSQL("UPDATE threads SET root=id, parent=NULL");

                // Delete entries from 'messages' table
                db.execSQL("DELETE FROM messages WHERE deleted = 0 AND uid NOT LIKE 'Local%'");
                return null;
            }
        });

        compact();

        if (true) {
            Log.i("DB_LOG", "After clear message count = " + getMessageCount());

            Log.i("DB_LOG", "After clear size = " + getSize());
        }
    }

    public int getMessageCount() throws MessagingException {
        return database.execute(false, new DbCallback<Integer>() {
            @Override
            public Integer doDbWork(final SQLiteDatabase db) {
                Cursor cursor = null;
                try {
                    cursor = db.rawQuery("SELECT COUNT(*) FROM messages", null);
                    cursor.moveToFirst();
                    return cursor.getInt(0);   // message count
                } finally {
                    if( cursor != null ){
                        cursor.close();
                    }
                }
            }
        });
    }

    public int getFolderCount() throws MessagingException {
        return database.execute(false, new DbCallback<Integer>() {
            @Override
            public Integer doDbWork(final SQLiteDatabase db) {
                Cursor cursor = null;
                try {
                    cursor = db.rawQuery("SELECT COUNT(*) FROM folders", null);
                    cursor.moveToFirst();
                    return cursor.getInt(0);        // folder count
                } finally {
                    if( cursor != null ){
                        cursor.close();
                    }
                }
            }
        });
    }


    public Map<String, String> moveMessages(final Message[] msgs) throws MessagingException {

        final Map<String, String> uidMap = new HashMap<String, String>();

        try {
            database.execute(false, new DbCallback<Void>() {
                @Override
                public Void doDbWork(final SQLiteDatabase db) throws WrappedException {
                    try {
                        System.out.println("LocalFOlder.moveMessages() moving " + msgs.length + " messages");
                        for (Message message : msgs) {
                            Message lMessage = (Message)message;

                            String oldUID = message.getUid();

                            if (true) {
                                Log.d("DB_LOG", "Updating folder_id to for message with UID "
                                        + message.getUid() + ", id  currently in folder ");
                            }

                            String newUid = "MYLOCAL_" + UUID.randomUUID().toString();
                            message.setUid(newUid);
                            oldUID = message.getUid();

                            uidMap.put(oldUID, newUid);
                            long msgId = -1; //lMessage.getId();
                            String[] idArg = new String[] { Long.toString(msgId) };

                            ContentValues cv = new ContentValues();


                            // Create/update entry in 'threads' table for the message in the
                            // target folder
                            cv.clear();
                            cv.put("message_id", msgId);


                            cv.clear();
                            cv.put("uid", oldUID);
                            cv.putNull("flags");
                            cv.put("read", 1);
                            cv.put("deleted", 1);
                            cv.put("folder_id", 1);
                            cv.put("empty", 0);

                            String messageId = message.getMessageId();
                            if (messageId != null) {
                                cv.put("message_id", messageId);
                            }

                            final long newId;
                            newId = db.insert("messages", null, cv);
                            cv.clear();
                            cv.put("message_id", newId);
                            db.update("threads", cv, "id = ?",
                                    new String[] { Long.toString(3) });
                        }
                    } catch (MessagingException e) {
                        throw new WrappedException(e);
                    }
                    return null;
                }
            });


            return uidMap;
        } catch (WrappedException e) {
            throw(MessagingException) e.getCause();
        }

    }


    public boolean addMessages(final Message[] messages, final boolean copy) throws MessagingException {

        try {
            final Long[] expirationTime = new Long[1];

            final Map<String, String> uidMap = new HashMap<String, String>();
            database.execute(true, new DbCallback<Void>() {
                @Override
                public Void doDbWork(final SQLiteDatabase db) throws WrappedException {
                    try {
                        for (Message message : messages) {

                            long oldMessageId = -1;
                            String uid = message.getUid();
                            if (uid == null || copy) {
                                    /*
                                     * Create a new message in the database
                                     */
                                String randomLocalUid = "MYLOCAL_" +
                                        UUID.randomUUID().toString();

                                if (copy) {
                                    // Save mapping: source UID -> target UID
                                    uidMap.put(uid, randomLocalUid);
                                } else {
                                    // Modify the Message instance to reference the new UID
                                    message.setUid(randomLocalUid);
                                }

                                // The message will be saved with the newly generated UID
                                uid = randomLocalUid;
                            }

                            long rootId = -1;
                            long parentId = -1;

                            boolean isDraft = false;

                            String text = message.getText();
                            String html = "empty";
                            String preview = Message.calculateContentPreview(text);
                            long start = System.currentTimeMillis();


                            try {
                                ContentValues cv = new ContentValues();
                                cv.put("uid", uid);
                                cv.put("subject", message.getSubject());
                                cv.put("sender_list", message.getFrom());
                                cv.put("date", message.getSentDate() == null
                                        ? System.currentTimeMillis() : message.getSentDate().getTime());
                                cv.put("flags", "SOME_FLAGS");
                                cv.put("deleted", message.isSet(Flag.DELETED) ? 1 : 0);
                                cv.put("read", message.isSet(Flag.SEEN) ? 1 : 0);
                                cv.put("flagged", message.isSet(Flag.FLAGGED) ? 1 : 0);
                                cv.put("answered", message.isSet(Flag.ANSWERED) ? 1 : 0);
                                cv.put("forwarded", message.isSet(Flag.FORWARDED) ? 1 : 0);
                                cv.put("folder_id", 1);
                                cv.put("to_list", message.getFrom());
                                cv.put("cc_list", message.getFrom());
                                cv.put("bcc_list", message.getFrom());
                                cv.put("html_content", html.length() > 0 ? html : null);
                                cv.put("text_content", text.length() > 0 ? text : null);
                                cv.put("preview", preview.length() > 0 ? preview : null);
                                cv.put("reply_to_list", message.getReplyTo());
                                cv.put("attachment_count", 0);
                                cv.put("attachment_image_count", 0);
                                cv.put("attachment_contact_count", 0);
                                cv.put("internal_date",  message.getInternalDate() == null
                                        ? System.currentTimeMillis() : message.getInternalDate().getTime());
                                cv.put("stored_date", System.currentTimeMillis());
                                cv.put("mime_type", "dummy/mimetype");
                                cv.put("encryption_keys", "XXXX");
                                cv.put("empty", 0);
                                cv.putNull("burn_expire_time");


                                String messageId = message.getMessageId();
                                if (messageId != null) {
                                    cv.put("message_id", messageId);
                                }

                                System.out.println("LocalStore.appendMessage() message = " + oldMessageId + " read = " + message.isSet(Flag.SEEN));

                                long msgId;

                                if (oldMessageId == -1) {
                                    msgId = db.insert("messages", "uid", cv);

                                    // Create entry in 'threads' table
                                    cv.clear();
                                    cv.put("message_id", msgId);

                                    if (rootId != -1) {
                                        cv.put("root", rootId);
                                    }
                                    if (parentId != -1) {
                                        cv.put("parent", parentId);
                                    }

                                    db.insert("threads", null, cv);
                                } else {
                                    db.update("messages", cv, "id = ?", new String[] { Long.toString(oldMessageId) });
                                    msgId = oldMessageId;
                                }
                            } catch (Exception e) {
                                throw new MessagingException("Error appending message", e);
                            }
                        }
                    } catch (MessagingException e) {
                        throw new WrappedException(e);
                    }
                    return null;
                }
            });


            return true;
        } catch (WrappedException e) {
            throw(MessagingException) e.getCause();
        }
    }


    public void simpleSqlExecute( final String aSql ) {
        database.execute(false, new DbCallback<Void>() {
            @Override
            public Void doDbWork(final SQLiteDatabase db) {
                db.execSQL(aSql);
                return null;
            }
        });
    }

    public String GetSimpleQueryValue( final String aSql ){
        final String sqlQuery = aSql; //"PRAGMA "+ aPragma + ";";
        String lResult = "";
        final ArrayList<String> lVals = new ArrayList<String>();

        database.execute(false, new DbCallback<Integer>() {
            @Override
            public Integer doDbWork(final SQLiteDatabase db) {
                Cursor cursor = null;
                try {
                    cursor = db.rawQuery(sqlQuery, null);
                    //cursor.moveToFirst();
                    while (cursor.moveToNext()){
                        lVals.add(cursor.getString(0));        // folder count
                    }
                    return 0;
                } finally {
                    if( cursor != null ){
                        cursor.close();
                    }
                }
            }
        });

        for(int i=0; i<lVals.size(); i++){
            lResult += lVals.get(i)+" ";
        }
        return lResult;
    }


    public ArrayList<Message> searchForMessages() throws MessagingException
    {

        StringBuilder query = new StringBuilder();
        List<String> queryArgs = new ArrayList<String>();
        //SqlQueryBuilder.buildWhereClause(mAccount, search.getConditions(), query, queryArgs);

        // Avoid "ambiguous column name" error by prefixing "id" with the message table name
        //String where = SqlQueryBuilder.addPrefixToSelection(new String[] { "id" }, "messages.", query.toString());

        String[] selectionArgs = queryArgs.toArray(EMPTY_STRING_ARRAY);

        String sqlQuery = "SELECT " + GET_MESSAGES_COLS + "FROM messages " +
                "LEFT JOIN threads ON (threads.message_id = messages.id) " +
                "LEFT JOIN folders ON (folders.id = messages.folder_id) WHERE " +
                "((empty IS NULL OR empty != 1) AND deleted = 0)" +
                //((!StringUtils.isNullOrEmpty(where)) ? " AND (" + where + ")" : "") +
                " ORDER BY date DESC";

        if (true) {
            Log.d("BENCH", "Query = " + sqlQuery);
        }

        return getMessages(sqlQuery, selectionArgs);
    }

    private ArrayList<Message> getMessages(
            final String queryString, final String[] placeHolders
    ) throws MessagingException {
        //Log.i("LocalStore.getMessages", "SQL: " + queryString);
        final ArrayList<Message> messages = new ArrayList<Message>();
        final int j = database.execute(false, new DbCallback<Integer>() {
            @Override
            public Integer doDbWork(final SQLiteDatabase db) throws WrappedException {
                Cursor cursor = null;
                int i = 0;
                try {
                    cursor = db.rawQuery(queryString + " LIMIT 10", placeHolders);

                    while (cursor.moveToNext()) {
                        Message message = new Message(true);
                        message.mSubject = cursor.getString(0);
                        message.mFrom = cursor.getString(1);
                        message.mText = cursor.getString(14);
                        //message.populateFromGetMessageCursor(cursor);

                        messages.add(message);
                        i++;
                    }
                    cursor.close();


                    //cursor = db.rawQuery(queryString + " LIMIT -1 OFFSET 10", placeHolders);
                    //cursor = db.rawQuery(queryString + " LIMIT 5000", placeHolders);
                    cursor = db.rawQuery(queryString, placeHolders);

                    while (cursor.moveToNext()) {
                        if( i>=20 ) {
                            Message message = new Message();
                            //message.populateFromGetMessageCursor(cursor);
                            message.mSubject = cursor.getString(0);
                            message.mFrom = cursor.getString(1);
                            message.mText = cursor.getString(14);

                            messages.add(message);
                        }
                        i++;
                    }
                } catch (Exception e) {
                    Log.d("BENCH", "Got an exception", e);
                } finally {
                    if( cursor != null ) {
                        cursor.close();
                    }
                }
                return i;
            }
        });
        //if (listener != null) {
        //    listener.messagesFinished(j);
        //}

        return messages; //.toArray(EMPTY_MESSAGE_ARRAY);

    }




}
