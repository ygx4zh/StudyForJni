package com.example.jni;


import android.util.Log;

public class Test {
    private static final String TAG = "Test";
    static
    {
        System.loadLibrary("hello_jni");
    }
    public static native boolean getBoolean(boolean flag);
    public static native int getInt(int i);
    public static native byte getByte(int b);
    public static native short getShort();
    public static native char getChar(char c);
    public static native long getLong();
    public static native float getFloat();
    public static native double getDouble();

    public static native boolean[] getBooleans(int size);
    public static native int[] getInts(int size);
    public static native byte[] getBytes(int sieze);
    public static native short[] getShorts(int size);
    public static native char[] getChars(int size);
    public static native long[] getLongs(int size);
    public static native float[] getFloats(int size);
    public static native double[] getDoubles(int size);

    public static native int[][] getIntArrays(int size);

    public static native String sayHello();
    public static native String[] getLink();
    public static native NetInfo getNetInfo();

    public native void callNative();
    public void callByNative(String msg){
        Log.e(TAG, "callByNative: "+msg);
    }

    public static native boolean isNull();
}
