/*****************************
 * Writer: Harel
 * Reviewer: Or
 * Date: 11/07/23
 * Counting Sort Multi - Threaded
 *****************************/

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

public class HarelReview {
    public static char[] readFile(String filePath) throws IOException {
        FileReader reader = null;
        int countCharsInDictionary = 0;
        try {
            File file = new File(filePath);
            reader = new FileReader(file);
            BufferedReader br = new BufferedReader(reader);
            int temp = 0;
            while ((temp = br.read()) != -1){
                if (temp != '\n') {
                    ++countCharsInDictionary;
                }
            }

            file = new File(filePath);
            reader = new FileReader(file);
            char[] dictionary = new char[countCharsInDictionary];
            br = new BufferedReader(reader);
            int i = 0;
            temp = 0;
            while ((temp = br.read()) != -1){
                if(temp != '\n'){
                    dictionary[i] = (char)temp;
                    ++i;
                }
            }
            return dictionary;

        } finally {
            if (reader != null) {
                reader.close();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {

        try {
            char[] dictionary = readFile("/usr/share/dict/american-english");


            for (int i = 1 ; i < 100 ; ++i){

                char []bigData = initBigData(dictionary);

                //System.out.println("For " + i + " Threads:");
                long startTime = System.currentTimeMillis();
                CountingSortHarel.countSort(bigData, i);
                System.out.println((System.currentTimeMillis() - startTime ));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static char[] initBigData(char []dictionary){

        char []bigData = new char[dictionary.length * 10000];

        for (int k = 0 , j = 0; k < bigData.length ; ++k, ++j){
            if (j + 1 == dictionary.length) {
                j = 0;
            }
            bigData[k] = dictionary[j];
        }
        return bigData;
    }
}


class CountingSortHarel{
    static final Object monitor = new Object();
    static int []countingHash = new int[256];

    public static void countSort(char[] arr, int numOfThreads) throws InterruptedException {
        Arrays.fill(countingHash, (char) 0);
        Thread []threads = new Thread[numOfThreads];

        for (int i = 0; i < numOfThreads; ++i) {
            int start = i * (arr.length / numOfThreads);
            int stop = (i + 1) * (arr.length / numOfThreads);
            if (i == numOfThreads - 1) {
                stop = arr.length;
            }
            threads[i] = new sortingThread(arr, start, stop);
            threads[i].start();
        }

        for (Thread thread : threads){
            thread.join();
        }

        for (int i = 1; i < countingHash.length; ++i) {
            countingHash[i] += countingHash[i - 1];
        }
        char[] output = new char[arr.length];

        for (int i = arr.length - 1; i >= 0; --i) {
            output[countingHash[arr[i]] - 1] = arr[i];
            --countingHash[arr[i]];
        }

        System.arraycopy(output, 0, arr, 0, arr.length);
    }

    static class sortingThread extends Thread{
        int start = 0;
        int stop = 0;
        char []arr = null;
        public sortingThread(char[] arr, int start, int stop) {
            this.arr = arr;
            this.start = start;
            this.stop = stop;
        }

        public void run() {
            int[] countArr = new int[256];
            for (int j = this.start; j < this.stop; ++j) {
                ++countArr[arr[j]];
            }
            synchronized (monitor) {
                for (int i = 0; i < countingHash.length; ++i) {
                    countingHash[i] += countArr[i];
                }
            }
        }
    }
}