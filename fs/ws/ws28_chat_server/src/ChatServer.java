/****************************
 *  @Author : Or         *
 *  @Reviewer : Aviv        *
 *  @Date : 21.08.2023       *
 ****************************/


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

import ServerSidePkg.*;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.ServerSocketChannel;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.function.Consumer;

public class ChatServer {
    private static final int PORT_TCP = 8787;
    private static final Map<String, IPeer> clientToPeerMap = new HashMap<>();
    private static final Map<String, Command> commandMap = new HashMap<>();

    @FunctionalInterface
    private interface Command {
        void runCommand(String[] command, IPeer peer);
    }

    public static void main(String[] args) throws IOException {
        ServerSide serverSide = new ServerSide();
        initCommands();

        try (ServerSocketChannel tcpChannel = ServerSocketChannel.open()) {
            tcpChannel.bind(new InetSocketAddress(PORT_TCP));
            tcpChannel.configureBlocking(false);

            serverSide.register(tcpChannel, new ClientHandler());

            Thread serverThread = new Thread(serverSide);
            serverThread.start();

            Scanner scanner = new Scanner(System.in);
            while (!scanner.nextLine().equals("quit")) ;
            serverSide.stop();
        }
    }

    private static class ClientHandler implements Consumer<ServerSidePkg.IPeer> {
        @Override
        public void accept(IPeer iPeer) {
            byte[] msg = iPeer.read(256);
            if (null == msg) {
                return;
            }
            String strMsg = new String(msg);
            strMsg = strMsg.trim();
            String[] split = strMsg.split(" ");

            Command command = getCommand(split[0]);
            if (null == command) {
                invalidCommand(iPeer);
            } else {
                command.runCommand(split, iPeer);
            }
        }
    }

    private static class BM implements Command {
        @Override
        public void runCommand(String[] command, IPeer peer) {
            if (!checkPermission(command[1], peer)) {
                return;
            }

            for (Map.Entry<String, IPeer> entry : clientToPeerMap.entrySet()) {
                if (!entry.getKey().equals(command[1])) {
                    String msg = "From " + command[1] + " : " +
                            combineArrayToString(command, 2, command.length - 1);

                    entry.getValue().write(msg.getBytes());
                }
            }
        }
    }

    private static class PM implements Command {
        @Override
        public void runCommand(String[] command, IPeer peer) {
            if (!checkPermission(command[1], peer)) {
                return;
            }

            if (command.length < 3 || !clientToPeerMap.containsKey(command[2])) {
                peer.write("Can't find receiver".getBytes());
                return;
            }

            for (Map.Entry<String, IPeer> entry : clientToPeerMap.entrySet()) {
                if (entry.getKey().equals(command[2])) {
                    String msg = "Whisper From " + command[1] + " : " +
                            combineArrayToString(command, 3, command.length - 1);

                    entry.getValue().write(msg.getBytes());
                    break;
                }
            }
        }
    }

    private static class REG implements Command {
        @Override
        public void runCommand(String[] command, IPeer peer) {
            if (clientToPeerMap.containsKey(command[1]) || clientToPeerMap.containsValue(peer)) {
                peer.write("Registered Unsuccessful".getBytes());
                return;
            }

            clientToPeerMap.put(command[1], peer);
            peer.write("Registered successfully".getBytes());
        }
    }

    private static class LOGOUT implements Command {

        @Override
        public void runCommand(String[] command, IPeer peer) {
            if (!checkPermission(command[1], peer)) {
                return;
            }

            clientToPeerMap.remove(command[1]);
            peer.close();
        }
    }

    private static String combineArrayToString(String[] array, int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex >= array.length || startIndex > endIndex) {
            throw new IllegalArgumentException("Invalid start or end index");
        }

        StringBuilder combinedString = new StringBuilder();
        combinedString.append(array[startIndex]);

        for (int i = startIndex + 1; i <= endIndex; ++i) {
            combinedString.append(" ");  // Add a space between strings
            combinedString.append(array[i]);
        }

        return combinedString.toString();
    }

    private static void initCommands() {
        commandMap.put("BM", new BM());
        commandMap.put("PM", new PM());
        commandMap.put("REG", new REG());
        commandMap.put("LOGOUT", new LOGOUT());
    }

    private static Command getCommand(String command) {
        return commandMap.getOrDefault(command, null);
    }

    private static void invalidCommand(IPeer peer) {
        peer.write("Invalid Command".getBytes());
    }

    private static boolean checkPermission(String senderName, IPeer senderIPeer) {

        if (clientToPeerMap.containsKey(senderName) && clientToPeerMap.get(senderName).equals(senderIPeer)) {
            return true;
        }

        senderIPeer.write("Not your name".getBytes());
        return false;
    }
}


