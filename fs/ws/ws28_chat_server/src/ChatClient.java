import java.io.*;
import java.net.Socket;
import java.util.HashSet;
import java.util.Scanner;

/***************************
 *  Written by : Or
 *  Reviewer : Aviv
 *  Date : 21.08.2023
 *  Description : TCP Client who request connection to localhost chat server
 *                with port 8787. using the network API established by the chat server
 ***************************/

/****************************** Description ******************************
 *   Chat server that waiting for connection from chat client on port 8787,
 *   the API is provided using documentation - Network chat API as follows :
 * @Register -  Register client to the chat with specific name identifier.
 *              template : "REG ClientName"
 *
 * @Broadcast - Sends message to all clients connected to chat.
 *              template : "BM SenderName message"
 *
 * @PrivateMsg - Sends private message to a specific client in that chat server.
 *              template : "PM SenderName ReceiverName message"
 *
 * @Logout -    Exits the chat server and disconnecting the name from database.
 *              template : "LOGOUT ClientName"
 *************************************************************************/
public class ChatClient {
    private static final int PORT_TCP = 8787;
    private static boolean running = true;
    private static PrintWriter printWriter = null;
    private static BufferedReader reader = null;
    private static Socket socketRef = null;
    public static void main(String[] args) {
        running = true;
        try (Socket socket = new Socket("localhost", PORT_TCP);
             InputStream input = socket.getInputStream();
             OutputStream output = socket.getOutputStream()) {

            socketRef = socket;
            printWriter = new PrintWriter(output, true);
            reader = new BufferedReader(new InputStreamReader(input));

            Thread readFromServer = new Thread(new read());
            Thread writeToServer = new Thread(new write());

            readFromServer.start();
            writeToServer.start();

            readFromServer.join();
            writeToServer.join();

        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    private static class read implements Runnable {
        @Override
        public void run() {
            while (running) {
                char[] buffGet = new char[256];
                int byteRead = -1;
                try {
                    if (-1 != (byteRead = reader.read(buffGet, 0, buffGet.length))){
                        System.out.println(new String(buffGet, 0, byteRead));
                    }
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    private static class write implements Runnable {
        @Override
        public void run() {
            Scanner scanner = new Scanner(System.in);
            String command = scanner.nextLine();

            while (!command.equals("quit")) {
                printWriter.println(command);
                command = scanner.nextLine();
            }

            running = false;
            try {
                socketRef.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
