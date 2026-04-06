using System;
using static System.Int32;
using System.Collections.Generic;

public class Program
{
    public static void Main()
    {
        while (true)
        {
            Console.WriteLine("Enter the first int to find the gcd of:");
            int a = int.Parse(Console.ReadLine());

            Console.WriteLine("Enter the second int to find the gcd of:");
            int b = int.Parse(Console.ReadLine());

            gcd(a, b);
        }
    }

    public static int gcd(int a, int b)
    {
        if (b == 0)
        {
            Console.WriteLine("The gcd of the two numbers is: " + a);
            return a;
        }
        else
        {
            return gcd(b, a % b);
        }
    }
}