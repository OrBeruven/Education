/***************************
 *  Written by : Or
 *  Reviewer : Lilach
 *  Date : 06.08.2023
 *  Description : Socket Ping-Pong, server side implementation using
 *                UDP mechanism.
 ***************************/
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class UdpServer {
    private static final int PORT = 12546;
    private static final DatagramSocket serverSocket;
    private static byte[] buffer = new byte[256];
    private static boolean running = true;


    static {
        try {
            serverSocket = new DatagramSocket(PORT);
        } catch (SocketException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) throws IOException {
        running = true;

        while (running) {
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
            String received = receivePackage(packet);
            if (received.equals("end")) {
                running = false;
                continue;
            }
            System.out.println(received);


            sendPackage(packet,"pong");
        }
    }

    private static String receivePackage(DatagramPacket packet) throws IOException {
        serverSocket.receive(packet);
        return new String(packet.getData(), 0, packet.getLength());
    }

    private static void sendPackage(DatagramPacket packet, String str) throws IOException {
        buffer = str.getBytes();
        InetAddress address = packet.getAddress();
        int port = packet.getPort();
        packet = new DatagramPacket(buffer, buffer.length, address, port);
        serverSocket.send(packet);
    }
}