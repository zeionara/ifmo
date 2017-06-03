using FourthLab;
using System;

public static class PolygonOperator
{
    public static Polygon CreatePolygon()
    {
        Console.WriteLine(MessagesForUser.CREATING_POLYGON_IN_PROCESS);
        Console.WriteLine(MessagesForUser.WHAT_WILL_CREATES);
        int selectedPolygonTypeMenuItem = SelectTypeOfPolygonFromMenu();
        int numberOfSides = GetNumberOfSides(selectedPolygonTypeMenuItem);
        int id = GetPolygonAttribute(MessagesForUser.ENTERING_ID_FOR_NEW_POLYGON, "id", 0, false);
        int[] sides = new int[numberOfSides];
        try
        {
            sides[0] = GetPolygonAttribute("Enter length of 1 side (integer number >= 1):",
                    "length of side", 1, true);
        }
        catch (ValueWasSkippedException exception)
        {
            Console.WriteLine(MessagesForUser.SIDES_WILL_SETS_BY_DEFAULT);
            switch (selectedPolygonTypeMenuItem)
            {
                case PolygonType.TRIANGLE: return new Triangle(id);
                case PolygonType.PARALLELOGRAM: return new Parallelogram(id);
                case PolygonType.PENTAGON: return new Pentagon(id);
                case PolygonType.HEXAGON: return new Hexagon(id);
                case PolygonType.HEPTAGON: return new Heptagon(id);
                default: throw new OperationWasCrashedException();
            }
        }
        for (int i = 1; i < numberOfSides; i++)
        {
            if ((numberOfSides != GetNumberOfSides(PolygonType.TRIANGLE))
                || (i < GetNumberOfSides(PolygonType.TRIANGLE) - 1))
            {
                sides[i] = GetPolygonAttribute("Enter length of " + (i + 1) + " side (integer number >= 1):",
                        "length of side", 1, false);
            }
            else
            {
                sides[i] = GetPolygonAttribute("Enter length of " + (i + 1) +
                        " side (integer number >= 1 and <= " + (sides[0] + sides[1]) + "):",
                        "length of side", 1, sides[0] + sides[1], false);
            }
        }
        switch (selectedPolygonTypeMenuItem)
        {
            case PolygonType.TRIANGLE: return new Triangle(id, sides);
            case PolygonType.PARALLELOGRAM: return new Parallelogram(id, sides);
            case PolygonType.PENTAGON: return new Pentagon(id, sides);
            case PolygonType.HEXAGON: return new Hexagon(id, sides);
            case PolygonType.HEPTAGON: return new Heptagon(id, sides);
            default: throw new OperationWasCrashedException();
        }
    }

    public static int SelectTypeOfPolygonFromMenu()
    {
        MenuItemSelector.DisplayMenu(Menues.PolygonTypeMenu);
        int selectedPolygonTypeMenuItem = MenuItemSelector.SelectMenuItem(Menues.PolygonTypeMenu);
        ContinueWorkingWithTypeOrCancel(selectedPolygonTypeMenuItem);
        return selectedPolygonTypeMenuItem;
    }
    public static int GetPolygonAttribute(string messageToUser, string nameOfNeededValue,
                               int lowerBound, bool canBeSkipped)
    {
        string readedString = "";
        int value;
        do
        {
            Console.WriteLine(messageToUser);
            readedString = Console.ReadLine();
            if (readedString.Length == 0)
            {
                SkipThisOrReportToUser(canBeSkipped);
            }
            else
            {
                if (!int.TryParse(readedString, out value))
                {
                    Console.WriteLine(MessagesForUser.UNCORRECT_NUMBER);
                }
                else
                {
                    if (value < lowerBound)
                    {
                        Console.WriteLine("Uncorrect " + nameOfNeededValue + " of polygon");
                    }
                    else
                    {
                        return value;
                    }
                }
            }
            Program.AskUserAboutRepeatingEntering();
        } while (true);
    }

    public static int GetPolygonAttribute(string messageToUser, string nameOfNeededValue,
                                   int lowerBound, int higherBound, bool canBeSkipped)
    {
        string readedString = "";
        int value;
        do
        {
            Console.WriteLine(messageToUser);
            readedString = Console.ReadLine();
            if (readedString.Length == 0)
            {
                SkipThisOrReportToUser(canBeSkipped);
            }
            else
            {
                if (!int.TryParse(readedString, out value))
                {
                    Console.WriteLine(MessagesForUser.UNCORRECT_NUMBER);
                }
                else
                {
                    if ((value < lowerBound) || (value > higherBound))
                    {
                        Console.WriteLine("Uncorrect " + nameOfNeededValue + " of polygon");
                    }
                    else
                    {
                        return value;
                    }
                }
            }
            Program.AskUserAboutRepeatingEntering();
        } while (true);
    }

    static void SkipThisOrReportToUser(bool canBeSkipped)
    {
        if (canBeSkipped)
        {
            throw new ValueWasSkippedException();
        }
        Console.WriteLine(MessagesForUser.EMPTY_INPUT_STRING);
    }

    public static int GetNumberOfSides(int selectedPolygonType)
    {
        switch (selectedPolygonType)
        {
            case PolygonType.TRIANGLE: return 3;
            case PolygonType.PARALLELOGRAM: return 4;
            case PolygonType.PENTAGON: return 5;
            case PolygonType.HEXAGON: return 6;
            case PolygonType.HEPTAGON: return 7;
            default: return 0;
        }
    }

    static void ContinueWorkingWithTypeOrCancel(int selectedTypeOfPolygon)
    {
        if (selectedTypeOfPolygon == PolygonType.GO_BACK)
        {
            throw new OperationWasCancelledException();
        }
        return;
    }

    public static int ReadPosition(int higherBound)
    {
        int position;
        int lowerBound = 0;
        do
        {
            Console.WriteLine("Please, Enter position of element. \nMinimal position:" + lowerBound + "\nMaximal position: " +
            higherBound);
            string readedString = Console.ReadLine();
            if (readedString.Length == 0)
            {
                Console.WriteLine(MessagesForUser.EMPTY_INPUT_STRING);
            }
            else if (!int.TryParse(readedString, out position))
            {
                Console.WriteLine(MessagesForUser.UNCORRECT_NUMBER);
            }
            else if ((position < lowerBound) || (position > higherBound))
            {
                Console.WriteLine(MessagesForUser.POSITION_OUT_OF_RANGE);
            }
            else
            {
                return position;
            }
            Program.AskUserAboutRepeatingEntering();
        } while (true);
    }
}
