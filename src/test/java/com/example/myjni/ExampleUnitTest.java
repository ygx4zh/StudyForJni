package com.example.myjni;

import org.junit.Test;

import java.lang.reflect.Type;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() throws Exception {
        assertEquals(4, 2 + 2);
    }

    @Test
    public void test_getType() throws Exception{
        //int[] arr = new int[10];
        Type t = String[].class;
        System.out.println(t.toString());
    }
}