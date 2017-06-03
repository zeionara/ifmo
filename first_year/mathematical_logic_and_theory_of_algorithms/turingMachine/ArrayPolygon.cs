using System;

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
        for (int i = 0; i < polygons.Length; i++)
        {
            if (polygons[i].Id == id)
            {
                RemoveElement(i);
                return true;
            }
        }
        return false;
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
