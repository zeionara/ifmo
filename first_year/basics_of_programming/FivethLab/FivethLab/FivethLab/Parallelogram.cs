using System;

public class Parallelogram : Polygon, IEquatable<Parallelogram>, IComparable<Parallelogram>
{
    public Parallelogram(int id)
        : base(id, 4)
    { }

    public Parallelogram(int id, int[] sides)
        : base(id, 4, sides)
    { }

    public override double GetSquare()
    {
        double perimeter = GetPerimeter();
        return Math.Sqrt(
                (perimeter / 2 - (int)lengthsOfSides[0]) *
                (perimeter / 2 - (int)lengthsOfSides[1]) *
                (perimeter / 2 - (int)lengthsOfSides[2]) *
                (perimeter / 2 - (int)lengthsOfSides[3]));
    }

    public int CompareTo(Parallelogram other)
    {
        return (GetPerimeter() + GetSquare()).CompareTo(other.GetPerimeter() + other.GetSquare());
    }

    public bool Equals(Parallelogram other)
    {
        return (GetPerimeter() + GetSquare()).Equals(other.GetPerimeter() + other.GetSquare());
    }
}