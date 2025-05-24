import java.util.function.Consumer;

public class ViewWindowFunctions<T> extends Dispatcher.AbstractCallback<T>{
    private final Consumer<T> notifyFunc;
    private final Runnable notifyDeathFunc;

    public ViewWindowFunctions(Consumer<T> notifyFunc, Runnable notifyDeathFunc) {
        this.notifyDeathFunc = notifyDeathFunc;
        this.notifyFunc = notifyFunc;
    }

    @Override
    public void update(T msg) {
        notifyFunc.accept(msg);
    }

    @Override
    public void updateOnDeath() {
        notifyDeathFunc.run();
    }
}
