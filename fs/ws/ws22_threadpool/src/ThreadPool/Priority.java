/************************************************
 *  Thread Pool Priority enum for user's use    *
 *                                              *
 *  Developer: Or Beruven                       *
 *  Reviewer: Nir                               *
 *  Date: 23.07.2023                            *
 ***********************************************/
package ThreadPool;

public enum Priority implements ThreadPoolPriorityI {
    LOW(1),
    DEFAULT(5),
    HIGH(10);

    private int priorityNumber = 0;
    Priority(int priority) {
        this.priorityNumber = priority;
    }

    @Override
    public int getPriority() {
        return this.priorityNumber;
    }
}
