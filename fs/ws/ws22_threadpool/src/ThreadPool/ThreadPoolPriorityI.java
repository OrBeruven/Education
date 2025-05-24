package ThreadPool;
interface ThreadPoolPriorityI {
    default int comparePriority(ThreadPoolPriorityI o) {
        return o.getPriority() - this.getPriority();
    }
    int getPriority();
}
