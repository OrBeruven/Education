public interface IPeer {
    public byte[] read();
    public void write(byte[]);
    public void close();
}

public class SelectorServerAPI {
    public void run();
    public void register(Object channel, Consumer<IPeer> handler);
    public void stop();
}
