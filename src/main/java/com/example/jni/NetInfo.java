package com.example.jni;


public class NetInfo {
    private String ip;
    private int port;

    public int getPort(){
        return port;
    }

    public String getIp() {
        return ip;
    }

    @Override
    public String toString(){
        return "ip: "+ip+", port: "+port;
    }
}
