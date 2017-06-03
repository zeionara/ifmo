using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Collections;
using System.IO;
using FourthLab;
using System.Security;

namespace FourthLabBP
{
    class FileSystemOperator<T>
    {
        public static bool IsFileWasLoaded { get; private set; }

        public static bool IsChangesWasSaved { get; private set; }

        public static bool IsFileLocked { get; private set; }

        public FileSystemOperator()
        {
            IsFileWasLoaded = false;
            IsChangesWasSaved = false;
            IsFileLocked = false;
        }

        private static Polygon RestorePolygon(int polygonType, ref XmlReader reader)
        {
            int numberOfSides = PolygonOperator.GetNumberOfSides(polygonType);
            int[] sides = new int[numberOfSides];
            int id = int.Parse(reader.GetAttribute("id"));
            for (int i = 0; i < sides.Length; i++)
            {
                reader.Read();
                reader.Read();
                sides[i] = int.Parse(reader.Value);
                reader.Read();
            }
            switch (polygonType)
            {
                case PolygonType.TRIANGLE: return new Triangle(id, sides);
                case PolygonType.PARALLELOGRAM: return new Parallelogram(id, sides);
                case PolygonType.PENTAGON: return new Pentagon(id, sides);
                case PolygonType.HEXAGON: return new Hexagon(id, sides);
                case PolygonType.HEPTAGON: return new Heptagon(id, sides);
                default: throw new OperationWasCrashedException();
            }
        }

        public static FileStream SelectFileForWriting()
        {
            FileStream fileStream;
            string path;
            while (true)
            {
                try {
                    Console.WriteLine("Please, enter here path to file:");
                    path = Console.ReadLine();
                    fileStream = new FileStream(path, FileMode.Create, FileAccess.Write);
                } catch (ArgumentNullException e)
                {
                    Console.WriteLine("Can't open file without path");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (ArgumentException e)
                {
                    Console.WriteLine("Invalid characters in path");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (NotSupportedException e)
                {
                    Console.WriteLine("Incorrect path to file");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (SecurityException e)
                {
                    Console.WriteLine("Can't get acess to file");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (UnauthorizedAccessException e)
                {
                    Console.WriteLine("Can't get acess to file");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (IOException e)
                {
                    Console.WriteLine("Internal error");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                return fileStream;
            }
        }

        public static FileStream SelectFileForReading()
        {
            FileStream fileStream;
            string path = "";
            while (true)
            {
                try
                {
                    Console.WriteLine("Please, enter here path to file:");
                    path = Console.ReadLine();
                    fileStream = new FileStream(path, FileMode.Open, FileAccess.Read);
                }
                catch (ArgumentNullException e)
                {
                    Console.WriteLine("Can't open file without path");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (ArgumentException e)
                {
                    Console.WriteLine("Invalid characters in path");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (NotSupportedException e)
                {
                    Console.WriteLine("Incorrect path to file");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (FileNotFoundException e)
                {
                    Console.WriteLine("File not exists");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (IOException e)
                {
                    Console.WriteLine("Internal error");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (SecurityException e)
                {
                    Console.WriteLine("Can't get acess to file");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }
                catch (UnauthorizedAccessException e)
                {
                    Console.WriteLine("Can't get acess to file");
                    Program.AskUserAboutRepeatingEntering();
                    continue;
                }

                return fileStream;
            }
        }

        private static void UpdateFileLocking(string path)
        {
            try
            {
                FileStream fileStream = new FileStream(path, FileMode.Open, FileAccess.Write);
            } catch (SecurityException e)
            {
                IsFileLocked = true;
                return;
            }
            IsFileLocked = false;
        }

        public static void CollectionWasUpdated()
        {
            IsChangesWasSaved = false;
        }

        public static void SaveCollection(ArrayPolygon arrayPolygon)
        {
            Polygon[] polygons = arrayPolygon.GetArrayOfPolygons();
            ArrayList sides;
            using (XmlWriter writer = XmlWriter.Create(SelectFileForWriting()))
            {
                writer.WriteStartDocument();
                writer.WriteStartElement("Polygons");

                for (int i = 0; i < polygons.Length; i++)
                {
                    writer.WriteStartElement(polygons[i].GetType().ToString());
                    writer.WriteAttributeString("id", polygons[i].Id.ToString());
                    sides = polygons[i].GetAllSides();
                    for (int j = 0; j < sides.Count; j++)
                    {
                        writer.WriteElementString("Side", sides[j].ToString());
                    }
                    writer.WriteEndElement();
                }

                writer.WriteEndElement();
                writer.WriteEndDocument();
            }
            IsChangesWasSaved = true;
        }

        public static ArrayPolygon LoadCollection()
        {
            ArrayPolygon arrayPolygon = new ArrayPolygon();
            XmlReader reader = XmlReader.Create(SelectFileForReading());
            while (reader.Read())
            {
                if (reader.NodeType == XmlNodeType.Element)
                {
                    switch (reader.Name)
                    {
                        case ("Triangle"):
                            arrayPolygon.AppendElement(RestorePolygon(PolygonType.TRIANGLE, ref reader));
                            break;
                        case ("Parallelogram"):
                            arrayPolygon.AppendElement(RestorePolygon(PolygonType.PARALLELOGRAM, ref reader));
                            break;
                        case ("Pentagon"):
                            arrayPolygon.AppendElement(RestorePolygon(PolygonType.PENTAGON, ref reader));
                            break;
                        case ("Hexagon"):
                            arrayPolygon.AppendElement(RestorePolygon(PolygonType.HEXAGON, ref reader));
                            break;
                        case ("Heptagon"):
                            arrayPolygon.AppendElement(RestorePolygon(PolygonType.HEPTAGON, ref reader));
                            break;
                    }// switch
                 }// if
            }// while
            IsFileWasLoaded = true;
            IsChangesWasSaved = true;
            return arrayPolygon;
        }
    }
}
