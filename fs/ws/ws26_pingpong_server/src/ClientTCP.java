/***************************
 *  Written by : Or
 *  Reviewer : Harel
 *  Date : 13.08.2023
 *  Description : TCP Client who request connection to localhost server
 *                with port 8080, send Ping and anticipate Pong from server
 ***************************/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientTCP {
    private static final int PORT_TCP = 8080;
    public static final int NUM_OF_PONGS = 3;

    public static void main(String[] args) {
        try (Socket socket = new Socket("localhost", PORT_TCP);
             PrintWriter printWriter = new PrintWriter(socket.getOutputStream(), true);
             BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

            for (int i = 0; i < NUM_OF_PONGS; ++i) {
                printWriter.println("Ping");
                Thread.sleep(500);

                char[] buffGet = new char[4];
                reader.read(buffGet, 0, 4);
                System.out.println(new String(buffGet));

                Thread.sleep(500);
            }
        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
