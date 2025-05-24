public class ViewWindow4<T> extends Dispatcher.AbstractCallback<T> {
    @Override
    public void update(T msg) {
        System.out.println(this + " Printing update : " + msg.toString());
    }

    @Override
    public void updateOnDeath() {
        System.out.println("View Window got broadcast that publisher is dead");
    }
}
