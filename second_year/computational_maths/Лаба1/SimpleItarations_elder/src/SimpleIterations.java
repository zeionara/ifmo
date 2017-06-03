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

    // General methods
    // Resolves system
    public static double[][] resolveSystem(double[][] koefficients, double[] freeMembers, double accuration){
        double preAccuration = 0;
        double[][] answer = new double[3][koefficients.length];
        double[][] koefficientsModified = new double[koefficients.length][koefficients[0].length];
        double[] freeMembersModified = new double[freeMembers.length];
        double[] approach = new double[freeMembers.length];
        double[] approachTmp = new double[freeMembers.length];
        double temp = 0;
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
        //show(koefficients);
        //show(koefficientsModified);

        //Iterative process
        do {
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
                //System.out.println(i+" "+approachTmp[i]);
            }

            numOfIteration ++;
            if (countMediumAccuration(approach, approachTmp) > preAccuration){
                for (int i=0; i<approach.length; i++){
                    approachTmp[i] = freeMembersModified[i];
                    approach[i] = approachTmp[i];
                }
                break;
            }
            preAccuration = countMediumAccuration(approach, approachTmp);
            //System.out.println(countMediumAccuration(approach, approachTmp));
        } while (countMediumAccuration(approach, approachTmp) >= accuration);

        // Returning result
        for (int i = 0; i < answer.length; i++){
            answer[0][i] = approachTmp[i];
        }

        for (int i = 0; i < answer.length; i++){
            answer[1][i] = Math.abs(approachTmp[i]-approach[i]);
        }

        answer[2][0] = numOfIteration;

        return answer;
    }

    // Checks diagonal domination in matrix and rebuilds if necessary
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

        //show (koefficients);



        return isDiagonalDomination;
    }

    // Additional methods

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

        //System.out.println("Swapping");
        //show(matrix);
        for (int i = 0; i < matrix.length; i++){
            acc = matrix[i][src];
            matrix[i][src] = matrix[i][dest];
            matrix[i][dest] = acc;
        }
        //show(matrix);
    }

    private static matrixMember[] findMaximals(double[][] koefficients) {

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
    }

    private static boolean isNotWrited (matrixMember[] array, int i, int j, int numOfItems){
        for (int k = 0; k < numOfItems; k++){
            if ((array[k].i == i) && (array[k].j == j)){
                return false;
            }
        }
        return true;
    }

    private static boolean isNotWritedHard (matrixMember[] array, int i, int j, int numOfItems){
        //System.out.println("--");
        for (int k = 0; k < numOfItems; k++){
            //System.out.println(array[k].i+" "+array[k].j);
            //System.out.println(i+" "+j);
            if ((array[k].i == i) || (array[k].j == j)){
                return false;
            }
        }
        return true;
    }

    private static boolean tryDominate(double[][] koefficients, int[] numXs) {

        //System.out.println("--------------------");

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
                if (koefficients[i][j] > max.value) {
                        max.value = koefficients[i][j];
                        max.i = i;
                        max.j = j;
                }
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




            // if (!isNotWritedHard(maximals,max.i,max.j,i)){ return false;}

            /*if (max.j != i){
                swapCols(koefficients, max.j, i);
                int ss = numXs[max.j];
                numXs[max.j] = numXs[i];
                numXs[i] = ss;

                max.j = i;
            }
            maximals[i] = max;*/
        } // end external for

        //System.out.println(maximals.length);
        mxs = new matrixMember[maximals.length];
        boolean ddop = tryFindCombination(0,maximals.length - 1, maximals, mxs);
        if (!ddop){
            return false;
        }

        //System.out.println(mxs[0].j);

        // In mxs - correct combination

        matrixMember current;

        //System.out.println("pppppppppppppppppppppppp");

        //show(koefficients);

        for (int i = 0; i < koefficients.length; i++) {
            current = mxs[i];
            if (current.j != i){
                swapCols(koefficients, current.j, i);
                int ss = numXs[current.j];
                numXs[current.j] = numXs[i];
                numXs[i] = ss;
                changeMaxJ(mxs,i,current.j);
                current.j = i;

                /*for (int j = 0; j < mxs.length; j++){
                    System.out.println("fcking "+j+" max = "+mxs[j].value);
                    System.out.println("fcking "+j+" max j = "+mxs[j].j);
                }*/
            }
        }

        //show(koefficients);

        return true;
    }

    private static void changeMaxJ(matrixMember[] mxs, int src, int dest){
        //System.out.println("FUCKING CHANGED!");
        for (int i = 0; i < mxs.length; i++){
            if (mxs[i].j == src){
                mxs[i].j = dest;
                return;
            }
        }
    }

    private static boolean tryFindCombination(int currentRaw, int finalRaw, maximalMembers[] maximals, matrixMember[] mxs){

        matrixMember current;

        if (currentRaw > finalRaw){
            return true;
        }


        for (int i = 0; i < maximals[currentRaw].getCnt(); i++){
            current = maximals[currentRaw].get(i);
            //System.out.println("-----"+current.value);
            if (currentRaw == 0){

            }
            if (!isNotWritedHard(mxs,current.i,current.j,currentRaw)){
                // Wrong combination
                continue;
            }
            //System.out.println("new max!");
            //System.out.println(currentRaw+" "+mxs.length);
            mxs[currentRaw] = current;
            if (tryFindCombination(currentRaw+1, finalRaw, maximals, mxs)){
                // Correct combination
                //System.out.println("currentRaw = "+currentRaw+"; num of max = "+maximals[currentRaw].getCnt());
                /*for (int j = 0; j < mxs.length; j++){
                    System.out.println("fcking "+j+" max = "+mxs[j].value);
                    System.out.println("fcking "+j+" max j = "+mxs[j].j);
                }*/
                return true;
            }
            // Wrong combination
            continue;
        }
        return false;
    }


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

    public static void show(double[][] k){
        for (int i=0; i<k.length; i++){
            for (int j=0; j<k[0].length;j++){
                System.out.print(" "+k[i][j]);
            }
            System.out.println();
        }
    }
}
