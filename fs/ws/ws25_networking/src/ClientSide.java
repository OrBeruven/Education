/***************************
 *  Written by : Or
 *  Reviewer : Lilach
 *  Date : 06.08.2023
 *  Description : Socket Ping-Pong, client side implementation using
 *                TCP mechanism.
 ***************************/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientSide {
    public static final int PORT = 13243;
    public static final int NUM_OF_PONGS = 10;


    public static void main(String[] args) {
        try (Socket socket = new Socket("localhost", PORT)) {
            PrintWriter printWriter = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            for (int i = 0; i < NUM_OF_PONGS; ++i) {
                printWriter.println("Ping");
                Thread.sleep(500);

                String line = reader.readLine();
                System.out.println(line);

                Thread.sleep(500);
            }

            printWriter.println("end");

        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
