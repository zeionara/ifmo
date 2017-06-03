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
        static ArrayPolygon figures = new ArrayPolygon();

        static void Main(string[] args)
        {
            Console.WriteLine("Welcome! You work with array of polygons");
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
            string processedString = " ";
            int idOfSelectedElement = 0;
            if (readedString.Length > 0)
            {
                processedString = readedString.Substring(0,1);
                if (int.TryParse(processedString, out idOfSelectedElement))
                {
                    Console.WriteLine(menu[idOfSelectedElement - 1].name);
                    idOfActiveMenuElement = menu[idOfSelectedElement - 1].id;
                } else
                {
                    RequestErrorProcessor("You enter uncorrect code");
                }
            } else
            {
                RequestErrorProcessor("You don't enter nothing");
            }
        }
        static void RequestErrorProcessor(string message)
        {
            Console.WriteLine(message+"\nDo you want to try again?\n 1 - yes\n 0 - no\n"+
                "Please, Enter answer and press <Enter>. If you enter more than one symbol"+
                " program takes only first");
            string readedString = Console.ReadLine();
            string processedString = " ";
            int idOfSelectedElement = 0;
            if (readedString.Length > 0)
            {
                processedString = readedString.Substring(0, 1);
                if (int.TryParse(processedString, out idOfSelectedElement))
                {
                    if (idOfSelectedElement == 0)
                    {
                        Environment.Exit(0);
                    } else
                    {
                        OutputMenu();
                        RequestProcessor();
                    }
                }
                else
                {
                    RequestErrorProcessor(message);
                }
            }
            else
            {
                RequestErrorProcessor(message);
            }
        }
        static void DataProcessor()
        {
            Polygon[] polygons;
            Polygon figure;
            int position;
            int id;
            switch (idOfActiveMenuElement)
            {
                case 1:
                    figure = FigureCreator();
                    figures.AppendElement(figure);
                    break;
                case 2:
                    figure = FigureCreator();
                    position = PositionReader();
                    figures.AddElement(figure, position);
                    break;
                case 3:
                    if (figures.Length() > 0)
                    {
                        figures.PopElement();
                        Console.WriteLine("Succesfully done");
                    } else
                    {
                        Console.WriteLine("Isn't possible, no one figure");
                    }
                    break;
                case 4:
                    if (figures.Length() > 0)
                    {
                        position = PositionReader();
                        figures.RemoveElement(position);
                        Console.WriteLine("Succesfully done");
                    }
                    else
                    {
                        Console.WriteLine("Isn't possible, no one figure");
                    }
                    break;
                case 5:
                    id = IdReader();
                    if (figures.RemoveElementById(id))
                    {
                        Console.WriteLine("Succesfully done");
                    }
                    else {
                        Console.WriteLine("Isn't possible, element not founded");
                    }
                    break;
                case 6:
                    id = IdReader();
                    figure = figures.FindElement(id);
                    if (figure._id == 0)
                    {
                        Console.WriteLine("Isn't possible, element not founded");
                    } else
                    {
                        Console.WriteLine("Element founded");
                        figure.OutputInfo();
                    }
                    break;
                case 7:
                    polygons = figures.GetAllPolygons();
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
                if (int.TryParse(processedString, out idOfSelectedElement))
                {
                    if (idOfSelectedElement == 0)
                    {
                        Environment.Exit(0);
                    }
                    else
                    {
                        DataProcessor();
                    }
                }
                else
                {
                    DataErrorProcessor(message);
                }
            }
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
                if (int.TryParse(processedString, out idOfSelectedElement))
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
                }
                else
                {
                    return DataErrorProcessorFigureCreator(message);
                }
            }
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
            } else if ((correctParameters.Length > 1) && ((correctParameters.Length - 2) != correctParameters[1]))
            {
                return DataErrorProcessorFigureCreator("Uncorrect number of sides");
            };
            return new Polygon(correctParameters);
        }
        static int PositionReader()
        {
            int position = -1;
            int min = 0;
            int max = figures.Length()-1;
            Console.WriteLine("Please, Enter position of element. \nMinimal position: 0\nMaximal position: "+
                max.ToString());
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
                if (int.TryParse(processedString, out idOfSelectedElement))
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
                }
                else
                {
                    return DataErrorProcessorPositionReader(message);
                }
            }
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
                if (int.TryParse(processedString, out idOfSelectedElement))
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
                }
                else
                {
                    return DataErrorProcessorIdReader(message);
                }
            }
            else
            {
                return DataErrorProcessorIdReader(message);
            }
        }
    }
    class Polygon
    {
        private int id = 0;
        private int numberOfSides = 0;
        private float perimeter = 0;
        private float square = 0;
        private ArrayList lengthsOfSides = new ArrayList();
        private TypeOfPolygon typeOfPolygon = TypeOfPolygon.Polygon;

        public int _id { get; private set; }

        public Polygon(int id)
        {
            this.id = id;
        }
        public Polygon(int id, int numberOfSides)
        {
            this.id = id;
            this.numberOfSides = numberOfSides;
            SetTypeOfPolygon();
        }
        public Polygon(int id, int numberOfSides, int[] args)
        {
            this.id = id;
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
            this.id = args[0];
            _id = id;
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
            Console.WriteLine("Id = " + this._id.ToString() + "\nPerimeter = " + perimeter.ToString() + "\nSquare = " +
                square.ToString() + "\nNumber of sides = " + numberOfSides.ToString() + "\nType of figure = " +
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
                if (figures[i]._id == id)
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
                if (figures[i]._id == id)
                {
                    figure = figures[i];
                    break;
                }
            }
            return figure;
        }
    }
}