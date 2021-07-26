package com.example.tensorapp;

import androidx.appcompat.app.AppCompatActivity;
import com.example.tensor.R;
import android.os.Bundle;
import android.widget.TextView;


import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


    byte[] getImage(){
        try {
            InputStream stream = this.getAssets().open("zivert.jpg");
            int size = stream.available();
            byte[] buffer = new byte[size];
            int r = stream.read(buffer);
            stream.close();
            return buffer;
        } catch (IOException e) {
            // Handle exceptions here
        }
        return null;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}