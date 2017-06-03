using System;
using Third_Lab;

public static class MenuItemHandler
{
    public static void HandleSelectedGeneralMenuItem(int selectedMenuItem, ArrayPolygon arrayPolygon)
    {
        Polygon[] polygons;
        Polygon polygon;
        int position;
        int id;
        switch (selectedMenuItem)
        {
            case IdItemsOfGeneralMenu.APPEND:
                polygon = PolygonCreator.CreatePolygon();
                arrayPolygon.AppendElement(polygon);
                Console.WriteLine(MessagesForUser.SUCCESSFUL);
                break;
            case IdItemsOfGeneralMenu.ADD_NEW_TO_POSITION:
                polygon = PolygonCreator.CreatePolygon();
                position = PositionReader(arrayPolygon.Length());
                arrayPolygon.AddElement(polygon, position);
                Console.WriteLine(MessagesForUser.SUCCESSFUL);
                break;
            case IdItemsOfGeneralMenu.POP_POLYGON:
                if (!IsPossibleWorkWithExistsPolygons(arrayPolygon)) { return; }
                arrayPolygon.PopElement();
                Console.WriteLine(MessagesForUser.SUCCESSFUL);
                break;
            case IdItemsOfGeneralMenu.REMOVE_POLYGON_FROM_POSITION:
                if (!IsPossibleWorkWithExistsPolygons(arrayPolygon)) { return; }
                position = PositionReader(arrayPolygon.Length() - 1);
                arrayPolygon.RemoveElement(position);
                Console.WriteLine(MessagesForUser.SUCCESSFUL);
                break;
            case IdItemsOfGeneralMenu.REMOVE_POLYGON_WITH_ID:
                id = PolygonCreator.GetPolygonAttribute(MessagesForUser.ENTERING_ID_FOR_NEW_POLYGON, "id", 0, false);
                if (arrayPolygon.RemoveElementById(id))
                { Console.WriteLine(MessagesForUser.SUCCESSFUL); }
                else { Console.WriteLine(MessagesForUser.NOT_POSSIBLE_BECAUSE_NOT_RESULTS_OF_SEARCHING_POLYGON); }
                break;
            case IdItemsOfGeneralMenu.FIND_POLYGON_BY_ID:
                id = PolygonCreator.GetPolygonAttribute(MessagesForUser.ENTERING_ID_FOR_NEW_POLYGON, "id", 0, false);
                polygon = arrayPolygon.FindPolygon(id);
                DisplayFoundedPolygon(polygon);
                break;
            case IdItemsOfGeneralMenu.PRINT_ALL_POLYGONS:
                if (!IsPossibleWorkWithExistsPolygons(arrayPolygon)) { return; }
                polygons = arrayPolygon.GetAllPolygons();
                ShowAllPolygons(polygons);
                break;
            case IdItemsOfGeneralMenu.EXIT:
                Environment.Exit(0);
                break;
            default:
                throw new OperationWasCrashed();
        }
    }

    static int PositionReader(int higherBound)
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

    static bool IsPossibleWorkWithExistsPolygons(ArrayPolygon arrayPolygon)
    {
        if (arrayPolygon.Length() == 0)
        {
            Console.WriteLine(MessagesForUser.NOT_POSSIBLE_WITHOUT_POLYGONS);
            return false;
        }
        return true;
    }

    static void DisplayFoundedPolygon(Polygon polygon)
    {
        Console.WriteLine(MessagesForUser.ELEMENT_FOUNDED);
        Console.WriteLine(polygon);
    }

    static void ShowAllPolygons(Polygon[] polygons)
    {
        for (int i = 0; i < polygons.Length; i++)
        {
            Console.WriteLine(polygons[i]);
        }
    }
}
