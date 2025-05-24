public enum Priority {
    LOW(1),
    DEFAULT(5),
    HIGH(10);

    int priorityNumber = 0;
    Priority(int priority) {
        this.priorityNumber = priority;
    }
}
