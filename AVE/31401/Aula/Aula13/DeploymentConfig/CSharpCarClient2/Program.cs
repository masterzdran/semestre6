﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using CarLibrary2;

namespace CSharpCarClient2
{
    public class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** C# CarLibrary Client App *****");
            // Make a sports car.
            SportsCar viper = new SportsCar("Viper", 240, 40);
            viper.TurboBoost();

            // Make a minivan.
            MiniVan mv = new MiniVan();
            mv.TurboBoost();
            Console.ReadLine();
        }
    }
}
