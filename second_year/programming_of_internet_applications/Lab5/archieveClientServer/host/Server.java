package host;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static void main(String[] args) {
        ServerSocket servers = null;

        try {
            servers = new ServerSocket(4444);
        } catch (IOException e) {
            System.out.println("Couldn't listen to port 4444");
            System.exit(-1);
        }

        Socket fromclient = null;
        try {
            System.out.print("Waiting for a client...");
            fromclient= servers.accept();
            System.out.println("Client connected");
        } catch (IOException e) {
            System.out.println("Can't accept");
            System.exit(-1);
        }

        BufferedReader in = null;
        PrintWriter out;

        String input,output;

        try {
            in = new BufferedReader(new
                    InputStreamReader(fromclient.getInputStream()));
            out = new PrintWriter(fromclient.getOutputStream(), true);

            System.out.println("Wait for messages");
            while ((input = in.readLine()) != null) {
                out.println(input+input.length());
                System.out.println(input);
            }
            out.close();
            in.close();
            fromclient.close();
            servers.close();
        } catch (IOException e){
            System.out.println("Can't connect to client");
            System.exit(-1);
        }
    }
}
