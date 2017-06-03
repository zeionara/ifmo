using System;

sealed class Hexagon : Polygon
{
    public Hexagon(int id)
        : base(id, 6)
    { }

    public Hexagon(int id, int[] sides)
        : base(id, 6, sides)
    { }
}