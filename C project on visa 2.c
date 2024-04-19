#include <stdio.h>
#include <stdbool.h>

// Define a structure to represent a node in the graph
struct Node
{
    int nodeid;        
    int adjcount;       
    int adjs[10];       // Array to store IDs of adjacent nodes
    int costs[10];      // Array to store costs associated with adjacent nodes
};

// Function to add a new node to the graph
// Parameters:
//   p: Pointer to the array of nodes
//   nid: ID of the node to be added
//   count: Current number of nodes in the graph
//   Updated count of nodes after adding the new node
int addNode(struct Node *p, int nid, int count)
{
    int i = 0, ncount = count;
    // Check if the node with given ID already exists
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }
    // If node doesn't exist, add it to the graph
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

// Function to add an adjacent node to a given node in the graph
// Parameters:
//   p: Pointer to the array of nodes
//   nid1: ID of the node to which the adjacent node will be added
//   nid2: ID of the adjacent node
//   cost: Cost associated with the edge between nid1 and nid2
//   count: Current number of nodes in the graph
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i = 0, index;
    // Find the index of the node with ID nid1
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            // Add nid2 as an adjacent node to nid1 with the given cost
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;
            break;
        }
    }
}

// Function to check if a node with given ID is already in a list
// Parameters:
//   list: Array containing IDs of nodes
//   lcount: Number of nodes in the list
//   nid: ID of the node to be checked
// Returns:
//   1 if the node is already in the list, 0 otherwise
int added(int *list, int lcount, int nid)
{
    int i = 0;
    for (i = 0; i < lcount; i++)
    {
        if (list[i] == nid)
        {
            return 1;
        }
    }
    return 0;
}

// Function to check if two nodes are adjacent
// Parameters:
//   n1: First node
//   n2: Second node
// Returns:
//   true if n1 and n2 are adjacent, false otherwise
bool Adjacent(struct Node n1, struct Node n2)
{
    for (int i = 0; i < n1.adjcount; i++)
    {
        if (n1.adjs[i] == n2.nodeid)
        {
            return true;
        }
    }
    return false;
}

// Main function
int main()
{
    struct Node nodes[50];  // Array to store nodes
    int nodecount = 0;      // Counter for number of nodes
    int n1 = 0, n2 = 0, c = 0;  // Variables to store user input for node IDs and costs

    // Loop to take input from the user until termination condition is met
    while (1)
    {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        // Termination condition: if any of the inputs is -9
        if (n1 == -9 || n2 == -9 || c == -9)
        {
            break;
        }
        // Add nodes and their adjacent nodes to the graph
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);
        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    // Loop through all possible combinations of three nodes to find triangular paths
    for (int i = 0; i < nodecount; i++)
    {
        for (int j = i + 1; j < nodecount; j++)
        {
            for (int k = j + 1; k < nodecount; k++)
            {
                struct Node n1 = nodes[i];
                struct Node n2 = nodes[j];
                struct Node n3 = nodes[k];
                // Check if all three nodes form a triangular path
                if (Adjacent(n1, n2) && Adjacent(n2, n3) && Adjacent(n3, n1))
                {
                    printf("Triangular path : %d %d %d \n", n1.nodeid, n2.nodeid, n3.nodeid);
                }
            }
        }
    }

    return 0;
}
