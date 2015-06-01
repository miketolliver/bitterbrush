package com.example.mike.javabenchmark;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

import java.util.ArrayList;


public class MainActivity extends ActionBarActivity {

    public DbManager mDbManager;
    public TextView mResults;
    public LocalStore mLocalStore;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mResults = (TextView)findViewById(R.id.mTextResults);

        mLocalStore = new LocalStore(this);
        //mDbManager = new DbManager(this);

        Button clickButton = (Button) findViewById(R.id.mStartBtn);
        clickButton.setOnClickListener( new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                setSlowPragmas();
            }
        });

        clickButton = (Button) findViewById(R.id.mBtnFast);
        clickButton.setOnClickListener( new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                setFastPragmas();
            }
        });

        clickButton = (Button) findViewById(R.id.mBtnAddMessages);
        clickButton.setOnClickListener( new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                addMessages();
            }
        });

        clickButton = (Button) findViewById(R.id.mBtnDelete);
        clickButton.setOnClickListener( new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                deleteSomeMessages();
            }
        });

        clickButton = (Button) findViewById(R.id.mBtnSearch);
        clickButton.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                searchMessages();
            }
        });

        clickButton = (Button) findViewById(R.id.mBtnPragmas);
        clickButton.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ListPragmas();
            }
        });

    }

    public void setFastPragmas(){
        String sql = "PRAGMA cache_size=2000";
        mLocalStore.doSimpleSql(sql);
        Log.d("BENCH", "PRAGMA set FAST...");
    }

    public void setSlowPragmas(){
        String sql = "PRAGMA cache_size=8000";
        mLocalStore.doSimpleSql(sql);
        Log.d("BENCH", "PRAGMA set SLOW...");
    }

    public boolean doWork(){

        /*
        Log.d("BENCH", "Starting work...");

        int lLoop = 100;
        long t1 = System.currentTimeMillis();

        for( int i=0; i<lLoop; i++ ){
            String lValue = "VALUE"+i;
            mDbManager.AddValueString(lValue, "Some dummy string.");
        }

        long t2 = System.currentTimeMillis();
        long dur1 = t2-t1;
        Log.d("BENCH", "Duration task1: "+ dur1);

        String str = "Duration task1: " + dur1 + "\n";
        mResults.append(str);

        for( int i=0; i<lLoop; i++ ) {
            String lValue = "VALUE" + i;
            mDbManager.SetValueString(lValue, "Some OTHER dummy string. Some OTHER dummy string. Some OTHER dummy string. Some OTHER dummy string. Some OTHER dummy string. Some OTHER dummy string. Some OTHER dummy string. Some OTHER dummy string. ");
        }
        long t3 = System.currentTimeMillis();
        long dur2 = t3-t2;
        Log.d("BENCH", "Duration task2: "+ dur2);
        str = "Duration task2: " + dur2 + "\n";
        mResults.append(str);


        String val="";
        for( int i=0; i<lLoop; i++ ) {
            String lValue = "VALUE" + i;
            val = mDbManager.GetValueString(lValue);
        }
        long t4 = System.currentTimeMillis();
        long dur3 = t4-t3;
        Log.d("BENCH", "Duration task3: "+ dur3 + ". String = "+val);
        str = "Duration task3: " + dur3 + ". String = "+val + "\n";
        mResults.append(str);


        for( int i=0; i<lLoop; i++ ) {
            String lValue = "VALUE" + i;
            mDbManager.DeleteValue(lValue);
        }
        long t5 = System.currentTimeMillis();
        long dur4 = t5-t4;
        Log.d("BENCH", "Duration task4: "+ dur4);
        str = "Duration task4: " + dur4 + "\n";
        mResults.append(str);

        */
        return true;
    }

    public void ListPragmas(){

        ArrayList<String> lPragmas = new ArrayList<String>();

        lPragmas.add("auto_vacuum");
        lPragmas.add("automatic_index");
        lPragmas.add("busy_timeout");
        lPragmas.add("cache_size");
        lPragmas.add("cache_spill");
        lPragmas.add("compile_options");
        lPragmas.add("encoding");
        lPragmas.add("foreign_key_check");
        lPragmas.add("freelist_count");
        lPragmas.add("fullfsync");
        lPragmas.add("ignore_check_constraints");
        lPragmas.add("incremental_vacuum");
        lPragmas.add("journal_mode");
        lPragmas.add("journal_size_limit");
        lPragmas.add("legacy_file_format");
        lPragmas.add("locking_mode");
        lPragmas.add("max_page_count");
        lPragmas.add("mmap_size");
        lPragmas.add("page_count");
        lPragmas.add("page_size");
        lPragmas.add("read_uncommitted");
        lPragmas.add("schema_version");
        lPragmas.add("soft_heap_limit");
        lPragmas.add("synchronous");
        lPragmas.add("temp_store");
        lPragmas.add("threads");

        for(int i=0; i< lPragmas.size(); i++){
            String lSql = "Pragma "+lPragmas.get(i)+";";
            String lRes = mLocalStore.GetSimpleQueryValue(lSql);
            String dbg = "Pragma "+lPragmas.get(i)+" = "+ lRes+ "\n";
            Log.d("BENCH", dbg);
            mResults.append(dbg);
        }

        String lSql = "select sqlite_version();";
        String lRes = mLocalStore.GetSimpleQueryValue(lSql);
        String dbg = "Sqlite version = "+ lRes+ "\n";
        Log.d("BENCH", dbg);
        mResults.append(dbg);

        lSql = "PRAGMA synchronous = 1;";
        mLocalStore.simpleSqlExecute(lSql);
        lSql = "PRAGMA temp_store = 2;";
        mLocalStore.simpleSqlExecute(lSql);
        lSql = "PRAGMA cache_size = 2000;";
        mLocalStore.simpleSqlExecute(lSql);
    }

    public boolean searchMessages(){

        ArrayList<Message> msgs;

        long t1 = System.currentTimeMillis();
        msgs = mLocalStore.searchForMessages();

        int lMsgCount = msgs.size();
        long t2 = System.currentTimeMillis();
        long dur1 = t2-t1;
        Log.d("BENCH", "Duration SearchMessages: "+ dur1 +", returned msgs: "+lMsgCount);

        String str = "Duration SearchMessages: " + dur1 +", returned msgs: "+lMsgCount+ "\n";
        mResults.append(str);

        if(lMsgCount > 0){
            Message lmsg = msgs.get(0);
            String str2 = "SearchMessages first result subject: " + lmsg.mSubject + "\n";
            String str3 = "SearchMessages first result text: " + lmsg.mText + "\n";
            mResults.append(str2);
            mResults.append(str3);
        }



        return true;
    }

    public boolean deleteSomeMessages(){
        long t1 = System.currentTimeMillis();
        mLocalStore.deleteSomeMessages();
        long t2 = System.currentTimeMillis();
        long dur1 = t2-t1;

        Log.d("BENCH", "Duration deleteSomeMessages: "+ dur1);
        String str = "Duration deleteSomeMessages: " + dur1 + "\n";
        mResults.append(str);

        return true;
    }

    public boolean addMessages(){

        int lCount = 100;
        Message[] lMessages = new Message[lCount];
        for(int i=0; i<lCount; i++){
            lMessages[i] = new Message();
        }

        long t1 = System.currentTimeMillis();
        boolean lres = mLocalStore.addMessages( lMessages, false );
        long t2 = System.currentTimeMillis();
        long dur1 = t2-t1;
        Log.d("BENCH", "Duration AddMessages: "+ dur1);

        String str = "Duration AddMessages: " + dur1 + "\n";
        mResults.append(str);
        return lres;
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
