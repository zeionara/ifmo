using System;

class Heptagon : Polygon, IEquatable<Heptagon>, IComparable<Heptagon>
{
    public Heptagon(int id)
        : base(id, 7)
    { }

    public Heptagon(int id, int[] sides)
        : base(id, 7, sides)
    { }

    public int CompareTo(Heptagon other)
    {
        return GetPerimeter().CompareTo(other.GetPerimeter());
    }

    public bool Equals(Heptagon other)
    {
        return GetPerimeter().Equals(other.GetPerimeter());
    }
}
