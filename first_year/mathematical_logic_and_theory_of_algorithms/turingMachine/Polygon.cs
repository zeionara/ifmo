using System;
using System.Collections;

class Polygon : IComparable
{
    public const int DEFAULT_SIDE_LENGTH = 1;

    private int numberOfSides = 0;
    protected ArrayList lengthsOfSides = new ArrayList();

    public int Id { get; private set; }

    public bool CheckEquilateral()
    {
        for (int i = 1; i < numberOfSides; i++)
        {
            if ((int)lengthsOfSides[i - 1] != (int)lengthsOfSides[i])
            {
                return false;
            }
        }
        return true;
    }

    public void RewriteSide(int side, int numberOfSide)
    {
        lengthsOfSides[numberOfSides - 1] = side;
    }

    public void RewriteAllSides(int[] sides)
    {
        for (int i = 0; i < numberOfSides; i++)
        {
            lengthsOfSides[i] = sides[i];
        }
    }

    public Polygon(int id, int numberOfSides)
    {
        this.Id = id;
        this.numberOfSides = numberOfSides;
        for (int i = 0; i < numberOfSides; i++)
        {
            lengthsOfSides.Add(DEFAULT_SIDE_LENGTH);
        }
    }

    public Polygon(int id, int numberOfSides, int[] sides)
        : this(id, numberOfSides)
    {
        RewriteAllSides(sides);
    }

    public int GetPerimeter()
    {
        int perimeter = 0;
        for (int i = 0; i < lengthsOfSides.Count; i++)
        {
            perimeter += (int)(lengthsOfSides[i]);
        }
        return perimeter;
    }

    public virtual double GetSquare()
    {
        if (CheckEquilateral())
        {
            return (numberOfSides * (int)lengthsOfSides[0] * (int)lengthsOfSides[0] /
                (4 * Math.Tan(360 / (2 * numberOfSides))));
        }
        throw new InvalidOperationException();
    }

    public override string ToString()
    {
        string outputString = "";
        double square = 0;
        try
        {
            square = GetSquare();
        }
        catch (InvalidOperationException exception)
        {
            outputString = "Uncouting square";
        }
        if (outputString.Length == 0)
        {
            outputString = this.GetType() + " with id " + Id + "\nPerimeter = " + GetPerimeter() + "\nSquare = " +
                square + "\nNumber of sides = " + numberOfSides + "\nLengths of sides:";
        }
        else
        {
            outputString = this.GetType() + " with id " + Id + "\nPerimeter = " + GetPerimeter() + "\n"+
                 "Uncouting square\nNumber of sides = " + numberOfSides + "\nLengths of sides:";
        }
        for (int i = 0; i < numberOfSides; i++)
        {
            if (i != 0)
            {
                outputString += ", ";
            }
            outputString += lengthsOfSides[i];
        }
        return outputString;
    }

    public int CompareTo(object obj)
    {
        if (obj is Polygon)
        {
            return GetPerimeter().CompareTo((obj as Polygon).GetPerimeter());
        }
        return 1;
    }
}