package net;

import java.io.*;
import java.net.SocketException;

public class Request implements Serializable{

    private double X;
    private double Y;
    private double R;

    public Request(double x, double y, double r){
        X = x;
        Y = y;
        R = r;
    }

    public void writeTo(OutputStream out) throws SocketException{
        try {
            ObjectOutputStream serializer = new ObjectOutputStream(out);
            serializer.writeObject(this);
        } catch (SocketException e){
            System.out.println("Connection reset");
            throw e;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static Request readFrom(InputStream in){
        Request request = null;
        try {
            ObjectInputStream deserializer = new ObjectInputStream(in);
            request = (Request)deserializer.readObject();
        } catch (IOException e) {
            System.out.println("[Server] Client disconnected");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        return request;
    }

    public double getX(){
        return X;
    }

    public double getY(){
        return Y;
    }

    public double getR(){
        return R;
    }

}
