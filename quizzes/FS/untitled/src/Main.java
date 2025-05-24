
import com.sun.jdi.VoidType;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Main {
    public static void main(String[] args) {
        ExecutorService executorService = Executors.newSingleThreadExecutor();
        Future f = executorService.submit(() -> {
            System.out.println("WEEEE");
        });



    }
}

