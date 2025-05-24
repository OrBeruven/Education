import java.sql.Array;
import java.util.ArrayList;
import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class Base {

    String s = "abc";
    Base() {
        System.out.println("Int ctor Base");
    }
    static
    {
        System.out.println("In Base static block");
    }

    {
        System.out.println("In Base init block");

    }

    public static void main(String[] args) {
        ArrayList<Integer> arr = new ArrayList<Integer>();
        arr.add(1);
        arr.add(2);
        arr.add(3);
        arr.add(4);
        System.out.println(arr.toString());
    }
}
