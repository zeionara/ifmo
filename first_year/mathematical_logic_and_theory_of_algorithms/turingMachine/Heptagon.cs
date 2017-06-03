using System;

sealed class Heptagon : Polygon
{
    public Heptagon(int id)
        : base(id, 7)
    { }

    public Heptagon(int id, int[] sides)
        : base(id, 7, sides)
    { }
}
