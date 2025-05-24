package ServerSidePkg;
public interface IPeer {
    byte[] read(int bytesToRead);
    void write(byte[] data);
    void close();
}
