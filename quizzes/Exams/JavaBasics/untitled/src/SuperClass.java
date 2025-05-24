public class SuperClass {
    int intSuperClass = 10;

    static {
        System.out.println("1 static initializer called of SuperClass");
    }

    {
        System.out.println("1 instance initializer called of SuperClass");
        System.out.println(intSuperClass);
    }
    public SuperClass() {
        System.out.println("constructor called of SuperClass");
        intSuperClass *= 2;
        System.out.println(intSuperClass);
    }

    static {
        System.out.println("2 static initializer called of SuperClass");
    }

    {
        System.out.println("2 instance initializer called of SuperClass");
    }
}
