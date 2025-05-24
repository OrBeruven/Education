/*
 *       Programmer : Or
 *       Reviewer : Neviu
 *       Date : 18.07.2023
 *       Description : WaitableQueue implementation
 */
package WaitablePQueue;
import java.time.LocalDateTime;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.TimeoutException;

/**
 Create a WaitablePQueue based on Priority Queue with synchronized
 implementation. making the data structure thread-safe on multithreaded
 program.
 @param <E> - Element type to insert to the queue
 */
public class WaitablePQueue<E> {
    private final PriorityQueue<E> PQ;
    public WaitablePQueue() {
        this.PQ = new PriorityQueue<>();
    }

    public WaitablePQueue(Comparator<? super E> cmp) {
        this.PQ = new PriorityQueue<>(cmp);
    }

    public boolean enque(E e) {
        boolean result = false;
        synchronized (this.PQ) {
            result = PQ.add(e);
            this.PQ.notify();
        }
        return result;
    }

    public E deque() throws InterruptedException {
        synchronized (this.PQ) {
            while (this.PQ.isEmpty()) {
                this.PQ.wait();
            }
            return this.PQ.poll();
        }

    }

    public E deque(long timeout) throws InterruptedException {
        long expectedEndTime = 0;

        synchronized (this.PQ) {
            while (this.PQ.isEmpty() && timeout > 0) {
                expectedEndTime = LocalDateTime.now().plusNanos(timeout).getNano();
                this.PQ.wait(timeout);
                timeout = expectedEndTime - LocalDateTime.now().getNano();
            }
            return PQ.poll();
        }
    }

    public boolean remove(Object o){
        synchronized (this.PQ) {
            return PQ.remove(o);
        }
    }

    public boolean isEmpty() {
        synchronized (this.PQ) {
            return PQ.isEmpty();
        }
    }
}