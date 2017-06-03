using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Second_Lab
{
    enum TypeOfPolygon {Triangle, Parallelogram, Pentagon, Hexagon, Heptagon, Polygon}
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
        static void Main(string[] args)
        {
            MenuInitializer();
            while (true)
            {
                OutputMenu();
                RequestProcessor();
                DataProcessor();
            }

            //Console.Read();
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
            Console.WriteLine("Please, enter bellow code of action and press <Enter>.\n"+
                "If you Enter more than one symbol program takes only first");
            string readedString = Console.ReadLine();
            string processedString = "";
            int idOfSelectedElement = 0;
            if (readedString.Length > 0)
            {
                processedString = readedString.Substring(0,1);
                if ((int.TryParse(processedString, out idOfSelectedElement)) && (idOfSelectedElement != 9))
                {
                    //Console.WriteLine(menu[idOfSelectedElement - 1].name);
                    idOfActiveMenuElement = menu[idOfSelectedElement - 1].id;
                } else
                {
                    RequestErrorProcessor("You enter uncorrect code");
                }
            } else
            {
                RequestErrorProcessor("You did't enter nothing");
            }
        }
        static void RequestErrorProcessor(string message)
        {
            Console.WriteLine(message+"\nDo you want to try again?\n 1 - yes\n 0 - no\n"+
                "Please, Enter answer and press <Enter>. If you enter more than one symbol"+
                " program takes only first");
            string readedString = Console.ReadLine();
            string processedString = "";
            int idOfSelectedElement = 0;
            if (readedString.Length > 0)
            {
                processedString = readedString.Substring(0, 1);
                if ((int.TryParse(processedString, out idOfSelectedElement)) && ((idOfSelectedElement == 0) ||
                                                                                (idOfSelectedElement == 1)))
                {
                    if (idOfSelectedElement == 0)
                    {
                        Environment.Exit(0);
                    } else
                    {
                        OutputMenu();
                        RequestProcessor();
                    }
                }// if entered 0 or 1
                else
                {
                    RequestErrorProcessor(message);
                }
            } // if (readedString.Length > 0)
            else
            {
                RequestErrorProcessor(message);
            }
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
                    polygon = FigureCreator();
                    arrayPolygon.AppendElement(polygon);
                    Console.WriteLine("Succesfully done");
                    break;
                case 2:
                    polygon = FigureCreator();
                    position = PositionReader();
                    arrayPolygon.AddElement(polygon, position);
                    Console.WriteLine("Succesfully done");
                    break;
                case 3:
                    if (arrayPolygon.Length() > 0)
                    {
                        arrayPolygon.PopElement();
                        Console.WriteLine("Succesfully done");
                    } else
                    {
                        Console.WriteLine("Isn't possible, no one figure");
                    }
                    break;
                case 4:
                    if (arrayPolygon.Length() > 0)
                    {
                        position = PositionReader();
                        arrayPolygon.RemoveElement(position);
                        Console.WriteLine("Succesfully done");
                    }
                    else
                    {
                        Console.WriteLine("Isn't possible, no one figure");
                    }
                    break;
                case 5:
                    id = IdReader();
                    if (arrayPolygon.RemoveElementById(id))
                    {
                        Console.WriteLine("Succesfully done");
                    }
                    else {
                        Console.WriteLine("Isn't possible, element not founded");
                    }
                    break;
                case 6:
                    id = IdReader();
                    polygon = arrayPolygon.FindElement(id);
                    if (polygon.Id == 0)
                    {
                        Console.WriteLine("Isn't possible, element not founded");
                    } else
                    {
                        Console.WriteLine("Element founded");
                        polygon.OutputInfo();
                    }
                    break;
                case 7:
                    polygons = arrayPolygon.GetAllPolygons();
                    for (int i = 0; i < polygons.Length; i++)
                    {
                        Console.WriteLine("Polygon "+(i+1));
                        polygons[i].OutputInfo();
                    }
                    break;
                default:
                    Environment.Exit(0);
                    break;
            }
        }
        static void DataErrorProcessor(string message)
        {
            Console.WriteLine(message + "\nDo you want to try again?\n 1 - yes\n 0 - no\n" +
                "Please, Enter answer and press <Enter>. If you enter more than one symbol" +
                " program takes only first");
            string readedString = Console.ReadLine();
            string processedString = " ";
            int idOfSelectedElement = 0;
            if (readedString.Length > 0)
            {
                processedString = readedString.Substring(0, 1);
                if ((int.TryParse(processedString, out idOfSelectedElement)) && ((idOfSelectedElement == 0) ||
                                                                                (idOfSelectedElement == 1)))
                {
                    if (idOfSelectedElement == 0)
                    {
                        Environment.Exit(0);
                    }
                    else
                    {
                        DataProcessor();
                    }
                }// if entered 0 or 1
                else
                {
                    DataErrorProcessor(message);
                }
            }// if (readedString.Length > 0)
            else
            {
                DataErrorProcessor(message);
            }
        }
        static Polygon DataErrorProcessorFigureCreator(string message)
        {
            Console.WriteLine(message + "\nDo you want to try again?\n 1 - yes\n 0 - no\n" +
                "Please, Enter answer and press <Enter>. If you enter more than one symbol" +
                " program takes only first");
            string readedString = Console.ReadLine();
            string processedString = " ";
            int idOfSelectedElement = 0;
            if (readedString.Length > 0)
            {
                processedString = readedString.Substring(0, 1);
                if ((int.TryParse(processedString, out idOfSelectedElement)) && ((idOfSelectedElement == 0) ||
                                                                                (idOfSelectedElement == 1)))
                {
                    if (idOfSelectedElement == 0)
                    {
                        OutputMenu();
                        RequestProcessor();
                        DataProcessor();
                        return new Polygon(0);
                    }
                    else
                    {
                        return FigureCreator();
                    }
                }// if entered 0 or 1
                else
                {
                    return DataErrorProcessorFigureCreator(message);
                }
            }// if (readedString.Length > 0)
            else
            {
                return DataErrorProcessorFigureCreator(message);
            }
        }
        static Polygon FigureCreator()
        {
            string[] parameters;
            int[] correctParameters;
            Console.WriteLine("To append new figure to collection you shold to write " +
                        "id of new figure ( integer number > 0), number if sides (integer number > 2) and " +
                        "lenghts of sides ( integer numbers > 0). Params separates by space. " +
                        "Two last params not required.");
            string readedString = Console.ReadLine();
            if (readedString.Length == 0)
            {
                DataErrorProcessorFigureCreator("No one symbol in string");
            }
            parameters = readedString.Split(' ');
            correctParameters = new int[parameters.Length];
            for (int i = 0; i < parameters.Length; i++)
            {
                if ((!int.TryParse(parameters[i], out correctParameters[i])) || (correctParameters[i] <= 0))
                {
                    return DataErrorProcessorFigureCreator("Uncorrect params");
                }
            }
            if ((correctParameters.Length > 1) && (correctParameters[1] <= 2))
            {
                return DataErrorProcessorFigureCreator("Uncorrect number of sides");
            } else if ((correctParameters.Length > 2) && ((correctParameters.Length - 2) != correctParameters[1]))
            {
                return DataErrorProcessorFigureCreator("Uncorrect list of sides");
            }
            return new Polygon(correctParameters);
        }
        static int PositionReader()
        {
            int position = -1;
            int min = 0;
            int max = arrayPolygon.Length();
            Console.WriteLine("Please, Enter position of element. \nMinimal position: 0\nMaximal position: "+
                max);
            string readedString = Console.ReadLine();
            if (readedString.Length == 0)
            {
                return DataErrorProcessorPositionReader("No one symbol in string");
            }
            if (!int.TryParse(readedString,out position))
            {
                return DataErrorProcessorPositionReader("Entered not a number");
            } else if ((position < min) || (position > max))
            {
                return DataErrorProcessorPositionReader("Position out of range");
            }
            return position;
        }
        static int DataErrorProcessorPositionReader(string message)
        {
            Console.WriteLine(message + "\nDo you want to try again?\n 1 - yes\n 0 - no\n" +
                "Please, Enter answer and press <Enter>. If you enter more than one symbol" +
                " program takes only first");
            string readedString = Console.ReadLine();
            string processedString = " ";
            int idOfSelectedElement = 0;
            if (readedString.Length > 0)
            {
                processedString = readedString.Substring(0, 1);
                if ((int.TryParse(processedString, out idOfSelectedElement)) && ((idOfSelectedElement == 0) ||
                                                                                (idOfSelectedElement == 1)))
                {
                    if (idOfSelectedElement == 0)
                    {
                        OutputMenu();
                        RequestProcessor();
                        DataProcessor();
                        return 0;
                    }
                    else
                    {
                        return PositionReader();
                    }
                }// if entered 0 or 1
                else
                {
                    return DataErrorProcessorPositionReader(message);
                }
            }// if (readedString.Length > 0)
            else
            {
                return DataErrorProcessorPositionReader(message);
            }
        }
        static int IdReader()
        {
            int id = -1;
            Console.WriteLine("Please, Enter Id of element (integer number > 0).");
            string readedString = Console.ReadLine();
            if (readedString.Length == 0)
            {
                return DataErrorProcessorIdReader("No one symbol in string");
            }
            if (!int.TryParse(readedString, out id))
            {
                return DataErrorProcessorIdReader("Entered not a number");
            }
            return id;
        }
        static int DataErrorProcessorIdReader(string message)
        {
            Console.WriteLine(message + "\nDo you want to try again?\n 1 - yes\n 0 - no\n" +
                "Please, Enter answer and press <Enter>. If you enter more than one symbol" +
                " program takes only first");
            string readedString = Console.ReadLine();
            string processedString = " ";
            int idOfSelectedElement = 0;
            if (readedString.Length > 0)
            {
                processedString = readedString.Substring(0, 1);
                if ((int.TryParse(processedString, out idOfSelectedElement)) && ((idOfSelectedElement == 0) ||
                                                                                (idOfSelectedElement == 1)))
                {
                    if (idOfSelectedElement == 0)
                    {
                        OutputMenu();
                        RequestProcessor();
                        DataProcessor();
                        return 0;
                    }
                    else
                    {
                        return IdReader();
                    }
                }// if entered 0 or 1
                else
                {
                    return DataErrorProcessorIdReader(message);
                }
            }// if (readedString.Length > 0)
            else
            {
                return DataErrorProcessorIdReader(message);
            }
        }
    }
    class Polygon
    {
        //private int id = 0;
        private int numberOfSides = 0;
        private float perimeter = 0;
        private float square = 0;
        private ArrayList lengthsOfSides = new ArrayList();
        private TypeOfPolygon typeOfPolygon = TypeOfPolygon.Polygon;

        public int Id { get; private set; }

        public Polygon(int id)
        {
            this.Id = id;
        }
        public Polygon(int id, int numberOfSides)
        {
            this.Id = id;
            this.numberOfSides = numberOfSides;
            SetTypeOfPolygon();
        }
        public Polygon(int id, int numberOfSides, int[] args)
        {
            this.Id = id;
            this.numberOfSides = numberOfSides;
            SetTypeOfPolygon();
            for (int i = 0; i < args.Length; i++)
            {
                lengthsOfSides.Add(args[i]);
            }
            ReCountSquare();
        }
        public Polygon(int[] args)
        {
            this.Id = args[0];
            if (args.Length >= 2)
            {
                this.numberOfSides = args[1];
                SetTypeOfPolygon();
            }
            if (args.Length > 2)
            {
                for (int i = 2; i < args.Length; i++)
                {
                    lengthsOfSides.Add(args[i]);
                }
                ReCountSquare();
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
        private void ReCountPerimeter()
        {
            perimeter = 0;
            for (int i = 0; i < lengthsOfSides.Count; i++)
            {
                perimeter += (int)(lengthsOfSides[i]);
            }
        }
        private void ReCountSquare()
        {
            switch (typeOfPolygon)
            {
                case TypeOfPolygon.Triangle:
                    ReCountSquareForTriangle();
                    break;
                case TypeOfPolygon.Parallelogram:
                    ReCountSquareForParallelogram();
                    break;
            }
        }
        private void ReCountSquareForTriangle()
        {
            ReCountPerimeter();
            square = (float)Math.Sqrt(perimeter / 2 *
                (perimeter / 2 - (int)lengthsOfSides[0]) *
                (perimeter / 2 - (int)lengthsOfSides[1]) *
                (perimeter / 2 - (int)lengthsOfSides[2]));
        }
        private void ReCountSquareForParallelogram()
        {
            ReCountPerimeter();
            square = (float)Math.Sqrt(
                (perimeter / 2 - (int)lengthsOfSides[0])*
                (perimeter / 2 - (int)lengthsOfSides[1])*
                (perimeter / 2 - (int)lengthsOfSides[2])*
                (perimeter / 2 - (int)lengthsOfSides[3]));
        }
        public void OutputInfo()
        {
            Console.WriteLine("Id = " + Id + "\nPerimeter = " + perimeter + "\nSquare = " +
                square + "\nNumber of sides = " + numberOfSides + "\nType of figure = " +
                typeOfPolygon + "\nLengths of sides: ");
            for (int i = 0; i < lengthsOfSides.Count; i++)
            {
                Console.WriteLine(lengthsOfSides[i].ToString());
            }
        }
    }
    class ArrayPolygon
    {
        private Polygon[] figures = new Polygon[0];
        public int Length()
        {
            return figures.Length;
        }
        public Polygon[] GetAllPolygons()
        {
            return figures;
        }
        public void AppendElement(Polygon figure)
        {
            Array.Resize(ref figures, figures.Length + 1);
            figures.SetValue(figure, figures.Length - 1);
        }
        public void AddElement(Polygon figure, int index)
        {
            Array.Resize(ref figures, figures.Length + 1);
            for (int i = figures.Length - 1; i > index; i--)
            {
                figures.SetValue(figures[i - 1], i);
            }
            figures.SetValue(figure, index);
        }
        public void PopElement()
        {
            if (figures.Length > 0)
            {
                Array.Resize(ref figures, figures.Length - 1);
            }
        }
        public void RemoveElement(int index)
        {
            for (int i = index + 1; i < figures.Length; i++)
            {
                figures.SetValue(figures[i], i - 1);
            }
            Array.Resize(ref figures, figures.Length - 1);
        }
        public bool RemoveElementById(int id)
        {
            int index = -1;
            for (int i = 0; i < figures.Length; i++)
            {
                if (figures[i].Id == id)
                {
                    index = i;
                    break;
                }
            }
            if (index >= 0)
            {
                for (int i = index + 1; i < figures.Length; i++)
                {
                    figures.SetValue(figures[i], i - 1);
                }
                Array.Resize(ref figures, figures.Length - 1);
                return true;
            } else
            {
                return false;
            }            
        }
        public Polygon FindElement(int id)
        {
            Polygon figure = new Polygon(0);
            for (int i = 0; i < figures.Length; i++)
            {
                if (figures[i].Id == id)
                {
                    figure = figures[i];
                    break;
                }
            }
            return figure;
        }
    }
}