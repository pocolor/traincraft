package me.pocolor.traincraft.engine;

public final class Engine {
    static {
        System.loadLibrary("engine");
    }

    public native void run();
}
