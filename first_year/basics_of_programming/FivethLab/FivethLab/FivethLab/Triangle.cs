using System;

public class Triangle : Polygon, IEquatable<Triangle>, IComparable<Triangle>
{
    public Triangle(int id)
        : base(id, 3)
    { }

    public Triangle(int id, int[] sides)
        : base(id, 3, sides)
    { }

    public int CompareTo(Triangle other)
    {
        return (GetPerimeter() + GetSquare()).CompareTo(other.GetPerimeter() + other.GetSquare());
    }

    public bool Equals(Triangle other)
    {
        return (GetPerimeter() + GetSquare()).Equals(other.GetPerimeter() + other.GetSquare());
    }

    public override double GetSquare()
    {
        double perimeter = GetPerimeter();
        return  Math.Sqrt(perimeter / 2 *
                (perimeter / 2 - (int)lengthsOfSides[0]) *
                (perimeter / 2 - (int)lengthsOfSides[1]) *
                (perimeter / 2 - (int)lengthsOfSides[2]));
    }
}
