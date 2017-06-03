using System;

public class ValueWasSkipped : Exception
{
    public string message = "Skipped by user"; 
	public ValueWasSkipped()
	{
	}
}
