package com.example.tensorapp;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.widget.TextView;

import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI("android.resource://com.example.tensorapp/" + R.raw.zivert));
        byte [] imageBuff = getImageFromAssets();

        tv.setText(stringFromJNI(imageBuff));
    }

    byte[] getImageFromAssets() {
        InputStream is = null;
        try {
            is = getAssets().open("zivert.jpg");
        } catch (IOException e) {
            e.printStackTrace();
        }


        int size = 0;
        try {
            size = is.available();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Read the entire asset into a local byte buffer.
        byte[] buffer = new byte[size];
        try {
            is.read(buffer);
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            is.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return buffer;
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     * @param imageBuff
     */
    public native String stringFromJNI(byte[] imageBuff);
}