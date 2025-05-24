import java.util.Objects;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.List;
import java.util.ArrayList;

public class ComplexNumber implements Comparable<ComplexNumber> {
    private double real = 0;
    private double imaginary = 0;

    public ComplexNumber() {
        this(0, 0);
    }

    public ComplexNumber(double newReal, double newImaginary) {
        this.real = newReal;
        this.imaginary = newImaginary;
    }

    public double getReal() {
        return real;
    }

    public double getImaginary() {
        return imaginary;
    }

    public void setImaginary(double imaginary) {
        this.imaginary = imaginary;
    }

    public void setReal(double real) {
        this.real = real;
    }

    public boolean isReal() {
        return this.getImaginary() == 0;
    }

    public boolean isImaginary() {
        return (this.getReal() == 0 && this.getImaginary() != 0);
    }

    public ComplexNumber add(ComplexNumber other) {
        return new ComplexNumber(this.getReal() + other.getReal(), this.getImaginary() + other.getImaginary());
    }
    
    public ComplexNumber subtract(ComplexNumber complexNumber) {
        return new ComplexNumber(this.getReal() - complexNumber.getReal(), this.getImaginary() - complexNumber.getImaginary());
    }

    @Override
    public String toString() {
        return "complexNumber { " + "real=" + this.getReal() + ", imagine=" + this.getImaginary() + "i " + '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (!(o instanceof ComplexNumber that)) {
            return false;
        }
        return Double.compare(that.getReal(), this.getReal()) == 0 && Double.compare(that.getImaginary(), this.getImaginary()) == 0;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 31 * hash + (int)this.getReal();
        hash = 31 * hash + (int)this.getImaginary();
        return hash;
    }

    public static ComplexNumber parse(String str) {
        double real = 0;
        double imaginary = 0;
        ComplexNumber to_ret = null;

        str = str.replaceAll(" ", "");
        Pattern pattern = Pattern.compile("([+-]?\\d+[.]?\\d*)([+-]\\d+[.]?\\d*)i");
        Matcher matcher = pattern.matcher(str);
        if (matcher.find()) {
            real = Double.parseDouble(matcher.group(1));
            imaginary = Double.parseDouble(matcher.group(2));
            to_ret = new ComplexNumber(real, imaginary);
        }

        return to_ret;
    }

    @Override
    public int compareTo(ComplexNumber other) {

        double val_comp = Math.sqrt(Math.pow(other.getReal(), 2) + Math.pow(other.getImaginary(), 2));
        double val_this = Math.sqrt(Math.pow(this.getReal(), 2) + Math.pow(this.getImaginary(), 2));

        int status = (val_comp == val_this) ? 0 : 1;

        status = (status == 0) ? 0 : (val_this > val_comp ? 1 : -1);

        return status ;
    }
}