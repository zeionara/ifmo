using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Second_Lab
{
    enum TypeOfPolygon { Triangle, Parallelogram, Pentagon, Hexagon, Heptagon, Polygon }
    class Program
    {
        struct MenuElement
        {
            public string name;
            public int id;
        }

        static MenuElement[] menu = new MenuElement[1];
        static int idOfActiveMenuElement = 0;
        static ArrayPolygon arrayPolygon = new ArrayPolygon();
        
        const int CANCELLED = -1;
        const int SKIPED = -2;

        static void Main(string[] args)
        {
            MenuInitializer();
            while (true)
            {
                OutputMenu();
                RequestProcessor();
                DataProcessor();
            }
        }

        static void MenuInitializer()
        {
            Array.Resize(ref menu, 8);
            menu[0].id = 1;
            menu[0].name = " 1 - Append Element";
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

        static void OutputMenu()
        {
            for (int i = 0; i < menu.Length; i++)
            {
                Console.WriteLine(menu[i].name);
            }
        }

        static void RequestProcessor()
        {
            do
            {
                Console.WriteLine(@"Please, enter bellow code of action and press <Enter>");
                string readedString = Console.ReadLine();
                int idOfSelectedElement = 0;
                if (readedString.Length > 0)
                {
                    if ((int.TryParse(readedString, out idOfSelectedElement)) &&
                        (idOfSelectedElement > 0) &&
                        (idOfSelectedElement < 9))
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
                else {
                    Environment.Exit(0);
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
                case 1:
                    polygon = PolygonCreator();
                    if (polygon == null)
                    {
                        Console.WriteLine("Cancelled by User");
                        return;
                    }
                    arrayPolygon.AppendElement(polygon);
                    Console.WriteLine("Succesfully done");
                    break;
                case 2:
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
                case 3:
                    if (arrayPolygon.Length() == 0)
                    {
                        Console.WriteLine("Isn't possible, no one polygon");
                        return;
                    }
                    arrayPolygon.PopElement();
                    Console.WriteLine("Succesfully done");
                    break;
                case 4:
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
                case 5:
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
                case 6:
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
                    polygon.OutputInfo();
                    break;
                case 7:
                    if (arrayPolygon.Length() == 0)
                    {
                        Console.WriteLine("No one polygon in list");
                        return;
                    }
                    polygons = arrayPolygon.GetAllPolygons();
                    for (int i = 0; i < polygons.Length; i++)
                    {
                        Console.WriteLine("Polygon " + (i + 1));
                        polygons[i].OutputInfo();
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
                } else if (!int.TryParse(readedString, out info))
                {
                    Console.WriteLine("Uncorrect number");
                } else
                {
                    if (info <= minimal)
                    {
                        Console.WriteLine("Uncorrect "+nameOfPartOfInfo+" of polygon");
                    } else
                    {
                        return info;
                    }
                }
                if (RepeatRequest() == 'y')
                {
                    continue;
                }
                else {
                    return CANCELLED;
                }
            } while (true);
        }

        static Polygon PolygonCreator()
        {
            Console.WriteLine("Creating a polygon...");
            int id = GetPolygonInfo("Enter Id of new polygon (integer number > 0):", "id", 0, false);
            if (id == CANCELLED)
            {
                return null;
            }
            int numberOfSides = GetPolygonInfo(@"Enter Number of sides
                in new polygon (integer number > 2):" , "number of sides:", 2, true);
            if (numberOfSides == CANCELLED)
            {
                return null;
            }
            if (numberOfSides != SKIPED)
            {
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
                        sides[i] = GetPolygonInfo("Enter length of " + (i + 1) + " side (integer number >= 1):",
                            "length of side", 0, false);
                        if (sides[i] == CANCELLED)
                        {
                            return null;
                        }
                    }
                    return new Polygon(id, numberOfSides, sides);
                } else
                {
                    return new Polygon(id, numberOfSides);
                }
            } else
            {
                return new Polygon(id);
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
                } else if (!int.TryParse(readedString, out position))
                {
                    Console.WriteLine("Entered not a number");
                } else if ((position < min) || (position > max))
                {
                    Console.WriteLine("Position out of range");
                } else
                {
                    return position;
                }
                if (RepeatRequest() == 'y')
                {
                    continue;
                }
                else {
                    return CANCELLED;
                }
            } while (true);
        }

    }
    class Polygon
    {
        private int numberOfSides = 0;
        private ArrayList lengthsOfSides = new ArrayList();
        private TypeOfPolygon typeOfPolygon = TypeOfPolygon.Polygon;

        public int Id { get; private set; }

        public Polygon(int id)
        {
            this.Id = id;
        }

        public Polygon(int id, int numberOfSides)
            : this(id)
        {
            this.numberOfSides = numberOfSides;
            SetTypeOfPolygon();
        }

        public Polygon(int id, int numberOfSides, int[] args)
            : this(id, numberOfSides)
        {
            for (int i = 0; i < args.Length; i++)
            {
                lengthsOfSides.Add(args[i]);
            }
        }

        private void SetTypeOfPolygon()
        {
            switch (numberOfSides)
            {
                case 3:
                    typeOfPolygon = TypeOfPolygon.Triangle;
                    break;
                case 4:
                    typeOfPolygon = TypeOfPolygon.Parallelogram;
                    break;
                case 5:
                    typeOfPolygon = TypeOfPolygon.Pentagon;
                    break;
                case 6:
                    typeOfPolygon = TypeOfPolygon.Hexagon;
                    break;
                case 7:
                    typeOfPolygon = TypeOfPolygon.Heptagon;
                    break;
            }
        }

        private int GetPerimeter()
        {
            int perimeter = 0;
            for (int i = 0; i < lengthsOfSides.Count; i++)
            {
                perimeter += (int)(lengthsOfSides[i]);
            }
            return perimeter;
        }

        private float GetSquare()
        {
            switch (typeOfPolygon)
            {
                case TypeOfPolygon.Triangle:
                    return GetSquareForTriangle();
                case TypeOfPolygon.Parallelogram:
                    return GetSquareForParallelogram();
            }
            return 0;
        }

        private float GetSquareForTriangle()
        {
            int perimeter = GetPerimeter();
            return (float)Math.Sqrt(perimeter / 2 *
                (perimeter / 2 - (int)lengthsOfSides[0]) *
                (perimeter / 2 - (int)lengthsOfSides[1]) *
                (perimeter / 2 - (int)lengthsOfSides[2]));
        }

        private float GetSquareForParallelogram()
        {
            int perimeter = GetPerimeter();
            return (float)Math.Sqrt(
                (perimeter / 2 - (int)lengthsOfSides[0]) *
                (perimeter / 2 - (int)lengthsOfSides[1]) *
                (perimeter / 2 - (int)lengthsOfSides[2]) *
                (perimeter / 2 - (int)lengthsOfSides[3]));
        }

        public void OutputInfo()
        {
            Console.WriteLine("Id = " + Id + "\nPerimeter = " + GetPerimeter() + "\nSquare = " +
                GetSquare() + "\nNumber of sides = " + numberOfSides + "\nType of polygon = " +
                typeOfPolygon + "\nLengths of sides: ");
            for (int i = 0; i < lengthsOfSides.Count; i++)
            {
                Console.WriteLine(lengthsOfSides[i].ToString());
            }
        }
    }
    class ArrayPolygon
    {
        private Polygon[] polygons = new Polygon[0];

        public int Length()
        {
            return polygons.Length;
        }

        public Polygon[] GetAllPolygons()
        {
            return polygons;
        }

        public void AppendElement(Polygon polygon)
        {
            Array.Resize(ref polygons, polygons.Length + 1);
            polygons.SetValue(polygon, polygons.Length - 1);
        }

        public void AddElement(Polygon polygon, int index)
        {
            Array.Resize(ref polygons, polygons.Length + 1);
            for (int i = polygons.Length - 1; i > index; i--)
            {
                polygons.SetValue(polygons[i - 1], i);
            }
            polygons.SetValue(polygon, index);
        }

        public Polygon PopElement()
        {
            if (polygons.Length > 0)
            {
                Polygon polygon = polygons[polygons.Length - 1];
                Array.Resize(ref polygons, polygons.Length - 1);
                return polygon;
            }
            return null;
        }

        public void RemoveElement(int index)
        {
            for (int i = index + 1; i < polygons.Length; i++)
            {
                polygons.SetValue(polygons[i], i - 1);
            }
            Array.Resize(ref polygons, polygons.Length - 1);
        }

        public bool RemoveElementById(int id)
        {
            int index = -1;
            for (int i = 0; i < polygons.Length; i++)
            {
                if (polygons[i].Id == id)
                {
                    index = i;
                    break;
                }
            }
            if (index >= 0)
            {
                RemoveElement(index);
                return true;
            }
            else
            {
                return false;
            }
        }

        public Polygon FindElement(int id)
        {
            for (int i = 0; i < polygons.Length; i++)
            {
                if (polygons[i].Id == id)
                {
                    return polygons[i];
                }
            }
            return null;
        }

    }
}