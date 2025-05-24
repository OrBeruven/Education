import java.util.function.Consumer;

public class ViewWindowExtendsCallback<T> extends Callback<T> {
    public ViewWindowExtendsCallback(Consumer<T> notifyFunc, Runnable notifyDeathFunc) {
        super(notifyFunc, notifyDeathFunc);
    }
}
