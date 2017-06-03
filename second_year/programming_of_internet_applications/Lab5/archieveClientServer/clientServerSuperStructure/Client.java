package clientServerSuperStructure;

import jswing.Ponto;

import java.io.IOException;
import java.net.*;

/**
 * Created by Zerbs on 11.11.2016.
 */
public class Client {
    private final int port;
    private InetAddress address;

    private Thread listenThread;
    private boolean running = false;
    private DatagramSocket socket;

    public Client(String ipAddress, int port){
        this.port = port;
        try {
            this.address = InetAddress.getByName(ipAddress);
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }

    public void start(){
        try {
            socket = new DatagramSocket(port,address);
        } catch (SocketException e){
            e.printStackTrace();
            return;
        }
    }

    public void send(byte[] data, InetAddress address, int port){
        assert(socket.isConnected());
        DatagramPacket datagramPacket = new DatagramPacket(data,data.length,address,port);
        try {
            socket.send(datagramPacket);
            System.out.println("sent");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendFloat(float dataf, InetAddress address, int port){
        assert(socket.isConnected());
        byte[] data = ByteArrayConverter.floatToByteArray(dataf);
        DatagramPacket datagramPacket = new DatagramPacket(data,data.length,address,port);
        try {
            socket.send(datagramPacket);
            System.out.println("sent "+dataf);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendPonto(Ponto p, InetAddress address, int port){
        assert(socket.isConnected());
        byte[] dataX = ByteArrayConverter.floatToByteArray((float)p.getX());
        byte[] dataY = ByteArrayConverter.floatToByteArray((float)p.getY());
        DatagramPacket datagramPacketX = new DatagramPacket(dataX,dataX.length,address,port);
        DatagramPacket datagramPacketY = new DatagramPacket(dataY,dataY.length,address,port);
        try {
            System.out.println("sent "+p);
            socket.send(datagramPacketX);
            socket.send(datagramPacketY);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public int receiveInt(){
        byte[] buf = new byte[4];
        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        try {
            socket.receive(packet);
            buf = packet.getData();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return ByteArrayConverter.byteArrayToInt(buf);
    }


    private InetAddress getAddress(){
        return address;
    }

    private int getPort(){
        return port;
    }

}
