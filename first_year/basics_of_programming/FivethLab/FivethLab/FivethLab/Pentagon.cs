using System;

sealed class Pentagon : Polygon, IEquatable<Triangle>, IComparable<Triangle>
{
    public Pentagon(int id)
        : base(id, 5)
    { }

    public Pentagon(int id, int[] sides)
        : base(id, 5, sides)
    { }

    public int CompareTo(Triangle other)
    {
        return GetPerimeter().CompareTo(other.GetPerimeter());
    }

    public bool Equals(Triangle other)
    {
        return GetPerimeter().Equals(other.GetPerimeter());
    }
}