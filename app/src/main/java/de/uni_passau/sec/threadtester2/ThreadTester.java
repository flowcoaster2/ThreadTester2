package de.uni_passau.sec.threadtester2;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class ThreadTester extends Activity implements View.OnClickListener{
    private static String TAG = "ThreadTester";
    private TextView editField = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button startThreads = (Button) findViewById(R.id.button);
        startThreads.setOnClickListener(this);

        editField = (TextView) findViewById(R.id.editText);
    }

    public void startThreads(View v) {
        Log.d(TAG, "starting Threads");
        int numThreads = Integer.parseInt(editField.getText().toString());

        RunnerThread[] rt = new RunnerThread[numThreads];
        boolean useJni = false;
        for (int i=0; i<numThreads; i++) {
            rt[i] = new RunnerThread(useJni);
            if (i == numThreads/2) useJni = true;
        }
        Log.d(TAG, "created "+numThreads+" threads");

        for (int i=0; i<numThreads; i++) {
            rt[i].start();
        }
        Log.d(TAG, "All threads now running");
    }

    //@Override
    public void onClick(View view) {
        startThreads(view);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
}
