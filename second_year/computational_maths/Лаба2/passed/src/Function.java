/**
 * Created by Zerbs on 14.10.2016.
 */
public class Function {
    private String tag = "";

    public String addPlusIfNeed(String retstr){
        if(retstr.length() > 0){
            return retstr + " + ";
        }
        return retstr;
    }
    public String addKoefIfNeed(String retstr, double k){
        if(k != 1){
            return retstr + k;
        }
        return retstr;
    }
    public boolean AreAllZero(double... args){
        for(double v : args){
            if (v != 0){
                return false;
            }
        }// for
        return true;
    }
}
