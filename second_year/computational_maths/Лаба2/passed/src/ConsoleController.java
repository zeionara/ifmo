import java.beans.IntrospectionException;
import java.util.ArrayList;
import java.util.*;
import java.util.concurrent.CancellationException;

import static java.lang.Double.*;

/**
 * Created by Zerbs on 14.10.2016.
 */
public class ConsoleController {
    private final static Double MAX_ACCURATION = 0.5;
    private final static String EXIT_STRING = "exit";

    public static void main(String... args){
        String selection = "";
        Double rangeleft = 0d;
        Double rangeright = 0d;
        Double accuration = 0.0001;
        Map<String, Integrable> functions = OutputHello(InitializeFunctions());

        // Getting name of function
            try {
                selection = getSelection("Please, type here name of function :\n" +
                                "(or type " + EXIT_STRING + " to exit)",
                        "Ok, you are trying to enter name of function here:", functions.keySet());
            } catch (CancellationException e) {
                finishApplication();
            }

            // Getting first value of range
            rangeleft = getDoubleWithHandler("Now type first bound of integration area here:",
                        "Ok, you are trying to enter first bound of integration area here:",
                        -MAX_VALUE, MAX_VALUE);

            // Getting second value of rane
            rangeright = getDoubleWithHandler("Now type second bound of integration area here:",
                        "Ok, you are trying to enter second bound of integration area here:",
                        -MAX_VALUE, MAX_VALUE);

            // Getting accuracy
            accuration = getDoubleWithHandler("Now type accuration of integration:",
                        "Ok, you are trying to enter accuration of integration here:",
                        -Math.abs(MAX_ACCURATION), Math.abs(MAX_ACCURATION));

            try {
                ShowRezult(Integrals.CountIntegral(functions.get(selection)::getValue, rangeleft, rangeright, accuration));
            } catch (IllegalArgumentException e) {
                System.out.println("Sorry, but we can't count this integral");
            }
    }

    private static double getDoubleWithHandler(String messageToUser, String messageToUserRetrying, double lowBound, double highBound){
        try {
            return getDouble(messageToUser,
                    messageToUserRetrying,
                    lowBound, highBound);
        } catch (CancellationException e) {
            return NaN;
        }
    }


    private static void ShowRezult(ArrayList<Double> rezult){
        System.out.println("Rezult:");
        System.out.println("Value of integral : "+rezult.get(0));
        System.out.println("Number of segments : "+rezult.get(1).longValue());
        System.out.println("Real accuration : "+rezult.get(2));
    }

    private static double getDouble(String messageToUser, String messageToUserRetrying, double lowBound, double highBound){
        boolean isCorrect = false;
        Scanner sc = new Scanner(System.in);
        double number = 0D;
        System.out.println(messageToUser);
        do {
            try {
                number = parseDouble(sc.nextLine());
            } catch (NumberFormatException e){
                if (!isTryAgain(messageToUserRetrying)){
                    throw new CancellationException();
                } else continue;
            }

            isCorrect = checkDouble(number, lowBound, highBound);

            if ((!isCorrect) && (!isTryAgain(messageToUserRetrying))){
                throw new CancellationException();
            }

        } while (!isCorrect);
        return number;
    }

    private static boolean checkDouble(double number, double lowBound, double highBound){
        return (number <= highBound) && (number >= lowBound);
    }

    private static Map<String, Integrable> OutputHello(Map<String, Integrable> functions){
        System.out.println("Hello! Here some functions for you: ");

        for (Map.Entry<String,Integrable> entry : functions.entrySet()){
            System.out.println(entry.getKey() + "(x) = "+entry.getValue());
        }
        return functions;
    }

    private static Map<String, Integrable> InitializeFunctions(){
        Map<String, Integrable> functions = new TreeMap<>();

        functions.put("a",new PolynomialFunction(13.6,63.1,61.13));
        functions.put("b",new TriangularFunction(-4,5.87,6.6,-7));
        functions.put("c",new LogarifmicalFunction(8.1,9.2,10.5));
        functions.put("d",new ComplicatedFunction(15.8,3.14,2.718281828459045,0.1));

        return functions;
    }

    private static String getSelection(String messageToUser, String messageToUserRetrying, Set<String> validOptions){
        boolean isCorrect = false;
        Scanner sc = new Scanner(System.in);
        String selection;
        System.out.println(messageToUser);
        do {
            selection = sc.nextLine();

            isCorrect = checkString(selection, validOptions);

            if ((selection.equals(EXIT_STRING)) || ((!isCorrect) && (!isTryAgain(messageToUserRetrying)))){
                throw new CancellationException();
            }

        } while (!isCorrect);
        return selection;
    }

    private static boolean checkString(String str, Set<String> validOptions){
        for (String s : validOptions){
            if(str.equals(s)){
                return true;
            }
        }
        return false;
    }

    private static boolean isTryAgain(String messageForUser){
        Scanner sc = new Scanner(System.in);
        String selection;
        do{
            System.out.println("You entered wrong value, do you want to try again? \n" +
                    "type y or n and press enter");
            selection = sc.nextLine();
        } while ((!selection.equals("y")) && (!selection.equals("n")));
        if (selection.equals("y")){
            System.out.println(messageForUser);
            return true;
        }
        return false;
    }

    public static void finishApplication(){
        System.out.println("Thanks for using. Good buy!");
        System.exit(0);
    }
}
