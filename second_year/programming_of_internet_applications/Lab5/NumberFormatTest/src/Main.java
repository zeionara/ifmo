import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.NumberFormat;
import java.text.ParsePosition;
import java.util.Locale;

/**
 * Created by Zerbs on 20.11.2016.
 */
public class Main {
    private static double myNumber=666.1313;
    private static double mn = 222.0;

    public static void main(String[] args) {
        //NumberFormat
        System.out.println(NumberFormat.getCurrencyInstance(Locale.CHINESE).format(myNumber));

        NumberFormat numberFormat = NumberFormat.getCurrencyInstance(Locale.CANADA);
        numberFormat.setParseIntegerOnly(false);
        Number parsed = numberFormat.parse(numberFormat.format(myNumber)+" "+numberFormat.format(mn),new ParsePosition(-1));
        System.out.println(parsed);
        //DecimalFormat
        DecimalFormat decimalFormat = new DecimalFormat("####,###");
        System.out.println(decimalFormat.format(myNumber));
        //output : 666

        decimalFormat.applyPattern("вот твое число : 000.00000");
        System.out.println(decimalFormat.format(myNumber));
        //output : вот твое число : 666,13130

        decimalFormat.applyPattern("###,##.#");
        System.out.println(decimalFormat.format(myNumber));
        //',' - separator in integer part (in our localization it is ' ')
        //'.' - separator between integer and float part (in our localization it is ',')
        //output : 6 66,1

        decimalFormat.applyLocalizedPattern("###,##.#");
        System.out.println(decimalFormat.format(myNumber));
        //',' - in our localization it is separator of integer and float part
        //'.' - in our localization it is something strange
        //output : 666,131.

        NumberFormat nf = NumberFormat.getInstance(Locale.ENGLISH);
        DecimalFormat df = (DecimalFormat)nf;
        df.applyPattern("####,##.#");
        System.out.println(df.format(myNumber));
        //In the England symbol '.' - separator of integer and float parts
        //output : 6,66.1

        nf = NumberFormat.getInstance(Locale.GERMAN);
        df = (DecimalFormat)nf;
        df.applyPattern("####,##.#");
        System.out.println(df.format(myNumber));
        //In the German symbol ',' - separator of integer and float parts
        //output : 6.66,1

        //DecimalFormatSymbols
        DecimalFormatSymbols decimalFormatSymbols = new DecimalFormatSymbols();
        decimalFormatSymbols.setCurrencySymbol(" бабла");
        decimalFormatSymbols.setDecimalSeparator('a');
        decimalFormatSymbols.setGroupingSeparator('б');

        df = new DecimalFormat("##,##.##",decimalFormatSymbols);

        System.out.println(df.format(myNumber));
        //output : 6б66a13

        nf = NumberFormat.getCurrencyInstance();
        ((DecimalFormat) nf).setDecimalFormatSymbols(decimalFormatSymbols);
        System.out.println(nf.format(myNumber));
        //output : 666,13 бабла

    }


}
