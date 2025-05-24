public class JavaQuiz3 {
    String s = "abc";

    public JavaQuiz3() {
        System.out.println("Constructor called");
    }

    static {
        System.out.println("static called");
    }

    {
        System.out.println("instance called");
    }

    public static void main(String[] args) {
        new JavaQuiz3();
        new JavaQuiz3();
    }
}
