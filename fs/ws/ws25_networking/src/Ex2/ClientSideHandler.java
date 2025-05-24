package Ex2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientSideHandler extends Thread {
    Socket mySocket;
    ClientSideHandler(Socket clientSocket) {
        this.mySocket = clientSocket;
    }

    @Override
    public void run() {
//        BufferedReader inputReader = null;
//        try {
//            inputReader = new BufferedReader(new InputStreamReader(mySocket.getInputStream()));
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }
//        PrintWriter outputWriter = new PrintWriter(clientSocket.getOutputStream(), true);
//
//        // Handle client communication here
//        String message;
//        while (true) {
//            try {
//                if ((message = inputReader.readLine()) == null) break;
//            } catch (IOException e) {
//                throw new RuntimeException(e);
//            }
//            System.out.println("Received from client: " + message);
//        }
//
//        // Close the resources when done
//        try {
//            inputReader.close();
//            mySocket.close();
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }
    }
}
