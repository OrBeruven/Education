/**********************************
 * @Author: Or Beruven
 * @Reviewer: Daniel Wurtzel
 * @Date: 30.7.23
 * @Description: Dispatcher class enables registrations of AbstractCallback instances.
 * An application calling the Dispatcher's notifyAll or notifyNClients methods,
 * causes all of its AbstractCallback instances to be notified with a given message.
 */
import java.util.ArrayList;
import java.util.List;

public class Dispatcher<T> {
    private final List<AbstractCallback<T>> callbackList = new ArrayList<>();

    public static abstract class AbstractCallback<V>{
        private Dispatcher<V> dispatcher = null;

        public abstract void update(V msg);

        public abstract void updateOnDeath();

        public final void stop() {
            dispatcher.removeCallback(this);
        }
    }

    public void addCallback(AbstractCallback<T> callback) {
        callback.dispatcher = this;
        synchronized (this.callbackList) {
            callbackList.add(callback);
        }
    }

    public boolean removeCallback(AbstractCallback<T> callback) {
        boolean removeValue = false;
        synchronized (this.callbackList) {
            removeValue = this.callbackList.remove(callback);
        }

        return removeValue;
    }

    public void notifyAll(T msg) {
        List<AbstractCallback<T>> copyMailingList = null;
        synchronized (this.callbackList) {
            copyMailingList = new ArrayList<>(this.callbackList);
        }

        for (AbstractCallback<T> callback : copyMailingList) {
            callback.update(msg);
        }
    }

    public void stop() {
        for (AbstractCallback<T> callback : this.callbackList) {
            callback.updateOnDeath();
        }

        this.callbackList.clear();
    }
}