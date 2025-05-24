/**********************************
 * @Author: Or Beruven
 * @Reviewer: Daniel Wurtzel
 * @Date: 30.7.23
 * @Description: Callback class extends AbstractCallback, implements default implementation
 * and makes as template for classes to extend, and add user functions (alien functions).
 */
import java.util.function.Consumer;

public class Callback<T> extends Dispatcher.AbstractCallback<T> {
    private final Dispatcher<T> dispatcher = null;
    private Consumer<T> notifyFunc = null;
    private Runnable notifyDeathFunc = null;

    public Callback(Consumer<T> notifyFunc, Runnable notifyDeathFunc) {
        this.notifyFunc = notifyFunc;
        this.notifyDeathFunc = notifyDeathFunc;
    }

    public void update(T msg) {
        this.notifyFunc.accept(msg);
    }

    public void updateOnDeath() {
        this.notifyDeathFunc.run();
    }
}
