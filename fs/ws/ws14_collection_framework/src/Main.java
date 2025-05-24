import java.util.*;

public class Main {
    public static void main(String[] args) {
        //Ex1();
        //Ex2();
        Main m = new Main();
        m.Ex3();
    }

    public static void Ex1() {
        int[] ints = {5, 1, 4, 3};
        System.out.println(Arrays.toString(ints));

        List<Integer> intList = new ArrayList<>(ints.length);

        for (int i : ints) {
            intList.add(i);
        }

        Collections.sort(intList);
        System.out.println(intList.toString());
    }

    public static void Ex2() {
        Map<String, Integer> days = new HashMap<>();
        days.put("Sunday", 1);
        days.put("Monday", 2);
        days.put("Tuesday", 3);
        days.put("Wednesday", 4);
        days.put("Thursday", 5);
        days.put("Friday", 6);
        days.put("Saturday", 7);

        for (Map.Entry<String, Integer> entry : days.entrySet()) {
            System.out.println("Day " + entry.getKey() + " Numbered " + entry.getValue());
        }

        for (String s : days.keySet()) {
            System.out.println("Day name : " + s);
        }

        for (Integer i : days.values()) {
            System.out.println("Number of day : " + i);
        }
    }

    public void Ex3() {
        DataObject[] dataObjects = new DataObject[3];
        int[] mem1 = {5, 5, 10, 1};
        int[] mem2 = {0};
        int[] mem3 = {1, 2, 3, 4, 5, 6, 7};
        dataObjects[0] = new DataObject("Sum21", mem1);
        dataObjects[1] = new DataObject("Sum0", mem2);
        dataObjects[2] = new DataObject("Sum28", mem3);

        Map<String, int[]> map = new HashMap<>();

        for (DataObject d : dataObjects) {
            map.put(d.getKey(), d.getValue());
        }

        for (Map.Entry<String, int[]> entry : map.entrySet()) {
            System.out.println("Name : " + entry.getKey() + " Sum : " + Arrays.stream(entry.getValue()).sum());
        }
    }

    /***********************************************
     *
     *                Ex3 Help class
     *
     * *********************************************/
    class DataObject implements Map.Entry<String, int[]>{
        private String code = null;
        private int[] members = null;

        DataObject(String code, int[] members) {
            this.code = code;
            this.members = members;
        }

        @Override
        public String getKey() {
            return this.code;
        }

        @Override
        public int[] getValue() {
            return this.members;
        }

        @Override
        public int[] setValue(int[] value) {
            return new int[0];
        }
    }
}