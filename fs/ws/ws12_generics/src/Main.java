import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

public class Main {
    /*public static void main(String[] args) {
        ArrayList<? super Object> v = new ArrayList<>();
        v.add("test");
        Integer i = (Integer)v.get(0);

        List<Object> l = new ArrayList<>();
        List c = l;

    }*/

    /*public static void foo(List<Object> l) {
        System.out.println(l.get(0));
    }*/

    //public <U extends B1 & B3 & B2> void foo2();

    class B1 {
        /**/
    }

    interface B2 {
        /**/
    }

    class B3 {
        /**/
    }

    class TypePar<T> {
        T a;
        //static T b; error
    }


    //public void print(Set<String> stringSet) {};
    //public void print(Set<Integer> integerSet) {};

    public void Ex24() {
        List<Object> objectList;
        List<String> stringList = null;
        //objectList = (List<Object>)stringList;
    }

    public static void main(String[] args) {
        List rawList;
        List<?> listOfAnyType = null;
        List<Object> listOfObject = new ArrayList<Object>();
        List<String> listOfString = new ArrayList<String>();
        List<Integer> listOfInteger = new ArrayList<Integer>();

        rawList = listOfAnyType;
        rawList = listOfString;
        rawList = listOfInteger;

        listOfAnyType = listOfString;
        listOfAnyType = listOfInteger;
        //listOfObject = (List<Object>) listOfString;
    }
}