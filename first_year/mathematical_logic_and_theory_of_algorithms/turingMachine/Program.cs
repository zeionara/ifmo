using System;

namespace Third_Lab
{
    class Program
    {
        struct MenuElement
        {
            public string description;
            public int id;
        }

        static MenuElement[] menuGeneral;
        static MenuElement[] menuSelectingPolygonType;

        static ArrayPolygon arrayPolygon = new ArrayPolygon();

        const int CANCELLED = -1;
        const int SKIPED = -2;

        public static class ElementsOfMenuGeneral
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

        public static class ElementsOfMenuSelectingPolygonType
        {
            public const int TRIANGLE = 1;
            public const int PARALLELOGRAM = 2;
            public const int PENTAGON = 3;
            public const int HEXAGON = 4;
            public const int HEPTAGON = 5;
            public const int GO_BACK = 6;
        }
        

        static void Main(string[] args)
        {
            Console.Derad();

            int activeGeneralMenuElement = ElementsOfMenuGeneral.UNDEFINED;
            MenuInitializer();
            ElementSubMenuInitializer();
            while (true)
            {
                DisplayMenu(menuGeneral);
                activeGeneralMenuElement = SelectMenuItem(menuGeneral);
                HandleMenuElements(activeGeneralMenuElement);
            }
        }

        static void ElementSubMenuInitializer()
        {
            menuSelectingPolygonType = new MenuElement[6];
            menuSelectingPolygonType[0].id = ElementsOfMenuSelectingPolygonType.TRIANGLE;
            menuSelectingPolygonType[0].description = " 1 - Create new Triangle";
            menuSelectingPolygonType[1].id = ElementsOfMenuSelectingPolygonType.PARALLELOGRAM;
            menuSelectingPolygonType[1].description = " 2 - Create new Parallelogram";
            menuSelectingPolygonType[2].id = ElementsOfMenuSelectingPolygonType.PENTAGON;
            menuSelectingPolygonType[2].description = " 3 - Create new Pentagon";
            menuSelectingPolygonType[3].id = ElementsOfMenuSelectingPolygonType.HEXAGON;
            menuSelectingPolygonType[3].description = " 4 - Create new Hexagon";
            menuSelectingPolygonType[4].id = ElementsOfMenuSelectingPolygonType.HEPTAGON;
            menuSelectingPolygonType[4].description = " 5 - Create new Heptagon";
            menuSelectingPolygonType[5].id = ElementsOfMenuSelectingPolygonType.GO_BACK;
            menuSelectingPolygonType[5].description = " 6 - Return back to menu";
        }

        static void MenuInitializer()
        {
            menuGeneral = new MenuElement[8];
            menuGeneral[0].id = ElementsOfMenuGeneral.APPEND;
            menuGeneral[0].description = " 1 - ASeeeeeeeeeAppend Element";
            menuGeneral[1].id = ElementsOfMenuGeneral.ADD_NEW_TO_POSITION;
            menuGeneral[1].description = " 2 - Add Element to position";
            menuGeneral[2].id = ElementsOfMenuGeneral.POP_POLYGON;
            menuGeneral[2].description = " 3 - Pop Element";
            menuGeneral[3].id = ElementsOfMenuGeneral.REMOVE_POLYGON_FROM_POSITION;
            menuGeneral[3].description = " 4 - Remove Element from position";
            menuGeneral[4].id = ElementsOfMenuGeneral.REMOVE_POLYGON_WITH_ID;
            menuGeneral[4].description = " 5 - Remove Element with Id";
            menuGeneral[5].id = ElementsOfMenuGeneral.FIND_POLYGON_BY_ID;
            menuGeneral[5].description = " 6 - Find Element by Id";
            menuGeneral[6].id = ElementsOfMenuGeneral.PRINT_ALL_POLYGONS;
            menuGeneral[6].description = " 7 - Print All Elements";
            menuGeneral[7].id = ElementsOfMenuGeneral.EXIT;
            menuGeneral[7].description = " 8 - Close program";
        }

        static void DisplayMenu(MenuElement[] menu)
        {
            for (int i = 0; i < menu.Length; i++)
            {
                Console.WriteLine(menu[i].description);
            }
        }

        static int SelectMenuItem(MenuElement[] menu)
        {
            int max = menu.Length;
            do
            {
                Console.WriteLine("Please, enter bellow code of action and press <Enter>");
                string readedString = Console.ReadLine();
                int selectedElement = 0;
                if (readedString.Length > 0)
                {
                    if ((int.TryParse(readedString, out selectedElement)) &&
                        (selectedElement > 0) &&
                        (selectedElement <= max))
                    {
                        return selectedElement;
                    }
                    else
                    {
                        Console.WriteLine("You enter uncorrect code");
                    }
                }
                else
                {
                    Console.WriteLine("You did't enter nothing");
                }
            } while (true);
        }

