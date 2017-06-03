using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ThirdLabOnCSharp
{
    struct memberOfMatrix
    {
        public int counter;
        public int value;
    }
    struct uniqueElementsOfMatrix
    {
        public memberOfMatrix[] elements;
        public ulong size;
    }
    class Sets
    {
        private char repeatGetSize(char errCode)
        {
            string str;
            char c;
            while (true)
            {
                switch (errCode)
                {
                    case '-':
                        Console.WriteLine("You enter not positive value, do you want try again? (type y or n)");
                        break;
                    case '.':
                        Console.WriteLine("You enter not integer value, do you want try again? (type y or n)");
                        break;
                    case ',':
                        Console.WriteLine("You enter not integer value, do you want try again? (type y or n)");
                        break;
                    default:
                        Console.WriteLine("You enter uncorrect value, do you want try again? (type y or n)");
                        break;
                }
                str = Console.ReadLine();
                if (str.Length > 0)
                {
                    c = str[0];
                    if ((c == 'y') || (c == 'n'))
                    {
                        return c;
                    }//if
                }//if
            }//while
        }//repeatGetSize
        private char repeatGetSize()
        {
            string str;
            Console.WriteLine("Do you want try again ? (type y or n)");
            char c;
            while (true)
            {
                str = Console.ReadLine();
                if (str.Length > 0)
                {
                    c = str[0];
                    if ((c == 'y') || (c == 'n'))
                    {
                        return c;
                    }//if
                }//if
            }//while
        }//repeatGetSize
        public ulong getSize(String outputStr)
        {
            char yesOrNo = 'y';
            ulong size=0; 
            int valid = 0, n = 0, i=0;
            string pre_str = "";
            while (valid == 0) {
                Console.WriteLine(outputStr);
                pre_str = Console.ReadLine();
                valid = 1;
                foreach (char c in pre_str)
                {
                    if ((c!='0') && (c!='1') && (c!='2') && (c!='3') && (c!='4') 
                        && (c!='5') && (c!='6') && (c!='7') && (c!='8') && (c!='9'))
                    {
                        valid = 0;
                        Console.WriteLine(valid);
                        yesOrNo = repeatGetSize(c);
                        if (yesOrNo == 'n')
                        {
                            Environment.Exit(0);
                        }
                        break;
                    }//if
                }//foreach
                if (valid == 1 && pre_str.Length>0)
                {
                    try {
                        size = ulong.Parse(pre_str);
                    } catch (Exception e){
                        Console.WriteLine("Error! " + e.Message);
                        yesOrNo = repeatGetSize();
                        if (yesOrNo == 'n')
                        {
                            Environment.Exit(0);
                        }
                        continue;
                    }
                    return size;
                } else
                {
                    valid = 0;
                }
            }//while
            return 0;
        }//getSize
    }
    class SimpleSets:Sets
    {
        private void outputAnswer(int[] numberSet, int negativeSummary, int positiveSummary, ulong size)
        {
            Console.WriteLine("Negative summary: " + negativeSummary);
            Console.WriteLine("Positive summary: " + positiveSummary);
            Console.WriteLine("Reversed array:");
            outputArray(numberSet, size);
        }
        private int findPositivesToMax(int[] arr, int imax)
        {
            int i = 0, sum=0;
            for (i=0;i< imax; i++)
            {
                if (arr[i] > 0)
                {
                    sum = sum + arr[i];
                }
            }
            return sum;
        }
        private int findMaxIndex(int[] arr)
        {
            int len = arr.Length, i = 0, max = 0, imax=0 ;
            for (i=0;i< len; i++)
            {
                if ((arr[i]> max) || (i == 0))
                {
                    max = arr[i];
                    imax = i;
                }
            }
            return imax;
        }
        private int findNegativeSummary(int[] arr)
        {
            int sum = 1;
            foreach (int a in arr)
            {
                if (a < 0)
                {
                    sum = sum * a;
                }
            }
            return sum;
        }
        private void outputArray(int[] arr,ulong size)
        {
            ulong i = 0;
            for (i=0;i< size; i++)
            {
                Console.Write(arr[i] + " ");
            }
            Console.WriteLine();
        }
        private ulong size = 0;
        public SimpleSets()
        {
            Random randomizer = new Random();
            ulong i = 0;
            int negativeSummary=0, imax=0, positivesToMax=0, a=0;
            size = this.getSize("Type size of linear array:");
            int[] numberSet = new int[size];
            for (i=0; i< size; i++)
            {
                numberSet[i] = randomizer.Next(-100,100);
            }
            Console.WriteLine("Generated Array:");
            outputArray(numberSet, size);
            negativeSummary = findNegativeSummary(numberSet);
            imax = findMaxIndex(numberSet);
            positivesToMax = findPositivesToMax(numberSet, imax);
            for (i=0; i<Math.Floor((double)size/2); i++)
            {
                a = numberSet[i];
                numberSet[i] = numberSet[size - 1 - i];
                numberSet[size -1 - i] = a;
            }
            outputAnswer(numberSet, negativeSummary, positivesToMax, size);
        }
    }
    class DoubleSets:Sets
    {
        private void outputAnswer()
        {
            Console.WriteLine("Number of No null rows: " + numOfNoNullRows);
            Console.WriteLine("Max In repeaters items: " + maxInRepeaters);
        }
        private int findMaxInRepeaters(int[,] matrix, ulong height, ulong width)
        {
            ulong i = 0, j = 0, k=0, isinitialized=0;
            int equalFounded = 0, max=0;
            uniqueElementsOfMatrix elements = new uniqueElementsOfMatrix();
            elements.elements = new memberOfMatrix[height * width];
            elements.size = 0;
            for (i=0;i< height; i++)
            {
                for (j=0;j< width; j++)
                {
                    equalFounded = 0;
                    for (k = 0; k < elements.size; k++)
                    {
                        if (elements.elements[k].value == matrix[i, j])
                        {
                            elements.elements[k].counter++;
                            equalFounded = 1;
                            break;
                        }
                    }
                    if (equalFounded == 0)
                    {
                        elements.elements[elements.size].value = matrix[i, j];
                        elements.size++;
                    }
                }
            }
            for (k = 0; k < elements.size; k++)
            {
                if (isinitialized == 0)
                {
                    if (elements.elements[k].counter > 1)
                    {
                        max = elements.elements[k].value;
                        isinitialized = 1;
                        continue;
                    }
                }
                if ((elements.elements[k].counter > 1) && (elements.elements[k].value > max))
                {
                    max = elements.elements[k].value;
                }
            }
            if (isinitialized == 0)
            {
                throw new Exception("No repeated items founded");
            } else
            {
                return max;
            }
        }
        private int numberOfNoNullRows(int[,] matrix, ulong height, ulong width)
        {
            ulong i = 0, j = 0;
            int isNull = 0, n=0;
            for (i=0;i< height; i++)
            {
                isNull = 0;
                for (j=0;j< width; j++)
                {
                    if (matrix[i, j] == 0)
                    {
                        isNull = 1;
                        break;
                    }
                }
                if (isNull == 0)
                {
                    n++;
                }
            }
            return n;
        }
        private void outputMatrix(int[,] matrix, ulong height, ulong width)
        {
            ulong i = 0,j = 0;
            for (i=0;i< height; i++)
            {
                for (j=0;j< width; j++)
                {
                    Console.Write(matrix[i, j]+" ");
                }
                Console.WriteLine();
            }
        }
        private ulong width = 1;
        private ulong height = 1;
        private int numOfNoNullRows = 0;
        private int maxInRepeaters = 0;
        private int[,] matrix = new int[1,1];
        public DoubleSets()
        {
            ulong i = 0, j = 0;
            Random randomizer = new Random();
            width = getSize("Type width of matrix: ");
            if (width == 1)
            {
                while (height==1)
                {
                    height = getSize("Type height of matrix: ");
                    if (height == 1)
                    {
                        Console.WriteLine("Please, type another value");
                    }//if
                }//while
            } else
            {
                height = getSize("Type height of matrix: ");
            }
            matrix = new int[height,width];
            for (i=0; i<height ;i++)
            {
                for (j=0; j< width; j++)
                {
                    matrix[i, j] = randomizer.Next(-100, 100);
                }
            }
            Console.WriteLine("Generated Matrix: ");
            outputMatrix(matrix, height, width);
            numOfNoNullRows = numberOfNoNullRows(matrix, height, width);
            try {
                maxInRepeaters = findMaxInRepeaters(matrix, height, width);
            } catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            outputAnswer();
            Console.Read();
        }//DoubleSets Constructor
    }
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Third lab!");
            Console.WriteLine("Part 1");
            SimpleSets Arr = new SimpleSets();
            Console.WriteLine("Part 2");
            DoubleSets Matrix = new DoubleSets();
        }
    }
}
