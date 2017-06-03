package clientServerSuperStructure;

import jswing.Ponto;

import java.io.IOException;
import java.net.*;

/**
 * Created by Zerbs on 11.11.2016.
 */
public class Server {
    private final int port;
    private InetAddress address;

    private int clientport;
    private InetAddress clientaddress;

    private Thread listenThread;
    private boolean running = false;
    private DatagramSocket socket;

    public Server(String ipaddress, int port) {
        this.port = port;
        try {
            this.address = InetAddress.getByName(ipaddress);
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


        running = true;

        listenThread = new Thread(() -> listen());
        listenThread.start();
    }

    private void listen(){
        while(running){
            Thread processThread = new ProcessPontoThread(receivePonto(),receiveFloat(),clientaddress,clientport,socket);
            processThread.start();
        }
    }

    private byte[] receive(){
        byte[] buf = new byte[2];
        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        try {
            System.out.println("trying to receive...");
            socket.receive(packet);
            byte[] byte_array = packet.getData();

            System.out.println("received : ");
        } catch (IOException e) {
            e.printStackTrace();
        }
        return packet.getData();
    }

    private float receiveFloat(){
        byte[] buf = new byte[4];
        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        try {
            System.out.println("trying to receive float...");
            socket.receive(packet);
            buf = packet.getData();

            System.out.println("received bytes of float ");
        } catch (IOException e) {
            e.printStackTrace();
        }

        clientaddress = packet.getAddress();
        clientport = packet.getPort();
        System.out.println("Client's : "+clientaddress+" "+clientport);

        return ByteArrayConverter.byteArrayToFloat(buf);
    }

    private Ponto receivePonto(){
        byte[] bufX = new byte[4];
        byte[] bufY = new byte[4];
        DatagramPacket packetX = new DatagramPacket(bufX, bufX.length);
        DatagramPacket packetY = new DatagramPacket(bufY, bufY.length);

        try {
            socket.receive(packetX);
            bufX = packetX.getData();

            socket.receive(packetY);
            bufY = packetY.getData();

            System.out.println("received coords of ponto ");
        } catch (IOException e) {
            e.printStackTrace();
        }

        return new Ponto(ByteArrayConverter.byteArrayToFloat(bufX),ByteArrayConverter.byteArrayToFloat(bufY));
    }

    private void process(DatagramPacket datagramPacket){

    }

    /*
    *
    * @param data is the data to be sent
    * @param address is the is the address the data to be sent to
    * @param port is the port the data to be sent to
     */
    private void send(byte[] data){
        assert(socket.isConnected());
        DatagramPacket datagramPacket = new DatagramPacket(data,data.length,address,port);
        try {
            socket.send(datagramPacket);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public InetAddress getAddress(){
        return address;
    }

    public int getPort(){
        return port;
    }


}
