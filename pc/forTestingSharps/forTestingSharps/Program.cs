using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;

namespace forTestingSharps
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string first ="33.666";
            float f = 0;
            f = float.Parse(first, CultureInfo.InvariantCulture.NumberFormat);
            Console.WriteLine(first);

            Console.ReadLine();
        }
    }
}
