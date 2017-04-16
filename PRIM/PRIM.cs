using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Prim_Algorithm
{
    class Program
    {
        static void completa_matrix(int n, int[,] matrix_aux)
        {
	    
            for (int i = 0; i < n-1; i++)
            {
		var values = (Console.ReadLine().Split('	'));
		Console.Write("{0} ",values[0]);
		int aux = 0;		
                for (int j = 0; j < n; j++)
                {
                    if (i == j)
                    {
                        matrix_aux[i, j] = 0;
                    }
                    else
                    {
                        if (matrix_aux[i, j] != 0)
                        {
                            j++;
                        }
                        else
                        {
				matrix_aux[i, j] = int.Parse(values[aux]); 
			 	matrix_aux[j, i] = matrix_aux[i, j];
				aux++;
                        }                                               
                    }                    
                
		}
            }
		
        }

        private static int MinKey(int[] key, bool[] set, int verticesCount)
        {
            int min = int.MaxValue, minIndex = 0;

            for (int v = 0; v < verticesCount; ++v)
            {
                if (set[v] == false && key[v] < min)
                {
                    min = key[v];
                    minIndex = v;
                }
            }

            return minIndex;
        }

        private static void Print(int[] parent, int[,] matrix_aux, int verticesCount)
        {
            int soma = 0;
            Console.WriteLine("Aresta   Custo");
            for (int i = 1; i < verticesCount; ++i)
            {
                Console.WriteLine("{0} - {1}    {2}", parent[i], i, matrix_aux[i, parent[i]]);
                soma += matrix_aux[i, parent[i]];
            }
            Console.WriteLine("{0}    {1}","Total",soma);   
        }

        public static void PRIM(int[,] matrix_aux, int verticesCount)
        {
            int[] parent = new int[verticesCount];
            int[] key = new int[verticesCount];
            bool[] mstSet = new bool[verticesCount];

            for (int i = 0; i < verticesCount; ++i)
            {
                key[i] = int.MaxValue;
                mstSet[i] = false;
            }

            key[0] = 0;
            parent[0] = -1;

            for (int count = 0; count < verticesCount - 1; ++count)
            {
                int u = MinKey(key, mstSet, verticesCount);
                mstSet[u] = true;

                for (int v = 0; v < verticesCount; ++v)
                {
                    if (Convert.ToBoolean(matrix_aux[u, v]) && mstSet[v] == false && matrix_aux[u, v] < key[v])
                    {
                        parent[v] = u;
                        key[v] = matrix_aux[u, v];
                    }
                }
            }

            Print(parent, matrix_aux, verticesCount);
        }

        static void Main(string[] args)
        {
            int n = Convert.ToInt32(Console.ReadLine());
		Console.WriteLine(n);
            int[,] matrix = new int[n, n];
            completa_matrix(n, matrix);
            PRIM(matrix,n);
            Console.ReadKey();
        }
    }
}
