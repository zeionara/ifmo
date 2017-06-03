import sun.java2d.pipe.SpanShapeRenderer;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.IllegalFormatCodePointException;
import java.util.Random;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.concurrent.CancellationException;
import java.util.concurrent.atomic.DoubleAccumulator;

/**
 * Created by Zerbs on 15.09.2016.
 */
public class ConsoleController {
    public static void main(String[] args){
        double accuration = 0.000001;
        BufferedReader bf;
        double[] freeMembers;
        double[][] koefficients;
        String validStartOptions[] = {StringConstants.USE_FILE, StringConstants.USE_CONSOLE};
        String validYesNo[] = {StringConstants.YES, StringConstants.NO};
        String selection = "";
        int numberOfData;
        int[] numXs;


        while(true) {
            // Getting working mode
            try {
                selection = getSelection(StringMessages.START_MESSAGE, StringMessages.START_MESSAGE_RETRYING, validStartOptions);
            } catch (CancellationException e) {
                finishApplication();
            }


            if (selection.equals(StringConstants.USE_CONSOLE)) {
                // Getting number of data from console
                try {
                    numberOfData = getInt(StringMessages.NUMBER_OF_DATA_MESSAGE, StringMessages.NUMBER_OF_DATA_MESSAGE_RE,
                            NumberConstants.MIN_NUMBER_OF_DATA, NumberConstants.MAX_NUMBER_OF_DATA);
                    koefficients = initializeMatrix(numberOfData);
                } catch (CancellationException e) {
                    continue;
                }

                //Getting generation koefficients mod from console

                try {
                    selection = getSelection(StringMessages.RANDOM_KOEFFIC, StringMessages.RANDOM_KOEFFIC_RE, validYesNo);
                } catch (CancellationException e) {
                    continue;
                }

                // If use console to set koefficinents

                if (selection.equals(StringConstants.NO)) {
                    try {
                        for (int i = 0; i < numberOfData; i++) {
                            koefficients[i] = getEquationKoefficients(numberOfData, StringMessages.KOEF_ENTERING_1 +
                                    numberOfData + StringMessages.KOEF_ENTERING_2 + i + StringMessages.KOEF_ENTERING_3);
                        }
                        freeMembers = getEquationKoefficients(numberOfData, StringMessages.FREE_MEMBERS_ENTERING_1 +
                                numberOfData + StringMessages.FREE_MEMBERS_ENTERING_2);
                    } catch (CancellationException e) {
                        continue;
                    }
                } else {
                    koefficients = initializeMatrixRandom(numberOfData);
                    freeMembers = initializeArrayRandom(numberOfData);
                }

                // Getting accuration from console

                try {
                    accuration = getDouble(StringMessages.ACCURATION_MESSAGE, StringMessages.ACCURATION_MESSAGE_RE,
                            NumberConstants.MIN_ACCURATION, NumberConstants.MAX_ACCURATION);
                } catch (CancellationException e) {
                    continue;
                }

                // Counting
                callCountingFunctions(koefficients,freeMembers,accuration);
            } else {
                try{
                    bf = openFileForReading(getString(StringMessages.SET_FILENAME));
                    numberOfData = readNumberOfDataFromFile(bf);
                    koefficients = initializeMatrix(numberOfData);



                    for (int i = 0; i < numberOfData; i++) {
                        koefficients[i] = getEquationKoefficients(numberOfData, bf);
                    }
                    freeMembers = getEquationKoefficients(numberOfData, bf);
                    accuration = readAccurationFromFile(bf);
                } catch (IOException|NumberFormatException e){
                    System.out.println(StringMessages.INVALID_FILE);
                    if (!isTryAgain("")){
                        finishApplication();
                    }
                    continue;
                }
                callCountingFunctions(koefficients,freeMembers,accuration);
            }
        }
    }

    public static void callCountingFunctions(double[][] koefficients, double[] freeMembers, double accuration){
        int[] numXs = new int[koefficients.length];
        for (int i = 0; i < numXs.length; i++){
            numXs[i] = i+1;
        }

        try {
            if (SimpleIterations.diagonalDomination(koefficients,numXs)) {
                System.out.println(StringMessages.DIAGONAL_DOM);
            } else {
                System.out.println(StringMessages.NOT_DIAGONAL_DOM);
            }
            double[][] resolving = SimpleIterations.resolveSystem(koefficients,freeMembers,accuration);
            showAnswer(resolving,numXs);
        } catch (IllegalArgumentException e){
            System.out.println(StringMessages.FAIL_DIAGONAL_DOM);
        }
    }

