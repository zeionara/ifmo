/**
 * Created by Zerbs on 18.09.2016.
 */
class matrixMember{
    public double value;
    public int i;
    public int j;
}

class maximalMembers{
    private matrixMember[] members;
    private int cnt = 0;

    public maximalMembers(int length){
        members = new matrixMember[length];
    }

    public void add(matrixMember memb){
        members[cnt] = memb;
        cnt ++;
    }

    public matrixMember get(int cnt){
        return members[cnt];
    }

    public int getCnt(){
        return cnt;
    }
}

public class SimpleIterations {

    //
    // General methods
    //

    // Resolves system, returns array, in which first column contains resolve,
    // second - accuration and the third - number of iterations

    public static double[][] resolveSystem(double[][] koefficients, double[] freeMembers, double accuration) throws IllegalArgumentException{

        double[][] answer = new double[3][koefficients.length];
        double[][] koefficientsModified = new double[koefficients.length][koefficients[0].length];
        double[] freeMembersModified = new double[freeMembers.length];
        double[] approach = new double[freeMembers.length];
        double[] approachTmp = new double[freeMembers.length];
        int numOfIteration = 0;

        // Modifying koefficients
        for (int i = 0; i < koefficients.length; i++){
            for (int j = 0; j < koefficients[0].length; j++){
                koefficientsModified[i][j] = - koefficients[i][j]/koefficients[i][i];
            }
        }

        //Modifying free members
        for (int i=0; i < freeMembers.length; i++){
            freeMembersModified[i] = freeMembers[i]/koefficients[i][i];
        }

        // Zero's approach
        for (int i=0; i<approach.length; i++){
            approach[i] = freeMembersModified[i];
        }

        //Iterative process
        do {
            if (numOfIteration > NumberConstants.MAX_NUM_OF_ITERATIONS){
                throw new IllegalArgumentException();
            }

            if (numOfIteration > 0){
                for (int i = 0; i < koefficients.length; i++){
                    approach[i] = approachTmp[i];
                }
            }

            for (int i = 0; i < koefficients.length; i++){
                approachTmp[i] = 0;
                for (int j = 0; j < koefficients[0].length; j++){
                    if (i!=j){
                        approachTmp[i] += approach[j]*koefficientsModified[i][j];
                    }
                }
                approachTmp[i] += freeMembersModified[i];
            }

            numOfIteration ++;

        } while (countMediumAccuration(approach, approachTmp) >= accuration);

        // Returning result
        for (int i = 0; i < answer[0].length; i++){
            answer[0][i] = approachTmp[i];
        }

        for (int i = 0; i < answer[1].length; i++){
            answer[1][i] = Math.abs(approachTmp[i]-approach[i]);
        }

        answer[2][0] = numOfIteration;

        return answer;
    }

    // Checks diagonal domination in matrix and rebuilds if necessary
    // If rebuilding is unpossible, throws IllegalArgumentException
    // numXs for keeping numeration of variables

    public static boolean diagonalDomination(double[][] koefficients, int[] numXs){

        boolean isDiagonalDomination = true;

        check:
        for (int i = 0; i < koefficients.length; i++){
            for (int j = 0; j < koefficients[0].length; j++){
                if (koefficients[i][j] > koefficients[i][i]){
                    isDiagonalDomination = false;
                    break check;
                }
            }
        }

        if ((!isDiagonalDomination) && (!tryDominate(koefficients, numXs)) || (hasDiagonalZeros(koefficients))){
            throw new IllegalArgumentException();
        }

        return isDiagonalDomination;
    }

    public static boolean isSystemCorrect(double[][] matrix){
        if (getDeterminant(matrix, new int[matrix.length], 0) != 0){
            return true;
        }
        return false;
    }

    //
    // Additional methods
    //

    private static double countMediumAccuration(double[] array1, double[] array2){
        double sumAccuration = 0;
        for (int i=0; i<array1.length; i++){
            sumAccuration += Math.abs(array1[i] - array2[i]);
        }
        return sumAccuration/(double)array1.length;
    }

    private static void swapCols(double[][] matrix, int src, int dest){
        if ((src >= matrix[0].length) || (dest >= matrix[0].length)){
            throw new IllegalArgumentException();
        }

        double acc = 0;

        for (int i = 0; i < matrix.length; i++){
            acc = matrix[i][src];
            matrix[i][src] = matrix[i][dest];
            matrix[i][dest] = acc;
        }
    }

    private static boolean isNotWritedHard (matrixMember[] array, int i, int j, int numOfItems){
        for (int k = 0; k < numOfItems; k++){
            if ((array[k].i == i) || (array[k].j == j)){
                return false;
            }
        }
        return true;
    }

    // Tries to fix diagonal domination in the matrix, numXs for keeping numeration of variables