        static void HandleMenuElements(int idOfActiveMenuElement)
        {
            Polygon[] polygons;
            Polygon polygon;
            int position;
            int id;
            switch (idOfActiveMenuElement)
            {
                case ElementsOfMenuGeneral.APPEND:
                    polygon = PolygonCreator();
                    if (polygon == null)
                    {
                        Console.WriteLine("Cancelled by User");
                        return;
                    }
                    arrayPolygon.AppendElement(polygon);
                    Console.WriteLine("Succesfully done");
                    break;
                case ElementsOfMenuGeneral.ADD_NEW_TO_POSITION:
                    polygon = PolygonCreator();
                    if (polygon == null)
                    {
                        Console.WriteLine("Cancelled by User");
                        return;
                    }
                    position = PositionReader(arrayPolygon.Length());
                    if (position == CANCELLED)
                    {
                        Console.WriteLine("Cancelled by User");
                        return;
                    }
                    arrayPolygon.AddElement(polygon, position);
                    Console.WriteLine("Succesfully done");
                    break;
                case ElementsOfMenuGeneral.POP_POLYGON:
                    if (arrayPolygon.Length() == 0)
                    {
                        Console.WriteLine("Isn't possible, no one polygon");
                        return;
                    }
                    arrayPolygon.PopElement();
                    Console.WriteLine("Succesfully done");
                    break;
                case ElementsOfMenuGeneral.REMOVE_POLYGON_FROM_POSITION:
                    if (arrayPolygon.Length() == 0)
                    {
                        Console.WriteLine("Isn't possible, no one polygon");
                    }
                    position = PositionReader(arrayPolygon.Length() - 1);
                    if (position == CANCELLED)
                    {
                        Console.WriteLine("Cancelled by User");
                        return;
                    }
                    arrayPolygon.RemoveElement(position);
                    Console.WriteLine("Succesfully done");
                    break;
                case ElementsOfMenuGeneral.REMOVE_POLYGON_WITH_ID:
                    id = GetPolygonInfo("Enter Id of new polygon (integer number > 0):", "id", 0, false);
                    if (id == CANCELLED)
                    {
                        Console.WriteLine("Cancelled by User");
                        return;
                    }
                    if (arrayPolygon.RemoveElementById(id))
                    {
                        Console.WriteLine("Succesfully done");
                    }
                    else
                    {
                        Console.WriteLine("Isn't possible, element not founded");
                    }
                    break;
                case ElementsOfMenuGeneral.FIND_POLYGON_BY_ID:
                    id = GetPolygonInfo("Enter Id of new polygon (integer number > 0):", "id", 0, false);
                    if (id == CANCELLED)
                    {
                        Console.WriteLine("Cancelled by User");
                        return;
                    }
                    polygon = arrayPolygon.FindElement(id);
                    if (polygon == null)
                    {
                        Console.WriteLine("Isn't possible, element not founded");
                        return;
                    }
                    Console.WriteLine("Element founded");
                    Console.WriteLine(polygon);
                    break;
                case ElementsOfMenuGeneral.PRINT_ALL_POLYGONS:
                    if (arrayPolygon.Length() == 0)
                    {
                        Console.WriteLine("No one polygon in list");
                        return;
                    }
                    polygons = arrayPolygon.GetAllPolygons();
                    for (int i = 0; i < polygons.Length; i++)
                    {
                        //Console.WriteLine("Polygon " + (i + 1));
                        Console.WriteLine(polygons[i]);
                    }
                    break;
                case ElementsOfMenuGeneral.EXIT:
                    Environment.Exit(0);
                    break;
            }
        }

        static char RepeatRequest()
        {
            string inputString;
            do
            {
                Console.WriteLine("Do you want to try again?\nType y or n and press Enter");
                inputString = Console.ReadLine();
            } while ((inputString.Length != 1) || ((inputString[0] != 'y') && (inputString[0] != 'n')));
            return inputString[0];
        }

        static int GetPolygonInfo(string message, string nameOfPartOfInfo, int minimal, bool canBeSkip)
        {
            string readedString = "";
            int info;
            if (minimal < 0)
            {
                minimal = 0;
            }
            do
            {
                Console.WriteLine(message);
                readedString = Console.ReadLine();
                if (readedString.Length == 0)
                {
                    if (canBeSkip)
                    {
                        return SKIPED;
                    }
                    Console.WriteLine("No one symbol in string");
                }
                else
                {
                    if (!int.TryParse(readedString, out info))
                    {
                        Console.WriteLine("Uncorrect number");
                    }
                    else
                    {
                        if (info < minimal)
                        {
                            Console.WriteLine("Uncorrect " + nameOfPartOfInfo + " of polygon");
                        }
                        else
                        {
                            return info;
                        }
                    }
                }

                if (RepeatRequest() != 'y')
                {
                    return CANCELLED;
                }
            } while (true);
        }

