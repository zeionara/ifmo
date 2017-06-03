using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Third_Lab
{
    class Program
    {
        struct MenuElement
        {
            public string name;
            public int id;
        }

        static MenuElement[] menu = new MenuElement[1];
        static MenuElement[] elementSubMenu = new MenuElement[1];
        static int idOfActiveMenuElement = 0;
        static int idOfActiveSubMenuElement = 0;
        static ArrayPolygon arrayPolygon = new ArrayPolygon();

        const int CANCELLED = -1;
        const int SKIPED = -2;

        const int CREATE_NEW_POLYGON = 1;
        const int CREATE_NEW_POLYGON_IN_POSITION = 2;
        const int POP_POLYGON = 3;
        const int REMOVE_POLYGON_FROM_POSITION = 4;
        const int REMOVE_POLYGON_WITH_ID = 5;
        const int FIND_POLYGON_BY_ID = 6;
        const int SHOW_ALL_POLYGONS = 7;

        const int TRIANGLE = 1;
        const int PARALLELOGRAM = 2;
        const int PENTAGON = 3;
        const int HEXAGON = 4;

        static void Main(string[] args)
        {
            MenuInitializer();
            ElementSubMenuInitializer();
            while (true)
            {
                OutputMenu(menu);
                RequestProcessor(8, ref idOfActiveMenuElement, true, menu);
                DataProcessor();
            }
        }

        static void ElementSubMenuInitializer()
        {
            Array.Resize(ref elementSubMenu, 8);
            elementSubMenu[0].id = 1;
            elementSubMenu[0].name = " 1 - Create new Triangle";
            elementSubMenu[1].id = 2;
            elementSubMenu[1].name = " 2 - Create new Parallelogram";
            elementSubMenu[2].id = 3;
            elementSubMenu[2].name = " 3 - Create new Pentagon";
            elementSubMenu[3].id = 4;
            elementSubMenu[3].name = " 4 - Create new Hexagon";
            elementSubMenu[4].id = 5;
            elementSubMenu[4].name = " 5 - Create new Heptagon";
            elementSubMenu[5].id = 6;
            elementSubMenu[5].name = " 6 - Return back to menu";
        }

        static void MenuInitializer()
        {
            Array.Resize(ref menu, 8);
            menu[0].id = 1;
            menu[0].name = " 1 - Append Elementr";
            menu[1].id = 2;
            menu[1].name = " 2 - Add Element to position";
            menu[2].id = 3;
            menu[2].name = " 3 - Pop Element";
            menu[3].id = 4;
            menu[3].name = " 4 - Remove Element from position";
            menu[4].id = 5;
            menu[4].name = " 5 - Remove Element with Id";
            menu[5].id = 6;
            menu[5].name = " 6 - Find Element by Id";
            menu[6].id = 7;
            menu[6].name = " 7 - Print All Elements";
            menu[7].id = 8;
            menu[7].name = " 8 - Close program";
        }

        static void OutputMenu(MenuElement[] menu)
        {
            for (int i = 0; i < menu.Length; i++)
            {
                Console.WriteLine(menu[i].name);
            }
        }

        static void RequestProcessor(int max, ref int idOfActiveMenuElement, bool isItGeneral, MenuElement[] menu)
        {
            do
            {
                Console.WriteLine("Please, enter bellow code of action and press <Enter>");
                string readedString = Console.ReadLine();
                int idOfSelectedElement = 0;
                if (readedString.Length > 0)
                {
                    if ((int.TryParse(readedString, out idOfSelectedElement)) &&
                        (idOfSelectedElement > 0) &&
                        (idOfSelectedElement <= max))
                    {
                        idOfActiveMenuElement = menu[idOfSelectedElement - 1].id;
                        return;
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
                if (RepeatRequest() == 'y')
                {
                    continue;
                }
                else
                {
                    if (isItGeneral)
                    {
                        Environment.Exit(0);
                    }
                    idOfActiveMenuElement = -1;
                }
            } while (true);
        }

        static void DataProcessor()
        {
            Polygon[] polygons;
            Polygon polygon;
            int position;
            int id;
            switch (idOfActiveMenuElement)
            {
                case CREATE_NEW_POLYGON:
                    polygon = PolygonCreator();
                    if (polygon == null)
                    {
                        Console.WriteLine("Cancelled by User");
                        return;
                    }
                    arrayPolygon.AppendElement(polygon);
                    Console.WriteLine("Succesfully done");
                    break;
                case CREATE_NEW_POLYGON_IN_POSITION:
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
                case POP_POLYGON:
                    if (arrayPolygon.Length() == 0)
                    {
                        Console.WriteLine("Isn't possible, no one polygon");
                        return;
                    }
                    arrayPolygon.PopElement();
                    Console.WriteLine("Succesfully done");
                    break;
                case REMOVE_POLYGON_FROM_POSITION:
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
                case REMOVE_POLYGON_WITH_ID:
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
                case FIND_POLYGON_BY_ID:
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
                case SHOW_ALL_POLYGONS:
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
                default:
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

        static int DecodePolygonSelection()
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
            OutputMenu(elementSubMenu);
            RequestProcessor(6, ref idOfActiveSubMenuElement, false, elementSubMenu);
            if (idOfActiveSubMenuElement == -1 || idOfActiveSubMenuElement == 6)
            {
                return null;
            }
            int numberOfSides = DecodePolygonSelection();
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