    public static void showAnswer(double[][] resolving, int[] numXs){
        System.out.println(StringMessages.PRE_ANSWER);
        System.out.println(StringMessages.CAL_VARS);
        for (int i = 0; i < resolving[0].length; i++){
            for (int j = 0; j < resolving[0].length; j++){
                if (numXs[j] == i+1){
                    System.out.println(StringConstants.VAR+numXs[j]+" = "+resolving[0][j]);
                }
            }
        }
        System.out.println(StringMessages.CAL_ACC);
        for (int i = 0; i < resolving[1].length; i++){
            for (int j = 0; j < resolving[0].length; j++){
                if (numXs[j] == i+1){
                    System.out.println(StringConstants.VAR+numXs[j]+" = "+resolving[1][j]);
                }
            }
            //System.out.println(StringConstants.VAR+numXs[i]+" : "+resolving[1][i]);
        }
        System.out.println(StringMessages.ITERS+resolving[2][0]+StringMessages.ITERS2);
    }

    public static BufferedReader openFileForReading(String path) throws FileNotFoundException{
        return new BufferedReader(new FileReader(path));
    }

    public static int readNumberOfDataFromFile(BufferedReader reader) throws IOException{
        int numberOfData = Integer.parseInt(reader.readLine());
        if (checkNumber(numberOfData,NumberConstants.MIN_NUMBER_OF_DATA,NumberConstants.MAX_NUMBER_OF_DATA)){
            return numberOfData;
        }
        throw new IOException();
    }

    public static double readAccurationFromFile(BufferedReader reader) throws IOException{
        return Double.parseDouble(reader.readLine());
    }

    public static double[] getEquationKoefficients(int numberOfData, BufferedReader bf) throws IOException{
        // Array with koefficients
        double[] koefficients = new double[numberOfData];
        // Counts koefficients
        int counter = 0;
        // Contains result of checking entered number
        boolean isCorrect = false;
        // Contains answer about repeating enter if checking failed
        // Temporary variable to store number
        double number;
        // Splits entered string
        StringTokenizer st;
        // Reads new string from standard input
        Scanner sc = new Scanner(System.in);


        st = new StringTokenizer(bf.readLine());
        while (st.hasMoreTokens()){
            number = checkNextNumberFileMod(st);
            checkCurrentNumberFileMod(number, counter, numberOfData);

            koefficients[counter] = number;
            counter++;
        }
        if (counter != numberOfData){
            throw new IOException();
        }
        return koefficients;
    }

    public static double[] getEquationKoefficients(int numberOfData, String messageForUser){
        // Array with koefficients
        double[] koefficients = new double[numberOfData];
        // Counts koefficients
        int counter = 0;
        // Contains result of checking entered number
        boolean isCorrect = false;
        // Contains answer about repeating enter if checking failed
        // Temporary variable to store number
        double number;
        // Splits entered string
        StringTokenizer st;
        // Reads new string from standard input
        Scanner sc = new Scanner(System.in);

        re:
        do {
            System.out.println(messageForUser);
            st = new StringTokenizer(sc.nextLine());
            while (st.hasMoreTokens()){
                try{
                    number = checkNextNumber(st);
                    checkCurrentNumber(number, counter, numberOfData);
                } catch (IllegalArgumentException e){
                    counter = 0;
                    continue re;
                }
                koefficients[counter] = number;
                counter++;
            }
            if (counter != numberOfData){
                System.out.println(StringMessages.NOT_ENOUGH_DATA);
                if (!isTryAgain("")){
                    throw new CancellationException();
                }
                counter = 0;
                continue re;
            }
        } while (counter < numberOfData);
        return koefficients;
    }

    public static void checkCurrentNumber(double number, int counter, int numberOfData){
        boolean isCorrect = checkNumber(number, NumberConstants.MIN_KOEFF, NumberConstants.MAX_KOEFF);
        if ((!isCorrect) || (counter >= numberOfData)){
            if (!isTryAgain("")){
                throw new CancellationException();
            }
            throw new IllegalArgumentException();
        }
    }

    public static void checkCurrentNumberFileMod(double number, int counter, int numberOfData) throws IOException{
        boolean isCorrect = checkNumber(number, NumberConstants.MIN_KOEFF, NumberConstants.MAX_KOEFF);
        if ((!isCorrect) || (counter >= numberOfData)){
            throw new IOException();
        }
    }

    public static double checkNextNumber(StringTokenizer st){
        double number = 0;
        try {
            number = Double.parseDouble(st.nextToken());
        } catch (NumberFormatException e){
            answerUserRepeatEnterKoefficient();
        }
        return number;
    }

    public static double checkNextNumberFileMod(StringTokenizer st) throws IOException{
        double number = 0;
        try {
            number = Double.parseDouble(st.nextToken());
        } catch (NumberFormatException e){
            throw new IOException();
        }
        return number;
    }

