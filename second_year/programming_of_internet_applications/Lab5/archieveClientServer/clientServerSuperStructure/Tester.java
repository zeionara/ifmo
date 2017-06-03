package clientServerSuperStructure;

import jswing.Ponto;

/**
 * Created by Zerbs on 11.11.2016.
 */
public class Tester {
    public static void main(String[] args) {
        float R = 7.6f;

        Server server = new Server("127.0.0.1",6666);
        server.start();

        Client client = new Client("127.0.0.1",6667);
        client.start();
        client.sendPonto(new Ponto(100.0,100.0),server.getAddress(),server.getPort());
        client.sendFloat(R,server.getAddress(),server.getPort());
        System.out.println(client.receiveInt());
        //client.sendFloat(12.34f,server.getAddress(),server.getPort());
        //client.sendFloat(2.718281828459045f,server.getAddress(),server.getPort());
    }
}
