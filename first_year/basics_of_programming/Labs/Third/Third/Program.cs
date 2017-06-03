using System;

namespace Third_Lab
{
    class Program
    {
        
        static ArrayPolygon arrayPolygon = new ArrayPolygon();

        static void Main(string[] args)
        {
            int selectedGeneralMenuItem = IdItemsOfGeneralMenu.UNDEFINED;
            while (true)
            {
                MenuItemSelector.DisplayMenu(Menues.generalMenu);
                selectedGeneralMenuItem = MenuItemSelector.SelectMenuItem(Menues.generalMenu);
                try
                {
                    MenuItemHandler.HandleSelectedGeneralMenuItem(selectedGeneralMenuItem, arrayPolygon);
                } catch (Exception exception)
                {
                    Console.WriteLine(exception);
                }
            }
        }

        public static void AskUserAboutRepeatingEntering()
        {
            char agree = 'y';
            char disagree = 'n';
            string inputString;
            do
            {
                Console.WriteLine("Do you want to try again?\nType " + agree + " or " + disagree + " and press Enter");
                inputString = Console.ReadLine();
            } while ((inputString.Length != 1) || ((inputString[0] != agree) && (inputString[0] != disagree)));
            if (inputString[0] == disagree)
            {
                throw new OperationWasCancelled();
            }
            return;
        }
    }
}
