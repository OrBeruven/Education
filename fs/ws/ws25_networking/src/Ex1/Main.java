package Ex1;

import java.io.*;
import java.net.MalformedURLException;
import java.net.URL;

public class Main {
    public static void main(String[] args) throws IOException {
        printURL("https://en.wikipedia.org/wiki/Thread_pool");
    }

    public static void printURL(String webpageURL) throws IOException {
        URL url = null;
        try {
            url = new URL(webpageURL);
        } catch (MalformedURLException e) {
            System.out.println("Webpage Not Found");
            return;
        }
        BufferedReader reader = new BufferedReader(new InputStreamReader(url.openStream()));

        BufferedWriter writer = new BufferedWriter(new FileWriter("NewWebpage.html"));

        String line = null;
        while (null != (line = reader.readLine())) {
            writer.write(line);
            System.out.println(line);
        }

        reader.close();
        writer.close();
    }
}