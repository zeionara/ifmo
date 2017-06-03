using System;

sealed class Triangle : Polygon
{
    public Triangle(int id)
        : base(id, 3)
    { }

    public Triangle(int id, int[] sides)
        : base(id, 3, sides)
    { }

    public override double GetSquare()
    {
        double perimeter = GetPerimeter();
        return  Math.Sqrt(perimeter / 2 *
                (perimeter / 2 - (int)lengthsOfSides[0]) *
                (perimeter / 2 - (int)lengthsOfSides[1]) *
                (perimeter / 2 - (int)lengthsOfSides[2]));
    }
}
