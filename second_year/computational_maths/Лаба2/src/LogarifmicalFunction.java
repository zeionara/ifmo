/**
 * Created by Zerbs on 14.10.2016.
 */
public class LogarifmicalFunction extends Function implements Integrable {
    private double a = 0;
    private double b = 0;
    private double c = 0;

    public LogarifmicalFunction(double a, double b, double c){
        this.a = a;
        this.b = b;
        this.c = c;
    }

    @Override
    public double getValue(double x){
        return a*Math.log(x) + b*Math.log10(x) + c;
    }

    public String toString(){
        String retstr = "";
        if (a != 0){
            retstr = addKoefIfNeed(retstr, a);
            retstr += "ln(x)";
        }
        if (b != 0){
            retstr = addPlusIfNeed(retstr);
            retstr = addKoefIfNeed(retstr, b);
            retstr += "lg(x)";
        }
        if (c != 0){
            retstr = addPlusIfNeed(retstr);
            retstr += c;
        }
        return retstr;
    }
}
