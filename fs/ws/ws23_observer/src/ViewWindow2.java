public class ViewWindow2<T> extends Dispatcher.AbstractCallback<T> {
    int counter = 0;
    @Override
    public void update(T msg) {
        if (1 == counter) {
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
