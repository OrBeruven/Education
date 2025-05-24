class Useful {
    public void f() {}
    public void g() {}
}
class MoreUseful extends Useful {
    public void h() {}
    public void i() {}
    public void j() {}
    public void k() {}
}
public class RTTITest {
    public static void main(String[] args) {
        MoreUseful[] x = {
                new MoreUseful(),
                new MoreUseful()
        };
        x[0].f();
        x[1].i();
        x[1].g();

        ((MoreUseful)x[1]).i();
        ((MoreUseful)x[0]).i();
    }
}