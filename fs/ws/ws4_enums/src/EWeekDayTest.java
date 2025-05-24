import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class EWeekDayTest {

    @Test
    void getValue() {
        EWeekDay day = EWeekDay.MONDAY;
        assertEquals(2, day.getValue());
        assertEquals(7, EWeekDay.SHABAT.getValue());
        assertEquals(5, EWeekDay.THURSDAY.getValue());
    }

    @Test
    void fromValue() {
        EWeekDay day = EWeekDay.fromValue(1);
        assertEquals(1, day.getValue());
        assertEquals(3, EWeekDay.fromValue(3).getValue());
    }

    @Test
    void printValues() {
        EWeekDay.printValues();
    }
}