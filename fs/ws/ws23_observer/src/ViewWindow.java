public class ViewWindow<T> extends Dispatcher.AbstractCallback<T> {
    private int counter = 0;
    @Override
    public void update(T msg) {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        if (3 == counter) {
            this.stop();
            return;
        } else {
            ++counter;
        }
        System.out.println(this + " Printing update : " + msg.toString());
    }

    @Override
    public void updateOnDeath() {
        System.out.println("View Window got broadcast that publisher is dead");
    }
}
