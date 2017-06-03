using System;

class Hexagon : Polygon, IEquatable<Hexagon>, IComparable<Hexagon>
{
    public Hexagon(int id)
        : base(id, 6)
    { }

    public Hexagon(int id, int[] sides)
        : base(id, 6, sides)
    { }

    public int CompareTo(Hexagon other)
    {
        return GetPerimeter().CompareTo(other.GetPerimeter());
    }

    public bool Equals(Hexagon other)
    {
        return GetPerimeter().Equals(other.GetPerimeter());
    }
}