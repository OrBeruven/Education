/***************************
 *  Written by : Or
 *  Reviewer : Mor
 *  Date : 17.07.2023
 *  Factory Design pattern implementation
 ***************************/
import java.security.InvalidKeyException;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class FactoryClass <K,D,T> {
    Map<K, Function<D, ? extends T>> map = new HashMap<>();
    void add(K key, Function<D, ? extends T> impFunction) {
        if (null == impFunction) {
            throw new IllegalArgumentException("received impFunction with the value null");
        }

        this.map.put(key, impFunction);
    }
    T getInstance(K key, D param) throws InvalidKeyException {
        try {
           return map.get(key).apply(param);
        } catch (NullPointerException e) {
            throw new InvalidKeyException(e);
        }
    }
}