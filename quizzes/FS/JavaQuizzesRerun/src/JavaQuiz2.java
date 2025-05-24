public class JavaQuiz2 {
    public static void main(String[] args) {
        Q2();
    }
    public static void Q1() {
        StringBuffer stringBuffer = new StringBuffer("This, that, etc.!");
        System.out.println(stringBuffer.replace(12, 15, "etcetera"));
    }

    public static void Q2() {
        Boolean b = null;
        System.out.println(b? true : false);
    }

}

class Point {
    private int x = 0, y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Point() {
        this(0, 0);
    }
}