    public static void answerUserRepeatEnterKoefficient(){
        if (!isTryAgain("")){
            throw new CancellationException();
        }
        throw new IllegalArgumentException();
    }

    public static double[][] initializeMatrix(int numberOfData){
        double[][] matrix = new double[numberOfData][];
        for (int i = 0; i < numberOfData; i++){
            matrix[i] = new double[numberOfData];
            for (int j=0; j<numberOfData; j++){
                matrix[i][j] = NumberConstants.INITIAL_MATRIX_VALUE;
            }
        }
        return matrix;
    }

    public static double[][] initializeMatrixRandom(int numberOfData){
        Random random = new Random();
        double[][] matrix = new double[numberOfData][];
        for (int i = 0; i < numberOfData; i++){
            matrix[i] = new double[numberOfData];
            for (int j=0; j<numberOfData; j++){
                matrix[i][j] = random.nextInt()*200 - 100;
            }
        }
        return matrix;
    }

    public static double[] initializeArrayRandom(int numberOfData){
        Random random = new Random();
        double[] array = new double[numberOfData];
        for (int i = 0; i < numberOfData; i++){
            array[i] = random.nextInt()*200 - 100;
        }
        return array;
    }

    public static double getNumber(String messageToUser, String messageToUserRetrying, double lowBound, double highBound){
        boolean isCorrect = false;
        Scanner sc = new Scanner(System.in);
        double number = 0;
        System.out.println(messageToUser);
        do {
            try {
                number = Double.parseDouble(sc.nextLine());
            } catch (NumberFormatException e){
                if (!isTryAgain(messageToUserRetrying)){
                    throw new CancellationException();
                } else continue;
            }

            isCorrect = checkNumber(number, lowBound, highBound);

            if ((!isCorrect) && (!isTryAgain(messageToUserRetrying))){
                throw new CancellationException();
            }

        } while (!isCorrect);
        return number;
    }

    public static int getInt(String messageToUser, String messageToUserRetrying, int lowBound, int highBound){
        boolean isCorrect = false;
        Scanner sc = new Scanner(System.in);
        int number = 0;
        System.out.println(messageToUser);
        do {
            try {
                number = Integer.parseInt(sc.nextLine());
            } catch (NumberFormatException e){
                if (!isTryAgain(messageToUserRetrying)){
                    throw new CancellationException();
                } else continue;
            }

            isCorrect = checkNumber(number, lowBound, highBound);

            if ((!isCorrect) && (!isTryAgain(messageToUserRetrying))){
                throw new CancellationException();
            }

        } while (!isCorrect);
        return number;
    }

    public static double getDouble(String messageToUser, String messageToUserRetrying, double lowBound, double highBound){
        boolean isCorrect = false;
        Scanner sc = new Scanner(System.in);
        double number = 0D;
        System.out.println(messageToUser);
        do {
            try {
                number = Double.parseDouble(sc.nextLine());
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

    public static String getString(String messageToUser){
        Scanner sc = new Scanner(System.in);
        System.out.println(messageToUser);

        return sc.nextLine();
    }

    public static String getSelection(String messageToUser, String messageToUserRetrying, String[] validOptions){
        boolean isCorrect = false;
        Scanner sc = new Scanner(System.in);
        String selection;
        System.out.println(messageToUser);
        do {
            selection = sc.nextLine();

            isCorrect = checkString(selection, validOptions);

            if ((!isCorrect) && (!isTryAgain(messageToUserRetrying))){
                throw new CancellationException();
            }

        } while (!isCorrect);
        return selection;
    }

    public static boolean checkString(String str, String[] validOptions){
        for (String s : validOptions){
            if(str.equals(s)){
                return true;
            }
        }
        return false;
    }

    public static boolean checkNumber(double number, double lowBound, double highBound){
        return (number <= highBound) && (number >= lowBound);
    }

    public static boolean checkNumber(int number, int lowBound, int highBound){
        return (number <= highBound) && (number >= lowBound);
    }

    public static boolean checkDouble(double number, double lowBound, double highBound){
        return (number <= highBound) && (number >= lowBound);
    }

    public static boolean isTryAgain(String messageForUser){
        Scanner sc = new Scanner(System.in);
        String selection;
        do{
            System.out.println(StringMessages.TRY_AGAIN_MESSAGE);
            selection = sc.nextLine();
        } while ((!selection.equals("y")) && (!selection.equals("n")));
        if (selection.equals("y")){
            System.out.println(messageForUser);
            return true;
        }
        return false;
    }

    public static void finishApplication(){
        System.out.println(StringMessages.GOOD_BYE);
        System.exit(0);
    }
}
