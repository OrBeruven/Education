package GenericSLL;

public class ConcurrentModificationException extends RuntimeException {
    ConcurrentModificationException() {
        super("ConcurrentModificationException - Iterator not up to date");
    }
}