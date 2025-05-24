import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.MethodOrderer.OrderAnnotation;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;

@TestMethodOrder(OrderAnnotation.class)
class ComplexNumberTest {

    public static void main(String[] args) {
        ComplexNumber num = new ComplexNumber(4, 8);
        System.out.println(num.toString());
        num = ComplexNumber.parse("-5.2 - 2i");
        System.out.println(num.toString());
    }

    @Test
    void getReal() {
        ComplexNumber num = new ComplexNumber(4, 8);
        Assertions.assertEquals(4, num.getReal());
    }

    @Test
    void getImaginary() {
        ComplexNumber num = new ComplexNumber(4, -12324);
        Assertions.assertEquals(-12324, num.getImaginary());
    }

    @Test
    void setReal() {
        ComplexNumber num = new ComplexNumber(4, -12324);
        num.setReal(10);
        Assertions.assertEquals(10, num.getReal());
    }

    @Test
    void setImaginary() {
        ComplexNumber num = new ComplexNumber(4, -12324);
        num.setImaginary(-3);
        Assertions.assertEquals(-3, num.getImaginary());
    }

    @Test
    void isReal() {
        ComplexNumber num1 = new ComplexNumber(4, -12324);
        ComplexNumber num2 = new ComplexNumber(4, 0);

        Assertions.assertFalse(num1.isReal());
        Assertions.assertTrue(num2.isReal());
    }

    @Test
    void isImaginary() {
        ComplexNumber num1 = new ComplexNumber(4, -1);
        ComplexNumber num2 = new ComplexNumber(0, 7);

        Assertions.assertFalse(num1.isImaginary());
        Assertions.assertTrue(num2.isImaginary());
    }

    @Test
    void add() {
        ComplexNumber num1 = new ComplexNumber(10, -1);
        ComplexNumber num2 = new ComplexNumber(3, 7);

        ComplexNumber num3 = num1.add(num2);
        Assertions.assertEquals(13, num3.getReal());
        Assertions.assertEquals(6, num3.getImaginary());
    }

    @Test
    void subtract() {
        ComplexNumber num1 = new ComplexNumber(10, -1);
        ComplexNumber num2 = new ComplexNumber(3, 7);

        ComplexNumber num3 = num1.subtract(num2);
        Assertions.assertEquals(7, num3.getReal());
        Assertions.assertEquals(-8, num3.getImaginary());
    }

    @Test
    void parse() {
        ComplexNumber num1 = ComplexNumber.parse("3 + 5i");
        ComplexNumber num2 = ComplexNumber.parse("-1002.45+8i");

        Assertions.assertEquals(3, num1.getReal());
        Assertions.assertEquals(5, num1.getImaginary());
        Assertions.assertEquals(-1002.45, num2.getReal());
        Assertions.assertEquals(8, num2.getImaginary());

    }

    @Test
    void testEquals() {
        ComplexNumber num1 = ComplexNumber.parse("3 - 4i");
        ComplexNumber num2 = ComplexNumber.parse("-23.76 + 8i");
        ComplexNumber num3 = num1.add(num2);

        Assertions.assertEquals(num3, ComplexNumber.parse("-20.76 + 4i"));
        Assertions.assertNotEquals(num3, ComplexNumber.parse("-5+ 4i"));
    }

    @Test
    void testHashCode() {
        ComplexNumber num1 = ComplexNumber.parse("3 - 4i");
        ComplexNumber num2 = ComplexNumber.parse("10 - 80i");
        ComplexNumber num3 = ComplexNumber.parse("7 - 76i");

        num1 = num2.subtract(num1);
        Assertions.assertEquals(num1, num3);
        Assertions.assertEquals(num1.hashCode(), num3.hashCode());
    }

    @org.junit.jupiter.api.Test
    void compareTo() {

        ComplexNumber num1 = ComplexNumber.parse("3 - 4i");
        ComplexNumber num2 = ComplexNumber.parse("-23.76 + 8i");

        Assertions.assertTrue(num1.compareTo(num2) < 0);

        num2 = num2.add(ComplexNumber.parse("23 -4i"));

        Assertions.assertTrue(num1.compareTo(num2) > 0);

    }

}