/*Doti SandhyaRani (A04714047)
 * Advanced OS 
 * Project4 
 */
import java.util.*;
import java.util.Scanner;
import java.util.Random;

public class BellmanFord {
	
	//constants
	final int inifinty = Integer.MAX_VALUE;	
	int distance[];
	int n_vertices = 0;
	Scanner input = new Scanner(System.in);

	public BellmanFord(int n_vertices){
		this.n_vertices = n_vertices;
		distance = new int[n_vertices +1];
	}
	public  void shortestPath(int[][] weight, int source)throws Exception
	{
					
		// Step 1: initialize graph
			for (int node = 1; node <= n_vertices; node++){
	            distance[node] = Integer.MAX_VALUE;
	        }
		    distance[source] = 0;
			
		// Step 2: relax edges repeatedly
			for(int i=1;i<=n_vertices-1;i++){
				for(int j=1;j <= n_vertices;j++){
					for(int d=1;d <= n_vertices;d++){
						if(weight[j][d] != Integer.MAX_VALUE){
							if(distance[j] + weight[j][d] < distance[d] ){
							distance[d] = distance[j] + weight[j][d];
						}
					}
				}
			}
		}
		
		// Step 3: check for negative-weight cycles
		for(int v=1;v <= n_vertices; v++){
			for(int d = 1;d<=n_vertices;d++){
				if(weight[v][d] != Integer.MAX_VALUE){
					if(distance[v] + weight[v][d] < distance[d]){
					 throw new Exception("Negative cycle found");
					}
				}
			}
		}

		System.out.println("Enter the destination node : ");
		int destination = input.nextInt();

		
		// Printing the distance from source to destination
		System.out.println("Distance from source node " + source + " -- "
                      + destination + " is " + distance[destination]);
	
    }
	    
	//main method
	public static void main(String args[]) throws Exception
	{
		int source = 0;
		Scanner input = new Scanner(System.in);
		Random rand = new Random();

		System.out.println();
		System.out.println("****************************************");
		System.out.println("**********BellmanFord Algorithm*********");
		System.out.println("****************************************");
		System.out.println();
		
		System.out.println("Enter number of vertices : ");
		int vertices = input.nextInt();
		System.out.println();
		
		int[][] weight = new int[vertices + 1][vertices + 1];

	    	//generating the random graph with weight between 1 to 20 on each edge
	    	for (int s = 1; s <= vertices; s++)
	        {
	            for (int d = 1; d <= vertices; d++)
	            {

			weight[s][d] = rand.nextInt(20) + 1;
			weight[d][s] = weight[s][d];

	            	if (s == d)
	                {
	 	            weight[s][d] = 0;
	                    continue;
	                }
	                if (weight[s][d] == 0)
	                {
	                    weight[s][d] = Integer.MAX_VALUE;
	                }
	            }
	        }
		
		System.out.println("The generated adjacency matrix is (with weights) : ");
		for (int s = 1; s <= vertices; s++)
	        {
	            for (int d = 1; d <= vertices; d++)
	            {
			System.out.print(weight[s][d] + " ");
		    }
			System.out.println();
		}
			    
		System.out.println("Enter the source node : ");
		source = input.nextInt();
		

		BellmanFord b1 = new BellmanFord(vertices);

		b1.shortestPath(weight, source);
		input.close();
		} 
	}

