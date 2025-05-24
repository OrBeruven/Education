/***************************
 *  Written by : Or
 *  Reviewer : Lilach
 *  Date : 11.07.2023
 ***************************/
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Main {
    private static final int NUM_OF_THREADS = 100;
    public static void main(String[] args) throws IOException {
        //simpleCountTest();
        //printDictionary();
        performanceTest();
    }

    static void printDictionary() throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("/usr/share/dict/american-english"));
        StringBuilder buffer = new StringBuilder();
        String line = reader.readLine();

        while(null != line) {
            buffer.append(line);
            line = reader.readLine();
        }

        char[] arr = buffer.toString().toCharArray();

        char[] arr2 = CountingSort.countSort(arr, 2);
        System.out.println(arr2);
    }

    static void simpleCountTest() {
        char[] arr = new char[11];
        arr[0] = 'B';
        arr[1] = 'D';
        arr[2] = 'B';
        arr[3] = 'C';
        arr[4] = 'C';
        arr[5] = 'A';
        arr[6] = 'B';
        arr[7] = 'A';
        arr[8] = 'B';
        arr[9] = 'D';
        arr[10] = 'A';

        for (char a : arr) {
            System.out.println(a);
        }

        char[] sorted = CountingSort.countSort(arr, 10);

        System.out.println();
        System.out.println();
        for (char a : sorted) {
            System.out.println(a);
        }

        String sentence = "this is a test F asdpojapr g psdgjo[ieiw [ mo[sdkmfc [<sati gjna;kf <on foarpgznpdok zzzzzzzzzzzzzzzaaaaaaaaaazzzzzzz";
        char[] arr2 = CountingSort.countSort(sentence.toCharArray(), 2);
        System.out.println(arr2);
    }

    static void performanceTest() throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("/usr/share/dict/american-english"));
        StringBuilder buffer = new StringBuilder();
        String line = reader.readLine();

        while(null != line) {
            buffer.append(line);
            line = reader.readLine();
        }

        String bigData = new String(new char[500]).replace("\0", buffer.toString());
        for (int i = 1; i < NUM_OF_THREADS; ++i) {
            char[] arr = bigData.toCharArray();

            long startTime = System.nanoTime();
            CountingSort.countSort(arr, i);
            long endTime = System.nanoTime() - startTime;

            System.out.println((endTime/1000000));
            //System.out.println("It took " + i + " threads : " + (endTime/1000000) + "ms");
        }
    }
}
