package net;

import java.io.IOException;
import java.net.*;

public class Server {
    private final int port;
    private ServerSocket serverSocket;
    private Thread listenThread;

    private boolean running = false;

    public Server(int port) {
        this.port = port;
        try {
            serverSocket = new ServerSocket(port);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void start(){
            running = true;
            listenThread = new Thread(() -> listen());
            listenThread.start();
    }

    public void stop(){
        running = false;
        //closeServerSocket();
    }

    private void closeServerSocket(){
        try {
            serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void listen(){
        while(running) {
            Socket socket;
            try {
                socket = serverSocket.accept();
                new Thread(new ClientSession(socket)).start();
            } catch (IOException e) {
                System.out.println("[Server] Client disconnected");
            }
        }
    }

    public int getPort(){
        return port;
    }

    public InetAddress getSocketAddress(){
        return serverSocket.getInetAddress();
    }
}
