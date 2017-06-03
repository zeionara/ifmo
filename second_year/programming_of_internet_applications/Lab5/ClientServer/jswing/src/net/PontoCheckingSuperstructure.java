package net;

import jswing.Lab4;
import jswing.Ponto;

import java.io.IOException;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.util.ConcurrentModificationException;
import java.util.Set;

public class PontoCheckingSuperstructure {
    Lab4 lab4;
    Thread checking;
    Set<Ponto> pontos;
    Socket socket;
    SocketAddress socketAddress;
    boolean changesShowed = true;

    public PontoCheckingSuperstructure(Set<Ponto> pontos, SocketAddress socketAddress, Lab4 lab4){
        this.pontos = pontos;
        this.socketAddress = socketAddress;
        this.socket = new Socket();
        this.lab4 = lab4;

        checking = new Thread(() -> circuloInferni());
        checking.start();
    }

    private void circuloInferni(){
        while(true){
            try {
                pontos.stream().filter((Ponto p) -> !p.isChecked()).forEach((Ponto p) -> {
                    System.out.println("Checking...");
                    Request request;
                    request = new Request(p.getX(), p.getY(), lab4.getR());
                    boolean sent = false;
                    do {
                        try {
                            System.out.println("Trying to send request...");

                            Channel.sendRequest(request, socket);
                            sent = true;
                            System.out.println("Successful!");
                        } catch (SocketException e) {
                            System.out.println("Failed!");
                            tryConnect();
                        }
                    } while (!sent);
                    System.out.println("Waiting for response...");
                    Response response = null;
                    try {
                        response = Channel.receiveResponse(socket);
                    } catch (SocketException e) {
                        System.out.println("Unable to receive response");
                        return;
                    }
                    System.out.println("Response submitted!");
                    p.checkOn(response.getSupremumIudicium());
                    setChangesShowed(false);
                    System.out.println("Checked! For the " + p.getX() + " " + p.getY() + " it is " + response.getSupremumIudicium());
                });
                if (!changesShowed){
                    lab4.redrawPontos();
                    changesShowed = true;
                }

            } catch (ConcurrentModificationException e){
                System.out.println("Collection changed until iterating");
            }
        }// while
    }

    private void setChangesShowed(boolean value){
        changesShowed = value;
    }

    private void tryConnect(){
        assert(!socket.isConnected());
        boolean connected = false;
        boolean firstTry = true;
        do{
            if (!firstTry){
                try{
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                firstTry = false;
            }
            socket = new Socket();
            try {
                System.out.println("Trying to connect to "+socketAddress+" ...");
                try {
                    socket.connect(socketAddress, 2000);
                    connected = true;
                } catch (SocketTimeoutException e){
                    System.out.println("Connection timed out...");
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        } while(!connected);
        System.out.println("Connected!");
    }
}
