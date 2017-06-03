package clientServerSuperStructure;

import jswing.GeneralSilhouette;
import jswing.Ponto;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

/**
 * Created by Zerbs on 11.11.2016.
 */
public class ProcessPontoThread extends Thread {
    private Ponto ponto;
    private float R;

    private InetAddress clientaddress;
    private int clientport;

    private DatagramSocket socket;

    public ProcessPontoThread(Ponto ponto, float R, InetAddress clientaddress, int clientport, DatagramSocket socket){
        this.ponto = ponto;
        this.R = R;

        this.clientaddress = clientaddress;
        this.clientport = clientport;

        this.socket = socket;
    }



    @Override
    public void start(){
        int rezult = 0;
        if (new GeneralSilhouette(R).checkPonto(ponto)){
            System.out.println("Ponto in the silhouette :3");
            rezult = 100;
        } else {
            System.out.println("Ponto is not in the silhouette :(");
            rezult = -100;
        }
        sendInt(rezult);
    }

    private void sendInt(int rezult){
        assert(socket.isConnected());
        byte[] data = ByteArrayConverter.intToByteArray(rezult);
        DatagramPacket datagramPacket = new DatagramPacket(data,data.length,clientaddress,clientport);
        try {
            socket.send(datagramPacket);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
