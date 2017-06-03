package net;

import jswing.GeneralSilhouette;
import jswing.Ponto;
import jswing.Silhouette;

import java.net.Socket;

public class ClientProcess implements Runnable{
    private Socket socket;
    private Request request;

    public ClientProcess(Socket socket, Request request){
        this.socket = socket;
        this.request = request;
    }

    @Override
    public void run() {
        double X = request.getX();
        double Y = request.getY();
        double R = request.getR();

        System.out.println("[Server] Checking ponto in request...");
        boolean supremumIudicium = new GeneralSilhouette(R).checkPonto(new Ponto(X,Y));
        Response response = new Response(supremumIudicium);

        Channel.sendResponse(response, socket);
    }
}
