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

        static MenuElement[] generalMenu;
        static MenuElement[] PolygonTypeMenu;

        static ArrayPolygon arrayPolygon = new ArrayPolygon();

        static void Main(string[] args)
        {
            int selectedGeneralMenuItem = IdItemsOfGeneralMenu.UNDEFINED;
            GeneralMenuInitializer();
            PolygonTypeMenuInitializer();
            while (true)
            {
                DisplayMenu(generalMenu);
                selectedGeneralMenuItem = SelectMenuItem(generalMenu);
                try
                {

                    HandleSelectedGeneralMenuItem(selectedGeneralMenuItem);

                } catch (Exception exception)
                {
                    Console.WriteLine(exception);
                }
            }
        }

        static void PolygonTypeMenuInitializer()
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

        static void GeneralMenuInitializer()
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
                Console.WriteLine(MessagesForUser.SELECTING_MENU_ITEM);
                string readedString = Console.ReadLine();
                int selectedElement;
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
                        Console.WriteLine(MessagesForUser.INVALID_SELECTION_MENU_ITEM);
                    }
                }
                else
                {
                    Console.WriteLine(MessagesForUser.EMPTY_INPUT_STRING);
                }
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

        static void DisplayFoundedPolygon (Polygon polygon)
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

        static void HandleSelectedGeneralMenuItem(int selectedMenuItem)
        {
            Polygon[] polygons;
            Polygon polygon;
            int position;
            int id;
            switch (selectedMenuItem)
            {
                case IdItemsOfGeneralMenu.APPEND:
                    polygon = CreatePolygon();
                    arrayPolygon.AppendElement(polygon);
                    Console.WriteLine(MessagesForUser.SUCCESSFUL);
                    break;
                case IdItemsOfGeneralMenu.ADD_NEW_TO_POSITION:
                    polygon = CreatePolygon();
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
                    id = GetPolygonAttribute(MessagesForUser.ENTERING_ID_FOR_NEW_POLYGON, "id", 0, false);
                    if (arrayPolygon.RemoveElementById(id))
                    {   Console.WriteLine(MessagesForUser.SUCCESSFUL);  }
                    else  {     Console.WriteLine(MessagesForUser.NOT_POSSIBLE_BECAUSE_NOT_RESULTS_OF_SEARCHING_POLYGON);   }
                    break;
                case IdItemsOfGeneralMenu.FIND_POLYGON_BY_ID:
                    id = GetPolygonAttribute(MessagesForUser.ENTERING_ID_FOR_NEW_POLYGON, "id", 0, false);
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

        static void AskUserAboutRepeatingEntering()
        {
            char agree = 'y';
            char disagree = 'n';
            string inputString;
            do
            {
                Console.WriteLine("Do you want to try again?\nType "+agree+" or "+disagree+" and press Enter");
                inputString = Console.ReadLine();
            } while ((inputString.Length != 1) || ((inputString[0] != agree) && (inputString[0] != disagree)));
            if (inputString[0] == disagree)
            {
                throw new OperationWasCancelled();
            }
            return;
        }

        static void SkipThisOrReportToUser(bool canBeSkipped)
        {
            if (canBeSkipped)
            {
                throw new ValueWasSkipped();
            }
            Console.WriteLine(MessagesForUser.EMPTY_INPUT_STRING);
        }

        static int GetPolygonAttribute(string messageToUser, string nameOfNeededValue, 
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
                AskUserAboutRepeatingEntering();
            } while (true);
        }

        static int GetPolygonAttribute(string messageToUser, string nameOfNeededValue,
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
                AskUserAboutRepeatingEntering();
            } while (true);
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

        static Polygon CreatePolygon()
        {
            Console.WriteLine(MessagesForUser.CREATING_POLYGON_IN_PROCESS);
            Console.WriteLine(MessagesForUser.WHAT_WILL_CREATES);
            DisplayMenu(PolygonTypeMenu);
            int selectedPolygonTypeMenuItem = SelectMenuItem(PolygonTypeMenu);
            ContinueCreatingOrCancel(selectedPolygonTypeMenuItem);
            int numberOfSides = GetNumberOfSides(selectedPolygonTypeMenuItem);
            int id = GetPolygonAttribute(MessagesForUser.ENTERING_ID_FOR_NEW_POLYGON, "id", 0, false);
            int[] sides = new int[numberOfSides];
            try
            {
                sides[0] = GetPolygonAttribute("Enter length of 1 side (integer number >= 1):",
                        "length of side", 1, true);
            } catch (ValueWasSkipped exception)
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
                    || (i < GetNumberOfSides(IdItemsOfPolygonTypeMenu.TRIANGLE)-1))
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
                AskUserAboutRepeatingEntering();
            } while (true);
        }
    }
}
