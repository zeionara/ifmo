package net;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

/**
 * Created by Zerbs on 12.11.2016.
 */
public class ClientSession implements Runnable{
    private Socket socket;
    private InputStream in;
    private OutputStream out;

    public ClientSession(Socket socket) throws IOException{
        this.socket = socket;
        in = socket.getInputStream();
        out = socket.getOutputStream();
    }

    @Override
    public void run() {
        Request request;
        while(true) {
            System.out.println("[Server] Receiving request...");
            request = Channel.receiveRequest(socket);
            if (request == null){
                return;
            }
            System.out.println("[Server] Received : "+request.getX()+" "+request.getY());
            System.out.println("[Server] Processing request...");
            new Thread(new ClientProcess(socket,request)).start();
        }
    }
}
