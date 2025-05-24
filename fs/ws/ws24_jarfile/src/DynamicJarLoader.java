/***************************
 *  Written by : Or
 *  Reviewer : Evgenii
 *  Date : 02.08.2023
 *  Dynamic JAR Loader, loads inserted JAR.
 ***************************/
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.List;
import java.util.jar.JarEntry;
import java.util.jar.JarInputStream;


public class DynamicJarLoader {
    private String pathToJar = null;
    private String interfaceName = null;
    DynamicJarLoader(String pathToJar, String interfaceName) {
        this.pathToJar = pathToJar;
        this.interfaceName = getFileName(interfaceName);
    }

    List<Class<?>> load() {
        List<Class<?>> listOfClasses = new ArrayList<>();
        //Creating the classLoader and finding the requested interface
        URL url = null;
        try {
            url = new File(pathToJar).toURI().toURL();
        } catch (MalformedURLException e) {
            throw new RuntimeException(e);
        }

        try ( URLClassLoader classLoader = new URLClassLoader(new URL[]{url}) ) {
            Class<?> interfaceClass = null;
            try {
                interfaceClass = classLoader.loadClass(interfaceName);
            } catch (ClassNotFoundException e) {
                classLoader.close();
                throw new RuntimeException("Couldn't find requested interface", e);
            }

            /*the list to return*/
            JarInputStream jarInputStream = new JarInputStream(new FileInputStream(pathToJar));

            JarEntry currEntry = null;
            Class<?> currClass = null;

            while (null != (currEntry = jarInputStream.getNextJarEntry())) {
                try {
                    currClass = classLoader.loadClass(getFileName(currEntry.getName()));
                } catch (ClassNotFoundException e) {
                    System.out.println("Classnofound : " + currEntry.getName());
                    continue;
                }

                if (interfaceClass.isAssignableFrom(currClass) && !interfaceName.equals(currClass.getName())) {
                    listOfClasses.add(currClass);
                }
            }
        } catch (IOException e) {
          throw new RuntimeException(e);
        }

        return listOfClasses;
    }

    private static String getFileName(String absolutePath) {
        return absolutePath.replace(".class", "").replace("/", ".");
    }
}