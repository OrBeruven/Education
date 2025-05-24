import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketException;
import java.nio.channels.DatagramChannel;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.util.Set;

public class Main {
    public static void main(String[] args) throws IOException {
        DatagramPacket packet = new DatagramPacket(new byte[256], 256);
        DatagramSocket datagramSocket = new DatagramSocket(8080);
        DatagramChannel channel = DatagramChannel.open();
        channel.bind(new InetSocketAddress(8080));
        channel.configureBlocking(false);


        Selector selector = Selector.open();
        channel.register(selector, SelectionKey.OP_READ);

        selector.select();

        Set<SelectionKey> keys = selector.selectedKeys();

        for ()

        datagramSocket.receive(packet);

        System.out.println("Received = " + (new String(packet.getData(), 0, packet.getLength())));
    }
}