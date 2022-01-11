package com.example.miptest2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.example.informationprotection.MipLibrary;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        MipLibrary.Init(getApplicationContext());
    }
}