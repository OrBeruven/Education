/**********************************
 * @Author: Or Beruven
 * @Reviewer: Daniel Wurtzel
 * @Date: 30.7.23
 * @Description: Controller for tests, implements as Controller in MVC design.
 * used for communication between the DataModel and ViewWindows.
 */
public class Controller {
    Dispatcher<String> dispatcher = new Dispatcher<>();
    DataModel dm = null;

    Controller(DataModel dm) {
        this.dm = dm;
        this.dm.controller = this;
    }

    public void addSubscriber(Dispatcher.AbstractCallback<String> callback) {
        dispatcher.addCallback(callback);
    }

    public boolean removeSubscriber(Dispatcher.AbstractCallback<String> callback) {
        return dispatcher.removeCallback(callback);
    }

    public void broadcast(int index) {
        dispatcher.notifyAll(dm.getMsg(index));
    }
}
