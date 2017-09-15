package com.example.myjni;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.example.bean.Person;
import com.example.jni.Test;

import java.util.ArrayList;
import java.util.Arrays;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    int i = 999;
    boolean flag = false;
    private static Context sCtx;
    private Test test;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        sCtx = getApplicationContext();
        test = new Test();
    }

    public void callNative(View view) {

        final StringBuffer sBuf = new StringBuffer();
        sBuf.append("sayHello: ").append(Test.sayHello()).append(", \n")
                .append("getLink: ").append(Arrays.toString(Test.getLink())).append(", \n")
                .append("getNetInfo: ").append(Test.getNetInfo()).append(", \n")
                .append("getBoolean: ").append(Test.getBoolean(flag = !flag)).append(", \n")
                .append("getInt: ").append(Test.getInt(i)).append(", \n")
                .append("getByte: ").append(Test.getByte(200)).append(", \n")
                .append("getChar: ").append(Test.getChar((char) 98)).append(", \n")
                .append("getShort: ").append(Test.getShort()).append(", \n")
                .append("getDouble: ").append(Test.getDouble()).append(", \n")
                .append("getFloat: ").append(Test.getFloat()).append(", \n")
                .append("curTimeMillis: ").append(System.currentTimeMillis()).append(", \n")
                .append("getLong: ").append(Test.getLong()).append(", \n")
                .append("getInts: ").append(Arrays.toString(Test.getInts(10))).append(", \n")
                .append("getBooleans: ").append(Arrays.toString(Test.getBooleans(10))).append(", \n")
                .append("getBytes: ").append(Arrays.toString(Test.getBytes(10))).append(", \n")
                .append("getChars: ").append(Arrays.toString(Test.getChars(10))).append(", \n")
                .append("getShorts: ").append(Arrays.toString(Test.getShorts(10))).append(", \n")
                .append("getLongs: ").append(Arrays.toString(Test.getLongs(10))).append(", \n")
                .append("getFloats: ").append(Arrays.toString(Test.getFloats(10))).append(", \n")
                .append("getDoubles: ").append(Arrays.toString(Test.getDoubles(10))).append(", \n");
//        Toast.makeText(this, sBuf.toString(), Toast.LENGTH_SHORT).show();
        Log.e(TAG, "callNative: " + sBuf.toString());

        int[][] intArrays = Test.getIntArrays(10);
        for (int i = 0; i < intArrays.length; i++) {
            int[] intArray = intArrays[i];
            for (int j = 0; j < intArray.length; j++) {
                System.out.print(intArray[j] + " ");
            }
            System.out.println();
        }

        test.callNative();
        // Test.callNative();
        boolean aNull = Test.isNull();
        Log.e(TAG, "callNative: "+aNull);
    }

    public static void showToast(String msg, int count) {
        Toast.makeText(sCtx, msg + " " + count, Toast.LENGTH_SHORT).show();

    }

    public void callNative2(View view) {
        Person birth = Test.birth();
        Log.e(TAG, "callNative2: "+birth.toString());
        test.callbackByNative(new Person("ddd",12));

        for (Person person : Test.getListStudent()) {
            Log.e(TAG, "callNative2: "+person.toString());
        }
    }
}
