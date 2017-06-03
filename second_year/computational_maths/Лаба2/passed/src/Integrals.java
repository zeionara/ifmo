import java.util.ArrayList;

/**
 * Created by Zerbs on 14.10.2016.
 */
public class Integrals {
    public static ArrayList<Double> CountIntegral(Integrable f, double lowbound, double highbound, double accuration){
        boolean changeSign = false;
        ArrayList<Double> rezult = new ArrayList<>();
        double TmpValue = 0d;
        double Value = 0d;
        double realAccuration = 0d;
        int numberOfSegments = 1;


        if (lowbound > highbound){
            double tmp = lowbound;
            lowbound = highbound;
            highbound = tmp;
            changeSign = true;
        }

        double step = highbound - lowbound;

        Value = (highbound - lowbound)*(f.getValue(highbound) + f.getValue(lowbound))/2;

        if (!Double.isFinite(Value) || Double.isNaN(Value)){
            throw new IllegalArgumentException();
        }
        do{

            if (numberOfSegments > 100_000){
                throw new IllegalArgumentException();
            }

            TmpValue = Value;
            Value = 0;
            numberOfSegments *= 2;
            step = (highbound - lowbound)/numberOfSegments;
            for (int i = 0; i < numberOfSegments; i++){
                Value += step*(f.getValue(lowbound + i*step) + f.getValue(lowbound + (i+1)*step))/2;
            }
        } while(Math.abs(Value - TmpValue)/3 > Math.abs(accuration));
        realAccuration = Math.abs(Value - TmpValue)/3;
        if (changeSign){
            Value = -Value;
        }
        if (!Double.isFinite(Value) || Double.isNaN(Value)){
            throw new IllegalArgumentException();
        }

        rezult.add(Value);
        rezult.add((double)numberOfSegments);
        rezult.add(realAccuration);

        return rezult;
    }
}
