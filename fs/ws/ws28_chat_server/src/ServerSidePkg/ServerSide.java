package ServerSidePkg;

import java.io.IOException;
import java.net.SocketAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.nio.channels.spi.AbstractSelectableChannel;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.function.Consumer;
import java.util.logging.FileHandler;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

/****************************
 *  Written by : Or         *
 *  Reviewer : Harel        *
 *  Date : 13.08.2023       *
 ****************************/


/****************************** Description ******************************
 *   : Infrastructure for Single thread - asynchronous server which accepts
 *                connection. generic implementation for all protocols.
 *************************************************************************/
public class ServerSide implements Runnable {
    private final Selector serverSelector;
    private final Logger logger = Logger.getLogger("MyLog");
    private final FileHandler fileHandler;
    private boolean running = true;
    private static final int TIMEOUT = 7000;
    private final Map<AbstractSelectableChannel, IPeer> channelToPeerMap = new HashMap<>();

    {
        try {
            serverSelector = Selector.open();
            fileHandler = new FileHandler("./ServerLogFile.log");
            logger.addHandler(fileHandler);
            fileHandler.setFormatter(new SimpleFormatter());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void run() {
        try {
            while (running) {

                //If nothing happened for 7 seconds
                serverSelector.select();

                Set<SelectionKey> keys = serverSelector.selectedKeys();

                for (Iterator<SelectionKey> iterator = keys.iterator(); iterator.hasNext(); ) {
                    SelectionKey key = iterator.next();
                    SelectableChannel channelKey = key.channel();
                    iterator.remove();

                    if (key.isAcceptable()) {
                        acceptTCPChannel(key);
                    } else if (key.isReadable()) {
                        ((Consumer<IPeer>) key.attachment()).accept(channelToPeerMap.get(channelKey));
                    }
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            logger.info("Finished execution, closing resources and shutting down server");
            fileHandler.close();
            logger.removeHandler(fileHandler);
            try {
                for (IPeer peer : channelToPeerMap.values()) {
                    peer.close();
                }
                serverSelector.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    public void register(Object channel, Consumer<IPeer> handler) throws IOException {
        if (channel instanceof AbstractSelectableChannel abstractSelectableChannel) {
            IPeer channelPeer = null;
            abstractSelectableChannel.configureBlocking(false);

            if (channel instanceof ServerSocketChannel serverSocketChannel) {
                abstractSelectableChannel.register(serverSelector, SelectionKey.OP_ACCEPT, handler);
                return;
            }

            SelectionKey key = abstractSelectableChannel.register(serverSelector, SelectionKey.OP_READ, handler);
            if (channel instanceof SocketChannel socketChannel) {
                channelPeer = new TCPPeer(socketChannel, key);
            } else if (channel instanceof DatagramChannel datagramChannel) {
                channelPeer = new UDPPeer(datagramChannel);
            }
            channelToPeerMap.put(abstractSelectableChannel, channelPeer);
        } else {
            throw new IllegalArgumentException("Invalid Channel type");
        }
    }

    public void stop() {
        running = false;
        serverSelector.wakeup();
    }

    private void acceptTCPChannel(SelectionKey key) throws IOException {
        ServerSocketChannel serverSocketChannel = (ServerSocketChannel) key.channel();
        SocketChannel clientTCPChannel = serverSocketChannel.accept();
        clientTCPChannel.configureBlocking(false);
        //SelectionKey newKey = clientTCPChannel.register(serverSelector, SelectionKey.OP_READ, key.attachment());
        //channelToPeerMap.put(clientTCPChannel, new TCPPeer(clientTCPChannel, newKey));

        register(clientTCPChannel, (Consumer<IPeer>) key.attachment());
    }

    private class TCPPeer implements IPeer {
        private final SocketChannel tcpChannel;
        private final SelectionKey key;

        private TCPPeer(SocketChannel tcpChannel, SelectionKey key) {
            this.tcpChannel = tcpChannel;
            this.key = key;
        }

        @Override
        public byte[] read(int bytesToRead) {
            ByteBuffer buffer = ByteBuffer.allocate(bytesToRead);
            byte[] bytes = null;

            try {
                try {
                    tcpChannel.read(buffer);
                    buffer.flip();
                    bytes = new byte[buffer.limit()];
                    buffer.get(bytes);
                } catch (SocketException e) {
                    tcpChannel.close();
                    key.cancel();
                    return "Socket Disconnected".getBytes();
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            return bytes;
        }

        @Override
        public void write(byte[] data) {
            if (!key.isValid()) {
                return;
            }
            try {
                tcpChannel.write(ByteBuffer.wrap(data));
            } catch (IOException e) {
                if (!e.getMessage().equals("Broken pipe")) {
                    throw new RuntimeException(e);
                }
            }
        }

        @Override
        public void close() {
            try {
                tcpChannel.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    private class UDPPeer implements IPeer {
        private final DatagramChannel udpChannel;
        private SocketAddress connectAddress = null;

        private UDPPeer(DatagramChannel udpChannel) {
            this.udpChannel = udpChannel;
        }

        @Override
        public byte[] read(int bytesToRead) {
            ByteBuffer buffer = ByteBuffer.allocate(bytesToRead);
            try {
                connectAddress = udpChannel.receive(buffer);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            buffer.flip();
            return StandardCharsets.UTF_8.decode(buffer).toString().getBytes();
        }

        @Override
        public void write(byte[] data) {
            try {
                udpChannel.send(ByteBuffer.wrap(data), connectAddress);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        @Override
        public void close() {
            try {
                udpChannel.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
