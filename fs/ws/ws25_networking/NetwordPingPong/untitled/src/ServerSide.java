/***************************
 *  Written by : Or
 *  Reviewer : Lilach
 *  Date : 06.08.2023
 *  Description : Socket Ping-Pong, server side implementation using
 *                TCP mechanism.
 ***************************/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerSide {
    private static final int PORT = 13243;
    private static final int NUM_OF_PINGS = 10;
    private static boolean running = true;
    public static void main(String[] args) throws IOException {
        running = true;
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            Socket clientSocket = serverSocket.accept();
            while (running) {
                BufferedReader reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                String line = reader.readLine();

                if (line.equals("end")) {
                    running = false;
                    continue;
                }

                System.out.println(line);
                PrintWriter writer = new PrintWriter(clientSocket.getOutputStream(), true);
                writer.println("Pong");
            }
        }
    }
}
