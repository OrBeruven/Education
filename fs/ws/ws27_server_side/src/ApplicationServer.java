import ServerSidePkg.*;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.DatagramChannel;
import java.nio.channels.ServerSocketChannel;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;
import java.util.function.Consumer;

public class ApplicationServer {
    private static final int PORT_UDP = 3456;
    private static final int PORT_TCP = 8080;
    public static void main(String[] args) throws IOException {
        ServerSide serverSide = new ServerSide();

        try (DatagramChannel datagramChannel = DatagramChannel.open();
            ServerSocketChannel tcpChannel = ServerSocketChannel.open();
            Scanner scanner = new Scanner(System.in)) {

            datagramChannel.bind(new InetSocketAddress(PORT_UDP));
            datagramChannel.configureBlocking(false);

            tcpChannel.bind(new InetSocketAddress(PORT_TCP));
            tcpChannel.configureBlocking(false);

            serverSide.register(datagramChannel, new SendPong());
            serverSide.register(tcpChannel, new SendPong());

            Thread serverThread = new Thread(serverSide);
            serverThread.start();

            while (!scanner.nextLine().equals("quit"));
            serverSide.stop();
        }
    }
}

class SendPong implements Consumer<IPeer> {
    @Override
    public void accept(IPeer iPeer) {
        byte[] ping = iPeer.read(4);

        if (new String(ping).equals("Ping")) {
            System.out.println("Ping");
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            iPeer.write("Pong".getBytes(StandardCharsets.UTF_8));
        }
    }
}

