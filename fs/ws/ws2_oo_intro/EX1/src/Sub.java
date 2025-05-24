public class Sub extends Base{
    static int st1;
    static int st2;
    int in3;
    int in4;

    static
    {
        System.out.println("In Sub static block before ctor");
        st1 = 1;
        st2 = 2;
    }

    {
        System.out.println("In Sub init block before ctor");
        in3 = 3;
        in4 = 4;
    }
    Sub() {
        System.out.println("Int ctor Sub");
    }

    static int st5;
    static int st6;
    int in7;
    int in8;

    static
    {
        System.out.println("In Sub static block after ctor");
        st5 = 5;
        st6 = 6;
    }

    {
        System.out.println("In Sub init block after ctor");
        in7 = 7;
        in8 = 8;
    }
}
