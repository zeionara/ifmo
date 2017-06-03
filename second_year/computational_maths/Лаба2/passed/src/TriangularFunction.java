/**
 * Created by Zerbs on 14.10.2016.
 */
public class TriangularFunction extends Function implements Integrable {
    private double a;
    private double b;
    private double c;
    private double d;

    public TriangularFunction(double a, double b, double c, double d){
        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;
    }

    @Override
    public double getValue(double x){
        return a*Math.sin(x) + b*Math.cos(x) + c*Math.sin(x)/Math.cos(x) + d*Math.sin(x)*Math.cos(x);
    }

    public String toString(){
        String retstr = "";
        if (a != 0){
            retstr = addKoefIfNeed(retstr, a);
            retstr += "sin(x)";
        }
        if (b != 0){
            retstr = addPlusIfNeed(retstr);
            retstr = addKoefIfNeed(retstr, b);
            retstr += "cos(x)";
        }
        if (c != 0){
            retstr = addPlusIfNeed(retstr);
            retstr = addKoefIfNeed(retstr, c);
            retstr += "tg(x)";
        }
        if (d != 0){
            retstr = addPlusIfNeed(retstr);
            retstr = addKoefIfNeed(retstr, d);
            retstr += "sin(x)cos(x)";
        }
        return retstr;
    }
}
