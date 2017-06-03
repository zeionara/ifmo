import sun.rmi.runtime.Log;

/**
 * Created by Zerbs on 14.10.2016.
 */
public class ComplicatedFunction extends Function implements Integrable {
    private double a = 0;
    private double b = 0;
    private double c = 0;
    private double d = 0;
    private PolynomialFunction pf;
    private TriangularFunction tf;
    private LogarifmicalFunction lf;

    public ComplicatedFunction(double a, double b, double c, double d){
        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;

        pf = new PolynomialFunction(a, b, c);
        tf = new TriangularFunction(a, b, c, d);
        lf = new LogarifmicalFunction(a, b, c);
    }

    @Override
    public double getValue(double x){
        return (lf.getValue(x))*(tf.getValue(x)) - pf.getValue(x);
    }

    public String toString(){
        String retstr = "";
        String pfs = pf.toString();
        String tfs = tf.toString();
        String lfs = lf.toString();

        if ((lfs.length() > 0) && (tfs.length() > 0)){
            retstr += "( ( "+lfs+" ) * ( "+tfs+" ) ) ";
        } else if ((lfs.length() > 0) && !(tfs.length() > 0)){
            retstr += lfs;
        } else if (!(lfs.length() > 0) && (tfs.length() > 0)){
            retstr += tfs;
        }

        if (pfs.length() != 0){
            retstr += (" - ( " + pfs + " ) ");
        }

        return retstr;
    }
}
