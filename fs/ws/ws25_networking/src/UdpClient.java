/***************************
 *  Written by : Or
 *  Reviewer : Lilach
 *  Date : 06.08.2023
 *  Description : Socket Ping-Pong, client side implementation using
 *                UDP mechanism.
 ***************************/
import java.io.IOException;
import java.net.*;

public class UdpClient {
    private static final DatagramSocket clientSocket;
    private static final InetAddress address;
    private static byte[] buffer;
    private static final int NUL_OF_PINGPONGS = 10;
    private static final int PORT = 12546;


    static {
        try {
            clientSocket = new DatagramSocket();
        } catch (SocketException e) {
            throw new RuntimeException(e);
        }
        try {
            address = InetAddress.getByName("localhost");
        } catch (UnknownHostException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        for (int i = 0; i < NUL_OF_PINGPONGS; ++i) {
            sendPackage("ping");
            Thread.sleep(500);


            receivePackage();
            Thread.sleep(500);
        }

        sendPackage("end");
        clientSocket.close();
    }

    private static void sendPackage(String str) throws IOException {
        buffer = str.getBytes();
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, PORT);
        clientSocket.send(packet);
    }

    private static void receivePackage() throws IOException {
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        clientSocket.receive(packet);
        String received = new String(packet.getData(), 0, packet.getLength());
        System.out.println(received);
    }
}
