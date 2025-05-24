/**********************************
 * @Author: Or Beruven
 * @Reviewer: Daniel Wurtzel
 * @Date: 30.7.23
 * @Description: DataModel for tests, implements as Model in MVC design.
 * holds data and data operation for controller's use.
 */
import java.util.ArrayList;
import java.util.List;

public class DataModel {
    List<String> list = new ArrayList<>();
    Controller controller = null;

    public String getMsg(int index) {
        return this.list.get(index);
    }

    public void addAndSendMsg(String msg) {
        if (msg.equals("publish")) {
            controller.dispatcher.notifyAll(list.toString());
            return;
        }
        list.add(msg);
    }

    public void stopAll() {
        this.controller.dispatcher.stop();
    }
}
