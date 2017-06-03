namespace FourthLab
{
    public static class Menues
    {
        public struct MenuElement
        {
            public string description;
            public int id;
        }

        public static MenuElement[] generalMenu;
        public static MenuElement[] PolygonTypeMenu;
        public static MenuElement[] workWithFilesMenu;

        static Menues()
        {
            PolygonTypeMenuInitializer();
            GeneralMenuInitializer();
            WorkWithFilesMenuInitializer();
        }

        private static void WorkWithFilesMenuInitializer()
        {
            workWithFilesMenu = new MenuElement[6];
            workWithFilesMenu[0].id = IdItemsOfWorkWithFilesMenu.SAVE_COLLECTION;
            workWithFilesMenu[0].description = " 1 - Save collection";
            workWithFilesMenu[1].id = IdItemsOfWorkWithFilesMenu.LOAD_COLLECTION;
            workWithFilesMenu[1].description = " 2 - Load collection";
            workWithFilesMenu[2].id = IdItemsOfWorkWithFilesMenu.IS_FILE_LOADED;
            workWithFilesMenu[2].description = " 3 - Is file loaded?";
            workWithFilesMenu[4].id = IdItemsOfWorkWithFilesMenu.IS_FILE_LOCKED;
            workWithFilesMenu[4].description = " 5 - Is file locked?";
            workWithFilesMenu[3].id = IdItemsOfWorkWithFilesMenu.IS_CHANGES_SAVED;
            workWithFilesMenu[3].description = " 4 - Is changed saved?";
            workWithFilesMenu[5].id = IdItemsOfWorkWithFilesMenu.GO_BACK;
            workWithFilesMenu[5].description = " 6 - Return back to menu";
        }

        private static void PolygonTypeMenuInitializer()
        {
            PolygonTypeMenu = new MenuElement[6];
            PolygonTypeMenu[0].id = PolygonType.TRIANGLE;
            PolygonTypeMenu[0].description = " 1 - Triangle";
            PolygonTypeMenu[1].id = PolygonType.PARALLELOGRAM;
            PolygonTypeMenu[1].description = " 2 - Parallelogram";
            PolygonTypeMenu[2].id = PolygonType.PENTAGON;
            PolygonTypeMenu[2].description = " 3 - Pentagon";
            PolygonTypeMenu[3].id = PolygonType.HEXAGON;
            PolygonTypeMenu[3].description = " 4 - Hexagon";
            PolygonTypeMenu[4].id = PolygonType.HEPTAGON;
            PolygonTypeMenu[4].description = " 5 - Heptagon";
            PolygonTypeMenu[5].id = PolygonType.GO_BACK;
            PolygonTypeMenu[5].description = " 6 - Return back to menu";
        }

        private static void GeneralMenuInitializer()
        {
            generalMenu = new MenuElement[10];
            generalMenu[0].id = IdItemsOfGeneralMenu.APPEND;
            generalMenu[0].description = " 1 - Append Element";
            generalMenu[1].id = IdItemsOfGeneralMenu.ADD_NEW_TO_POSITION;
            generalMenu[1].description = " 2 - Inject Element to position";
            generalMenu[2].id = IdItemsOfGeneralMenu.POP_POLYGON;
            generalMenu[2].description = " 3 - Pop Element";
            generalMenu[3].id = IdItemsOfGeneralMenu.REMOVE_POLYGON_FROM_POSITION;
            generalMenu[3].description = " 4 - Remove Element from position";
            generalMenu[4].id = IdItemsOfGeneralMenu.REMOVE_POLYGON_WITH_ID;
            generalMenu[4].description = " 5 - Remove Element by Id";
            generalMenu[5].id = IdItemsOfGeneralMenu.FIND_POLYGON_BY_ID;
            generalMenu[5].description = " 6 - Find Element by Id";
            generalMenu[6].id = IdItemsOfGeneralMenu.PRINT_ALL_POLYGONS;
            generalMenu[6].description = " 7 - Print All Elements";
            generalMenu[7].id = IdItemsOfGeneralMenu.PRINT_POLYGONS_WITH_TYPE;
            generalMenu[7].description = " 8 - Print Elements by type";
            generalMenu[8].id = IdItemsOfGeneralMenu.WORK_WITH_FILES;
            generalMenu[8].description = " 9 - Work with files";
            generalMenu[9].id = IdItemsOfGeneralMenu.EXIT;
            generalMenu[9].description = " 10 - Close program";
        }
    }

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
        public const int PRINT_POLYGONS_WITH_TYPE = 8;
        public const int WORK_WITH_FILES = 9;
        public const int EXIT = 10;
    }

    public static class PolygonType
    {
        public const int UNDEFINED = -1;
        public const int TRIANGLE = 1;
        public const int PARALLELOGRAM = 2;
        public const int PENTAGON = 3;
        public const int HEXAGON = 4;
        public const int HEPTAGON = 5;
        public const int GO_BACK = 6;
    }

    public static class IdItemsOfWorkWithFilesMenu
    {
        public const int UNDEFINED = -1;
        public const int SAVE_COLLECTION = 1;
        public const int LOAD_COLLECTION = 2;
        public const int IS_FILE_LOADED = 3;
        public const int IS_CHANGES_SAVED = 4;
        public const int IS_FILE_LOCKED = 5;
        public const int GO_BACK = 6;
    }
}
