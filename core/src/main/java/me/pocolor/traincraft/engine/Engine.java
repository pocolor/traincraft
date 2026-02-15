package me.pocolor.traincraft.engine;

public class Engine {
    static { System.loadLibrary("native_engine"); }

    public native void test();
}
