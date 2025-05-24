/***************************
 *  Written by : Or
 *  Reviewer : Harel
 *  Date : 13.08.2023
 *  Description : Single thread - asynchronous server which accepts
 *              TCP and UDP connection. receives "ping" and returns "pong".
 ***************************/
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.nio.charset.StandardCharsets;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Set;
import java.util.logging.FileHandler;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

public class PingPongServer {
    private static final int PORT_UDP = 9090;
    private static final int PORT_TCP = 8080;
    private static final String MSG = "Pong\n";
    private static final Selector pingPongServer;
    private static final Logger logger = Logger.getLogger("MyLog");
    private static final FileHandler fileHandler;
    private static boolean running = true;
    private static final int TIMEOUT = 7000;

    static {
        try {
            pingPongServer = Selector.open();
            fileHandler = new FileHandler("./ServerLogFile.log");
            logger.addHandler(fileHandler);
            fileHandler.setFormatter(new SimpleFormatter());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        running = true;

        try (  DatagramChannel udpChannel = DatagramChannel.open();
             ServerSocketChannel tcpChannel = ServerSocketChannel.open() ) {

            Thread serverHandler = new ServerHandler();
            serverHandler.setDaemon(true);
            serverHandler.start();

            //Create the udp channel, and bind it to defined port
            udpChannel.socket().bind(new InetSocketAddress(PORT_UDP));
            udpChannel.configureBlocking(false);
            udpChannel.register(pingPongServer, SelectionKey.OP_READ);

            //same with the TCP channel
            tcpChannel.socket().bind(new InetSocketAddress(PORT_TCP));
            tcpChannel.configureBlocking(false);
            tcpChannel.register(pingPongServer, SelectionKey.OP_ACCEPT);

            while (running) {

                //If nothing happened for 7 seconds
                if (0 == pingPongServer.select(TIMEOUT)) {
                    logger.info("Nothing happened for 7 seconds");
                }

                Set<SelectionKey> keys = pingPongServer.selectedKeys();

                for (Iterator<SelectionKey> iterator = keys.iterator(); iterator.hasNext();) {
                    SelectionKey key = iterator.next();
                    SelectableChannel channelKey = key.channel();
                    iterator.remove();

                    if (key.isAcceptable()) {
                        tcpAccept(channelKey);
                    } else if (key.isReadable()) {
                        if (channelKey instanceof DatagramChannel) {
                            udpHandler(channelKey);
                        } else if (channelKey instanceof SocketChannel) {
                            tcpHandler(channelKey, key);
                        }
                    }
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {

            logger.info("Finished execution, closing resources and shutting down server");
            logger.removeHandler(fileHandler);
            try {
                pingPongServer.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    private static void udpHandler(SelectableChannel channelKey) throws IOException {
        DatagramChannel udpChannel = (DatagramChannel) channelKey;
        ByteBuffer buffer = ByteBuffer.allocate(256);
        SocketAddress clientAddress = udpChannel.receive(buffer);
        buffer.flip();
        String msgRead = StandardCharsets.UTF_8.decode(buffer).toString();

        synchronized (logger) {
            logger.info("Received UDP package: " + msgRead + "\nFrom : " + clientAddress);
        }
        udpChannel.send(ByteBuffer.wrap(MSG.getBytes()), clientAddress);
    }

    private static void tcpHandler(SelectableChannel channelKey, SelectionKey key) throws IOException {
        SocketChannel tcpChannel = (SocketChannel) channelKey;
        ByteBuffer buffer = ByteBuffer.allocate(256);
        try {
            if (0 < tcpChannel.read(buffer)) {
                buffer.flip();
                String msgRead = StandardCharsets.UTF_8.decode(buffer).toString();

                //System.out.println("Received TCP package: " + msgRead);
                synchronized (logger) {
                    logger.info("Received TCP package: " + msgRead + "\nFrom : " + tcpChannel.getRemoteAddress());
                }

                buffer.flip();
                tcpChannel.write(ByteBuffer.wrap(MSG.getBytes()));
            } else {
                logAndRemoveChannel(tcpChannel, key);
            }
        } catch (SocketException e) {
            logAndRemoveChannel(tcpChannel, key);
        }
    }

    private static void tcpAccept(SelectableChannel channel) throws IOException {
        ServerSocketChannel serverSocketChannel = (ServerSocketChannel) channel;
        SocketChannel clientTCPChannel = serverSocketChannel.accept();
        clientTCPChannel.configureBlocking(false);
        clientTCPChannel.register(pingPongServer, SelectionKey.OP_READ);
    }

    private static void logAndRemoveChannel(SocketChannel channel, SelectionKey key) throws IOException {
        synchronized (logger) {
            logger.info("TCP Connection Died");
        }
        channel.close();
        key.cancel();
    }

    private static class ServerHandler extends Thread {
        Scanner scanner = new Scanner(System.in);
        @Override
        public void run() {
            while (!scanner.nextLine().equals("quit"));

            running = false;
            synchronized (logger) {
                logger.info("Server is quiting, finishing tasks");
            }
        }
    }
}