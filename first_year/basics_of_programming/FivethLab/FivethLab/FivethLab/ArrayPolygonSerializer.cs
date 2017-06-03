using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;
using System.Collections;
using FourthLab;

namespace FourthLabBP
{
    class ArrayPolygonSerializer
    {
        public static void Serialize(ArrayPolygon Collection, string path)
        {
            FileStream fileStream = new FileStream(path, FileMode.Create, FileAccess.Write);
            XmlDocument xmlDocument = new XmlDocument();
            Polygon[] polygons = Collection.GetArrayOfPolygons();
            ArrayList sides;
            XmlElement root = xmlDocument.CreateElement("Polygons");

            for (int i = 0; i < polygons.Length; i++)
            {
                XmlElement polygon = xmlDocument.CreateElement(polygons[i].GetType().ToString());
                polygon.SetAttribute("id", polygons[i].Id.ToString());
                sides = polygons[i].GetAllSides();
                for (int j = 0; j < sides.Count; j++)
                {
                    XmlElement side = xmlDocument.CreateElement("Side");
                    side.InnerText = sides[j].ToString();
                    polygon.AppendChild(side);
                }
                root.AppendChild(polygon);
            }

            xmlDocument.AppendChild(root);
            xmlDocument.Save(fileStream);
        }

        public static ArrayPolygon DeSerialize(string path)
        {
            FileStream fileStream = new FileStream(path, FileMode.Open, FileAccess.Read);

            XmlDocument xmlDocument = new XmlDocument();

            xmlDocument.Load(fileStream);

            ArrayPolygon arrayPolygon = new ArrayPolygon();

            XmlNode root = xmlDocument.LastChild;

            Console.WriteLine(root.InnerXml);

            XmlNodeList xmlPolygons = root.ChildNodes;

            for (int i = 0; i < xmlPolygons.Count; i++)
            {
                switch (xmlPolygons[i].Name)
                {
                    case ("Triangle"):
                        arrayPolygon.AppendElement(RestorePolygon(PolygonType.TRIANGLE, xmlPolygons[i]));
                        break;
                    case ("Parallelogram"):
                        arrayPolygon.AppendElement(RestorePolygon(PolygonType.PARALLELOGRAM, xmlPolygons[i]));
                        break;
                    case ("Pentagon"):
                        arrayPolygon.AppendElement(RestorePolygon(PolygonType.PENTAGON, xmlPolygons[i]));
                        break;
                    case ("Hexagon"):
                        arrayPolygon.AppendElement(RestorePolygon(PolygonType.HEXAGON, xmlPolygons[i]));
                        break;
                    case ("Heptagon"):
                        arrayPolygon.AppendElement(RestorePolygon(PolygonType.HEPTAGON, xmlPolygons[i]));
                        break;
                }// switch
            }
            return arrayPolygon;            
        }

        private static Polygon RestorePolygon(int polygonType, XmlNode xmlpolygon)
        {
            int numberOfSides = PolygonOperator.GetNumberOfSides(polygonType);
            int[] sides = new int[numberOfSides];
            int id = int.Parse(xmlpolygon.Attributes[0].Value);
            XmlNodeList xmlsides = xmlpolygon.ChildNodes;
            for (int j = 0; j < sides.Length; j++)
            {
                sides[j] = int.Parse(xmlsides[j].InnerText);
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
    }
}
