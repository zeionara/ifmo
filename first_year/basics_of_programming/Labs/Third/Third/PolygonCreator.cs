using System;
using Third_Lab;

public static class PolygonCreator
{
    public static Polygon CreatePolygon()
    {
        Console.WriteLine(MessagesForUser.CREATING_POLYGON_IN_PROCESS);
        Console.WriteLine(MessagesForUser.WHAT_WILL_CREATES);
        MenuItemSelector.DisplayMenu(Menues.PolygonTypeMenu);
        int selectedPolygonTypeMenuItem = MenuItemSelector.SelectMenuItem(Menues.PolygonTypeMenu);
        ContinueCreatingOrCancel(selectedPolygonTypeMenuItem);
        int numberOfSides = GetNumberOfSides(selectedPolygonTypeMenuItem);
        int id = GetPolygonAttribute(MessagesForUser.ENTERING_ID_FOR_NEW_POLYGON, "id", 0, false);
        int[] sides = new int[numberOfSides];
        try
        {
            sides[0] = GetPolygonAttribute("Enter length of 1 side (integer number >= 1):",
                    "length of side", 1, true);
        }
        catch (ValueWasSkipped exception)
        {
            Console.WriteLine(MessagesForUser.SIDES_WILL_SETS_BY_DEFAULT);
            switch (selectedPolygonTypeMenuItem)
            {
                case IdItemsOfPolygonTypeMenu.TRIANGLE: return new Triangle(id);
                case IdItemsOfPolygonTypeMenu.PARALLELOGRAM: return new Parallelogram(id);
                case IdItemsOfPolygonTypeMenu.PENTAGON: return new Pentagon(id);
                case IdItemsOfPolygonTypeMenu.HEXAGON: return new Hexagon(id);
                case IdItemsOfPolygonTypeMenu.HEPTAGON: return new Heptagon(id);
                default: throw new OperationWasCrashed();
            }
        }
        for (int i = 1; i < numberOfSides; i++)
        {
            if ((numberOfSides != GetNumberOfSides(IdItemsOfPolygonTypeMenu.TRIANGLE))
                || (i < GetNumberOfSides(IdItemsOfPolygonTypeMenu.TRIANGLE) - 1))
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
            case IdItemsOfPolygonTypeMenu.TRIANGLE: return new Triangle(id, sides);
            case IdItemsOfPolygonTypeMenu.PARALLELOGRAM: return new Parallelogram(id, sides);
            case IdItemsOfPolygonTypeMenu.PENTAGON: return new Pentagon(id, sides);
            case IdItemsOfPolygonTypeMenu.HEXAGON: return new Hexagon(id, sides);
            case IdItemsOfPolygonTypeMenu.HEPTAGON: return new Heptagon(id, sides);
            default: throw new OperationWasCrashed();
        }
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
            throw new ValueWasSkipped();
        }
        Console.WriteLine(MessagesForUser.EMPTY_INPUT_STRING);
    }

    static int GetNumberOfSides(int selectedPolygonType)
    {
        switch (selectedPolygonType)
        {
            case IdItemsOfPolygonTypeMenu.TRIANGLE: return 3;
            case IdItemsOfPolygonTypeMenu.PARALLELOGRAM: return 4;
            case IdItemsOfPolygonTypeMenu.PENTAGON: return 5;
            case IdItemsOfPolygonTypeMenu.HEXAGON: return 6;
            case IdItemsOfPolygonTypeMenu.HEPTAGON: return 7;
            default: return 0;
        }
    }

    static void ContinueCreatingOrCancel(int selectedTypeOfPolygon)
    {
        if (selectedTypeOfPolygon == IdItemsOfPolygonTypeMenu.GO_BACK)
        {
            throw new OperationWasCancelled();
        }
        return;
    }
}
