package ThreadPool;

enum DeveloperPriority implements ThreadPoolPriorityI {
    DEV_LOW(0),
    DEV_HIGH(11);

    private int priorityNumber = 0;
    DeveloperPriority(int priority) {
        this.priorityNumber = priority;
    }

    @Override
    public int getPriority() {
        return this.priorityNumber;
    }
}