    private static boolean tryDominate(double[][] koefficients, int[] numXs) {

        // Initializing massive with maximal elements by rows

        matrixMember[] mxs = new matrixMember[koefficients.length];

        maximalMembers[] maximals = new maximalMembers[koefficients.length];

        for (int i = 0; i < maximals.length; i++){
            maximals[i] = new maximalMembers(koefficients[0].length);
        }

        matrixMember max;
        matrixMember tmpMM;

        // Searching maximals and writing to maximals array

        for (int i = 0; i < koefficients.length; i++) {
            max = new matrixMember();
            max.value = Double.NEGATIVE_INFINITY;

            // Finding max value in raw

            for (int j = 0; j < koefficients[0].length; j++) {

                if ((j==0) || (Math.abs(koefficients[i][j]) > Math.abs(max.value))) {
                        max.value = koefficients[i][j];
                        max.i = i;
                        max.j = j;
                }
                System.out.println(max.value);
            } // end internal for

            // Writing all maximals from this raw

            for (int j = 0; j < koefficients[0].length; j++) {
                if (koefficients[i][j] == max.value) {
                    tmpMM = new matrixMember();
                    tmpMM.value = max.value;
                    tmpMM.i = i;
                    tmpMM.j = j;
                    maximals[i].add(tmpMM);
                }
            } // end internal for
        } // end external for

        mxs = new matrixMember[maximals.length];
        boolean ddop = tryFindCombination(0,maximals.length - 1, maximals, mxs);
        System.out.println(ddop);
        if (!ddop){
            return false;
        }

        matrixMember current;

        for (int i = 0; i < koefficients.length; i++) {
            current = mxs[i];
            if (current.j != i){
                swapCols(koefficients, current.j, i);
                int ss = numXs[current.j];
                numXs[current.j] = numXs[i];
                numXs[i] = ss;
                changeMaxJ(mxs,i,current.j);
                current.j = i;
            }
        }

        return true;
    }

    private static void changeMaxJ(matrixMember[] mxs, int src, int dest){
        for (int i = 0; i < mxs.length; i++){
            if (mxs[i].j == src){
                mxs[i].j = dest;
                return;
            }
        }
    }

    // Tries to find combination of maximums by raws in matrix, with which we can fix diagonal domination
    // If succesful, combination saved in array mxs

    private static boolean tryFindCombination(int currentRaw, int finalRaw, maximalMembers[] maximals, matrixMember[] mxs){
        matrixMember current;
        if (currentRaw > finalRaw){
            // Perfect!
            return true;
        }
        for (int i = 0; i < maximals[currentRaw].getCnt(); i++){
            current = maximals[currentRaw].get(i);
            if (!isNotWritedHard(mxs,current.i,current.j,currentRaw)){
                // Wrong combination
                continue;
            }
            mxs[currentRaw] = current;
            if (tryFindCombination(currentRaw+1, finalRaw, maximals, mxs)){
                return true;
            }
            // Wrong combination
            continue;
        }
        return false;
    }

    // Checking for the zeros on the main diagonal

    private static boolean hasDiagonalZeros(double[][] koefficients){
        if (koefficients.length != koefficients[0].length){
            throw new IllegalArgumentException();
        }
        for (int i=0; i<koefficients.length; i++){
            if (koefficients[i][i] == 0){
                return true;
            }
        }
        return false;
    }

    // Checking determinant of the general matrix

    private static double getDeterminant(double[][] matrix, int[] selected, int numOfIteration){
        if (numOfIteration == matrix.length){
            double interRez = Math.pow(-1,countInvertions(selected));
            for (int i = 0; i < selected.length; i++){
                interRez *= matrix[selected[i]][i];
            }
            return interRez;
        }

        double sum = 0;
        for (int i = 0; i < matrix.length; i++){
            if (!tryFind(selected, i, numOfIteration)) {
                selected[numOfIteration] = i;
                sum += getDeterminant(matrix, selected, numOfIteration + 1);
            }
        }
        return sum;
    }

    private static boolean tryFind(int[] array, int src, int size){
        for (int i = 0; i < size; i++){
            if (array[i] == src){
                return true;
            }
        }
        return false;
    }

    private static int countInvertions(int[] array){
        int numberOfInvertions = 0;
        for (int i = 1; i < array.length; i++){
            for (int j = 0; j < i; j++) {
                if (array[j] > array[i]) {
                    numberOfInvertions++;
                }
            }
        }
        return numberOfInvertions;
    }

    /*private static matrixMember[] findMaximals(double[][] koefficients) {

        matrixMember[] maximals = new matrixMember[koefficients.length];
        int counter = 0;

        matrixMember max;

        while (counter < maximals.length) {
            max = new matrixMember();
            max.value = Double.NEGATIVE_INFINITY;

            for (int i = 0; i < koefficients.length; i++) {
                for (int j = 0; j < koefficients[0].length; j++) {
                    if ((koefficients[i][j] > max.value) && (isNotWrited(maximals, i, j, counter))) {
                        max.value = koefficients[i][j];
                        max.i = i;
                        max.j = j;
                    }
                } // end internal for
            } // end external for
            maximals[counter] = max;
            counter++;
        } // end while
        return maximals;
    }*/

    /*private static boolean isNotWrited (matrixMember[] array, int i, int j, int numOfItems){
        for (int k = 0; k < numOfItems; k++){
            if ((array[k].i == i) && (array[k].j == j)){
                return false;
            }
        }
        return true;
    }*/
}
