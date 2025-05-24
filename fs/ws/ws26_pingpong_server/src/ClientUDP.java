/***************************
 *  Written by : Or
 *  Reviewer : Harel
 *  Date : 13.08.2023
 *  Description : UDP Client who sends Ping to localhost server
 *                with port 8080, and anticipate Pong from server
 ***************************/
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class ClientUDP {
    private static final int PORT_UDP = 3456;
    public static void main(String[] args) {
        String send = "Ping";

        try (DatagramSocket socket = new DatagramSocket()) {
            InetAddress address = InetAddress.getByName("localhost");
            DatagramPacket packet = new DatagramPacket(send.getBytes(), send.length(), address, PORT_UDP);

            byte[] received = new byte[4];
            for (int i = 0; i < 5; ++i) {
                socket.send(packet);

                DatagramPacket receivedPackage = new DatagramPacket(received, received.length);
                socket.receive(receivedPackage);
                System.out.println(new String(received));

                Thread.sleep(1000);
            }

        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
