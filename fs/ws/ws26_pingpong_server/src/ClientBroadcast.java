/***************************
 *  Written by : Or
 *  Reviewer : Harel
 *  Date : 13.08.2023
 *  Description : UDP Client who broadcasts to all servers
 *                in the same LAN with port 8080
 ***************************/
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class ClientBroadcast {
    private static final int PORT_UDP = 9090;
    public static void main(String[] args) {
        String send = "Ping";

        try (DatagramSocket socket = new DatagramSocket()) {
            InetAddress address = InetAddress.getByName("10.1.255.255");
            socket.setBroadcast(true);
            DatagramPacket packet = new DatagramPacket(send.getBytes(), send.length(), address, PORT_UDP);

            byte[] received = new byte[4];
            for (int i = 0; i < 1000000; ++i) {
                socket.send(packet);

                DatagramPacket receivedPackage = new DatagramPacket(received, received.length);
                socket.receive(receivedPackage);
                System.out.println(new String(received) + " from : " + receivedPackage.getAddress().getHostAddress() + "\n");
                System.out.println(receivedPackage.getAddress().getCanonicalHostName());
                Thread.sleep(1000);
            }

        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
