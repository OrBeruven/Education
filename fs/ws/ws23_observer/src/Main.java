import java.util.function.Consumer;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        DataModel dataModel = new DataModel();
        Controller controller = new Controller(dataModel);

        ViewWindow<String> viewWindow = new ViewWindow<>();
        ViewWindow2<String> viewWindow2 = new ViewWindow2<>();
        ViewWindow3<String> viewWindow3 = new ViewWindow3<>();
        ViewWindow4<String> viewWindow4 = new ViewWindow4<>();
        ViewWindow4<String> viewWindow5 = new ViewWindow4<>();
        ViewWindowFunctions<String> viewWindowFunctions = new ViewWindowFunctions<>(new HandleMsg(), () -> {
            System.out.println("notifyOnDeathFunc has been invoked");
        });

        ViewWindowExtendsCallback<String> viewWindowExtendsCallback = new ViewWindowExtendsCallback(new HandleMsg(), () -> {
            System.out.println("notifyOnDeathFunc has been invoked"); });

        controller.addSubscriber(viewWindow);
        controller.addSubscriber(viewWindow2);
        controller.addSubscriber(viewWindow3);
        controller.addSubscriber(viewWindow4);
        controller.addSubscriber(viewWindow5);
        controller.addSubscriber(viewWindowFunctions);
        controller.addSubscriber(viewWindowExtendsCallback);

        dataModel.addAndSendMsg("Moishale");
        dataModel.addAndSendMsg("Nir Haefes");
        dataModel.addAndSendMsg("publish");
        dataModel.addAndSendMsg("Or");
        dataModel.addAndSendMsg("Neviu");
        dataModel.addAndSendMsg("Mor");
        dataModel.addAndSendMsg("publish");
        dataModel.addAndSendMsg("Evgenii");
        dataModel.addAndSendMsg("publish");
        dataModel.addAndSendMsg("Aviv");
        dataModel.addAndSendMsg("Lilach");
        dataModel.addAndSendMsg("FS139-140");
        dataModel.addAndSendMsg("FS139-140");
        dataModel.stopAll();

        dataModel.addAndSendMsg("publish");
    }

    static class BroadCast extends Thread {
        Dispatcher<String> controlWindow = null;

        BroadCast(Dispatcher<String> controlWindow) {
            this.controlWindow = controlWindow;
        }

        @Override
        public void run() {
            for (Integer i = 0; i < 12; ++ i) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }

                controlWindow.notifyAll(i.toString());
            }
        }
    }

    static class AddCall extends Thread {
        Dispatcher<String> controlWindow = null;

        AddCall(Dispatcher<String> controlWindow) {
            this.controlWindow = controlWindow;
        }

        @Override
        public void run() {
            controlWindow.addCallback(new ViewWindow3<>());
        }
    }

    static class HandleMsg implements Consumer<String> {
        @Override
        public void accept(String s) {
            if (s.contains("Neviu")) {
                System.out.println("The function notifyFunc received a msg with Neviu!!!");
                System.out.println("Happy Days");
            }
        }
    }
}
