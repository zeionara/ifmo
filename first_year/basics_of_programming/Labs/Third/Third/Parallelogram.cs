using System;

class Parallelogram : Polygon
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
}