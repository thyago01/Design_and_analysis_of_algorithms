using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace APA_Ordena3
{
    class Program
    {
        static void CountingSort(ref int[] data, int min, int max)
        {
            int[] count = new int[max - min + 1];
            int z = 0;

            for (int i = 0; i < count.Length; i++)
                count[i] = 0;

            for (int i = 0; i < data.Length; i++)
                count[data[i] - min]++;

            for (int i = min; i <= max; i++)
            {
                while (count[i - min]-- > 0)
                {
                    data[z] = i;
                    ++z;
                }
            }
        }

	static void RadixSort(ref int[] data)
	{
	int i, j;
	int[] temp = new int[data.Length];

	for (int shift = 31; shift > -1; --shift)
	{
		j = 0;

		for (i = 0; i < data.Length; ++i)
		{
			bool move = (data[i] << shift) >= 0;

			if (shift == 0 ? !move : move)
				data[i - j] = data[i];
			else
				temp[j++] = data[i];
		}

		Array.Copy(temp, 0, data, data.Length - j, j);
		}
	}

	static void BucketSort(ref int[] data)
	{	
	int minValue = data[0];
	int maxValue = data[0];
	
	for (int i = 1; i < data.Length; i++)
	{
		if (data[i] > maxValue)
			maxValue = data[i];
		if (data[i] < minValue)
			minValue = data[i];
	}
	
	List<int>[] bucket = new List<int>[maxValue - minValue + 1];
	
	for (int i = 0; i < bucket.Length; i++)
	{
		bucket[i] = new List<int>();
	}
	
	for (int i = 0; i < data.Length; i++)
	{
		bucket[data[i] - minValue].Add(data[i]);
	}
		
	int k = 0;
	for (int i = 0; i < bucket.Length; i++)
	{
		if (bucket[i].Count > 0)
		{
			for (int j = 0; j < bucket[i].Count; j++)
			{
				data[k] = bucket[i][j];
				k++;
			}
		}
	}
	}

        static void Main(string[] args)
        {
            int men = 0,mai = 0;
            int max = Convert.ToInt32(Console.ReadLine());
            int[] numarray = new int[max];
            for (int i = 0; i < max; i++)
            {
                numarray[i] = Convert.ToInt32(Console.ReadLine());
                if (i == 0)
                {
                    men = numarray[0];
                    mai = numarray[0];
                }

                if (numarray[i] < men)
                {
                    men = numarray[i];

                }
                else if (numarray[i] > mai)
                {
                    mai = numarray[i];
                }
            }

            int op = int.Parse(args[0]);
            if (op >= 1 && op <= 3)
            {
                switch (op)
                {
                    case 1:
                        CountingSort(ref numarray, men, mai);
			for (int i = 0; i < max; i++)
            		Console.WriteLine(numarray[i]);
                        break;
                    case 2:
    	   		BucketSort(ref numarray);
			for (int i = 0; i < max; i++)
            		Console.WriteLine(numarray[i]);
                        break;
                    case 3:
                        RadixSort(ref numarray);
			for (int i = 0; i < max; i++)
            		Console.WriteLine(numarray[i]);
                        break;
                    default:
                        Console.WriteLine("Algo de errado não está certo");
                        break;
                }
            }
            else
            {
                Console.WriteLine("Digite uma opção válida!!!");
                Console.WriteLine("1 - Counting sort");
                Console.WriteLine("2 - Bucket sort");
                Console.WriteLine("3 - Radix sort");
            }
        }
    }
}
