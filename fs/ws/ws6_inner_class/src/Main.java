
public class Main {
    public static void main(String[] args) {
        ShadowTest st = new ShadowTest();
        ShadowTest.FirstLevel fl = st.new FirstLevel(){
            @Override
            void methodInFirstLevel(int x) {
                System.out.println("HERE anonymous");
                //super.methodInFirstLevel(x);
            }
        };
        fl.methodInFirstLevel(23);
        ShadowTest.FirstLevel hahaha = st.new FirstLevel();
        hahaha.methodInFirstLevel(57);
    }
}

class ShadowTest {
    public int x = 0;
    void printHello(){
        System.out.println("Hello");
    }

    class FirstLevel {

        public int x = 1;

        void methodInFirstLevel(int x) {
            System.out.println("x = " + x);
            System.out.println("this.x = " + this.x);
            System.out.println("ShadowTest.this.x = " + ShadowTest.this.x);

            ShadowTest.this.printHello();
        }
    }


}
