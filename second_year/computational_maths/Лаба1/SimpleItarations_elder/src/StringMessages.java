/**
 * Created by Zerbs on 15.09.2016.
 */
public class StringMessages {
    public static final String START_MESSAGE = "Hello, please, select working mode: \n"+
                                        "1) "+StringConstants.USE_FILE+" - use files \n"+
                                        "2) "+StringConstants.USE_CONSOLE+" - use console \n";

    public static final String START_MESSAGE_RETRYING = "So, let's try again, select working mode: \n"+
            "1) "+StringConstants.USE_FILE+" - use files \n"+
            "2) "+StringConstants.USE_CONSOLE+" - use console \n";

    public static final String UNDEFINED_ERROR_MESSAGE = "Something goes wrong";

    public static final String TRY_AGAIN_MESSAGE = "You entered wrong value, try again? \n"+
            "1) "+StringConstants.YES+" - yes, try again \n"+
            "2) "+StringConstants.NO+" - no, cancel operation \n";

    public static final String GOOD_BYE = "Good bye! See you soon!";

    //

    public static final String NUMBER_OF_DATA_MESSAGE = "Ok, enter integer number of data from "+
            NumberConstants.MIN_NUMBER_OF_DATA + " to "+NumberConstants.MAX_NUMBER_OF_DATA + " : ";

    public static final String NUMBER_OF_DATA_MESSAGE_RE = "So, enter correct integer number of data from "+
            NumberConstants.MIN_NUMBER_OF_DATA + " to "+NumberConstants.MAX_NUMBER_OF_DATA + " : ";

    //

    public static final String RANDOM_KOEFFIC = "Do you want to use random koefficients?\n"+
            "1) "+StringConstants.YES+" - yes, I want \n"+
            "2) "+StringConstants.NO+" - no, use selected working mode \n";

    public static final String RANDOM_KOEFFIC_RE = "So, can I set random koefficients?\n"+
            "1) "+StringConstants.YES+" - yes, you can \n"+
            "2) "+StringConstants.NO+" - no, I want to do it myself \n";

    //

    public static final String KOEF_ENTERING_1 = "Let's type ";

    public static final String KOEF_ENTERING_2 = " koefficients for the ";

    public static final String KOEF_ENTERING_3 = " equation. \n "+
            "Note, that koefficients must be from "+NumberConstants.MIN_KOEFF+" to "+NumberConstants.MAX_KOEFF+
            " and must be separated by space.";
    public static final String NOT_ENOUGH_DATA = "There is not enough data in input string.";

    public static final String FREE_MEMBERS_ENTERING_1 = "Now, let's type ";
    public static final String FREE_MEMBERS_ENTERING_2 = "free members here :";

    public static final String SET_FILENAME = "Please, enter full filename here: ";

    public static final String INVALID_FILE = "File, which you selected, contains uncorrect data or doesn't exist.";

    //

    public static final String ACCURATION_MESSAGE = "Ok, let's try to enter accuration from "+
            NumberConstants.MIN_ACCURATION + " to "+NumberConstants.MAX_ACCURATION + " : ";

    public static final String ACCURATION_MESSAGE_RE = "So, I can't understand you, please, enter correct accuration from "+
            NumberConstants.MIN_ACCURATION + " to "+NumberConstants.MAX_ACCURATION + " : ";

    //

    public static final String DIAGONAL_DOM = "Perfect! Matrix has property 'diagonal domination'!";

    public static final String NOT_DIAGONAL_DOM = "O-oh, your matrix has no property 'diagonal domination' , but \n" +
            "we can fix it!";

    public static final String FAIL_DIAGONAL_DOM = "O-oh, your matrix has no property 'diagonal domination' , and \n" +
            "we can't fix it. You can return to start and enter another matrix.";

    //
    public static final String PRE_ANSWER = "Here is answer for your question: ";
    public static final String CAL_VARS = "Column of variables: ";
    public static final String CAL_ACC = "Column of accurations: ";

    public static final String ITERS = "Resolve founded after ";
    public static final String ITERS2 = " iterations.";
}