        static int GetPolygonInfo(string message, string nameOfPartOfInfo, int minimal, bool canBeSkip,
                                  int maximal)
        {
            string readedString = "";
            int info;
            if (minimal < 0)
            {
                minimal = 0;
            }
            do
            {
                Console.WriteLine(message);
                readedString = Console.ReadLine();
                if (readedString.Length == 0)
                {
                    if (canBeSkip)
                    {
                        return SKIPED;
                    }
                    Console.WriteLine("No one symbol in string");
                }
                else
                {
                    if (!int.TryParse(readedString, out info))
                    {
                        Console.WriteLine("Uncorrect number");
                    }
                    else
                    {
                        if ((info < minimal) || (info > maximal))
                        {
                            Console.WriteLine("Uncorrect " + nameOfPartOfInfo + " of polygon");
                        }
                        else
                        {
                            return info;
                        }
                    }
                }

                if (RepeatRequest() != 'y')
                {
                    return CANCELLED;
                }
            } while (true);
        }

        static int DecodePolygonSelection(int idOfActiveSubMenuElement)
        {
            switch (idOfActiveSubMenuElement)
            {
                case TRIANGLE: return 3;
                case PARALLELOGRAM: return 4;
                case PENTAGON: return 5;
                case HEXAGON: return 6;
                default: return 7;
            }
        }

        static Polygon PolygonCreator()
        {
            Console.WriteLine("Creating a polygon...");
            Console.WriteLine("What do you want to create?");
            OutputMenu(menuSelectingPolygonType);
            int idOfActiveSubMenuElement = RequestProcessor(menuSelectingPolygonType);
            if (idOfActiveSubMenuElement == 6)
            {
                return null;
            }
            int numberOfSides = DecodePolygonSelection(idOfActiveSubMenuElement);
            int id = GetPolygonInfo("Enter Id (integer number > 0):", "id", 0, false);
            if (id == CANCELLED)
            {
                return null;
            }
            int[] sides = new int[numberOfSides];
            sides[0] = GetPolygonInfo("Enter length of 1 side (integer number >= 1):",
                        "length of side", 1, true);
            if (sides[0] == CANCELLED)
            {
                return null;
            }
            if (sides[0] != SKIPED)
            {
                for (int i = 1; i < numberOfSides; i++)
                {
                    if ((numberOfSides != 3) || (i < 2))
                    {
                        sides[i] = GetPolygonInfo("Enter length of " + (i + 1) + " side (integer number >= 1):",
                            "length of side",1, false);
                    } else
                    {
                        sides[i] = GetPolygonInfo("Enter length of " + (i + 1) + 
                            " side (integer number >= 1 and <= " + (sides[0] + sides[1]) + "):",
                            "length of side", 1, false, sides[0]+sides[1]);
                    }
                    if (sides[i] == CANCELLED)
                    {
                        return null;
                    }
                }
                switch (numberOfSides)
                {
                    case 3: return new Triangle(id, sides);
                    case 4: return new Parallelogram(id, sides);
                    case 5: return new Pentagon(id, sides);
                    case 6: return new Hexagon(id, sides);
                    default: return new Heptagon(id, sides);
                }
            }
            else
            {
                switch (numberOfSides)
                {
                    case 3: return new Triangle(id);
                    case 4: return new Parallelogram(id);
                    case 5: return new Pentagon(id);
                    case 6: return new Hexagon(id);
                    default: return new Heptagon(id);
                }
            }
        }

        static int PositionReader(int max)
        {
            int position = -1;
            int min = 0;
            do
            {
                Console.WriteLine("Please, Enter position of element. \nMinimal position: 0\nMaximal position: " +
                max);
                string readedString = Console.ReadLine();
                if (readedString.Length == 0)
                {
                    Console.WriteLine("No one symbol in string");
                }
                else if (!int.TryParse(readedString, out position))
                {
                    Console.WriteLine("Entered not a number");
                }
                else if ((position < min) || (position > max))
                {
                    Console.WriteLine("Position out of range");
                }
                else
                {
                    return position;
                }
                if (RepeatRequest() == 'y')
                {
                    continue;
                }
                else
                {
                    return CANCELLED;
                }
            } while (true);
        }

    }
}