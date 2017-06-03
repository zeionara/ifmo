using System;

public static class IdItemsOfGeneralMenu
{
    public const int UNDEFINED = -1;
    public const int APPEND = 1;
    public const int ADD_NEW_TO_POSITION = 2;
    public const int POP_POLYGON = 3;
    public const int REMOVE_POLYGON_FROM_POSITION = 4;
    public const int REMOVE_POLYGON_WITH_ID = 5;
    public const int FIND_POLYGON_BY_ID = 6;
    public const int PRINT_ALL_POLYGONS = 7;
    public const int EXIT = 8;
}

public static class IdItemsOfPolygonTypeMenu
{
    public const int UNDEFINED = -1;
    public const int TRIANGLE = 1;
    public const int PARALLELOGRAM = 2;
    public const int PENTAGON = 3;
    public const int HEXAGON = 4;
    public const int HEPTAGON = 5;
    public const int GO_BACK = 6;
}

public static class MessagesForUser
{
    public const string SUCCESSFUL = "Successfully done";
    public const string SELECTING_MENU_ITEM = "Please, enter bellow code of action and press <Enter>";
    public const string INVALID_SELECTION_MENU_ITEM = "You enter uncorrect code";
    public const string EMPTY_INPUT_STRING = "You didn't enter nothing";
    public const string NOT_POSSIBLE_WITHOUT_POLYGONS = "Isn't possible, no one polygon";
    public const string NOT_POSSIBLE_BECAUSE_NOT_RESULTS_OF_SEARCHING_POLYGON =
                                        "Isn't possible, element not founded";
    public const string ELEMENT_FOUNDED = "Element founded";
    public const string UNCORRECT_NUMBER = "Uncorrect number";
    public const string POSITION_OUT_OF_RANGE = "Position out of range";
    public const string ENTERING_ID_FOR_NEW_POLYGON = "Enter Id of new polygon (integer number > 0):";
    public const string CREATING_POLYGON_IN_PROCESS = "Creating a polygon...";
    public const string WHAT_WILL_CREATES = "What do you want to create?";
    public const string SIDES_WILL_SETS_BY_DEFAULT = "Lengths of sides will sets as default";
}

public static class Menues
{
    public struct MenuElement
    {
        public string description;
        public int id;
    }

    public static MenuElement[] generalMenu;
    public static MenuElement[] PolygonTypeMenu;

    static Menues()
    {
        PolygonTypeMenuInitializer();
        GeneralMenuInitializer();
    }

    private static void PolygonTypeMenuInitializer()
    {
        PolygonTypeMenu = new MenuElement[6];
        PolygonTypeMenu[0].id = IdItemsOfPolygonTypeMenu.TRIANGLE;
        PolygonTypeMenu[0].description = " 1 - Create new Triangle";
        PolygonTypeMenu[1].id = IdItemsOfPolygonTypeMenu.PARALLELOGRAM;
        PolygonTypeMenu[1].description = " 2 - Create new Parallelogram";
        PolygonTypeMenu[2].id = IdItemsOfPolygonTypeMenu.PENTAGON;
        PolygonTypeMenu[2].description = " 3 - Create new Pentagon";
        PolygonTypeMenu[3].id = IdItemsOfPolygonTypeMenu.HEXAGON;
        PolygonTypeMenu[3].description = " 4 - Create new Hexagon";
        PolygonTypeMenu[4].id = IdItemsOfPolygonTypeMenu.HEPTAGON;
        PolygonTypeMenu[4].description = " 5 - Create new Heptagon";
        PolygonTypeMenu[5].id = IdItemsOfPolygonTypeMenu.GO_BACK;
        PolygonTypeMenu[5].description = " 6 - Return back to menu";
    }

    private static void GeneralMenuInitializer()
    {
        generalMenu = new MenuElement[8];
        generalMenu[0].id = IdItemsOfGeneralMenu.APPEND;
        generalMenu[0].description = " 1 - Append Element";
        generalMenu[1].id = IdItemsOfGeneralMenu.ADD_NEW_TO_POSITION;
        generalMenu[1].description = " 2 - Add Element to position";
        generalMenu[2].id = IdItemsOfGeneralMenu.POP_POLYGON;
        generalMenu[2].description = " 3 - Pop Element";
        generalMenu[3].id = IdItemsOfGeneralMenu.REMOVE_POLYGON_FROM_POSITION;
        generalMenu[3].description = " 4 - Remove Element from position";
        generalMenu[4].id = IdItemsOfGeneralMenu.REMOVE_POLYGON_WITH_ID;
        generalMenu[4].description = " 5 - Remove Element with Id";
        generalMenu[5].id = IdItemsOfGeneralMenu.FIND_POLYGON_BY_ID;
        generalMenu[5].description = " 6 - Find Element by Id";
        generalMenu[6].id = IdItemsOfGeneralMenu.PRINT_ALL_POLYGONS;
        generalMenu[6].description = " 7 - Print All Elements";
        generalMenu[7].id = IdItemsOfGeneralMenu.EXIT;
        generalMenu[7].description = " 8 - Close program";
    }
}
