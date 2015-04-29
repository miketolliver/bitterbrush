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


public class MainActivity extends ActionBarActivity {

    public DbManager mDbManager;
    public TextView mResults;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mResults = (TextView)findViewById(R.id.mTextResults);
        mDbManager = new DbManager(this);

        Button clickButton = (Button) findViewById(R.id.mStartBtn);
        clickButton.setOnClickListener( new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                doWork();
            }
        });



    }

    public boolean doWork(){

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


        return true;
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
