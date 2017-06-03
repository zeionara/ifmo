using System;
using System.Collections.Generic;

public class ArrayPolygon
{
    private List<Polygon> polygons = new List<Polygon>();

    public int Length()
    {
        return polygons.Count;
    }

    public Polygon[] GetArrayOfPolygons()
    {
        Polygon[] arrayOfPolygons = new Polygon[polygons.Count];
        for (int i = 0; i < polygons.Count; i++)
        {
            arrayOfPolygons[i] = polygons[i];
        }
        return arrayOfPolygons;
    }

    public void AppendElement(Polygon polygon)
    {
        polygons.Add(polygon);
    }

    public void AddElement(Polygon polygon, int index)
    {
        polygons.Insert(index, polygon);
    }

    public Polygon PopElement()
    {
        Polygon polygon = polygons[polygons.Count - 1];
        polygons.RemoveAt(polygons.Count - 1);
        return polygon;
    }

    public void RemoveElement(int index)
    {
        polygons.RemoveAt(index);
    }

    public bool RemoveElementById(int id)
    {
        for (int i = 0; i < polygons.Count; i++)
        {
            if (polygons[i].Id == id)
            {
                RemoveElement(i);
                return true;
            }
        }
        return false;
    }

    public Polygon FindPolygon(int id)
    {
        for (int i = 0; i < polygons.Count; i++)
        {
            if (polygons[i].Id == id)
            {
                return polygons[i];
            }
        }
        throw new PolygonNotFoundedException();
    }

    public List<Polygon> GetPolygonsWithType<T>()
        where T : Polygon
    {
        List<Polygon> foundedPolygons = new List<Polygon>();
        for (int i = 0; i < polygons.Count; i++)
        {
            if (polygons[i] is T)
            {
                foundedPolygons.Add(polygons[i]);
            }
        }
        return foundedPolygons;        
    }
}
