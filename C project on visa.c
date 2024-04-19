#include <stdio.h>

// Define a structure to represent a node in the graph
struct Node
{
    int nodeid;         // ID of the node
    int adjcount;       // Number of adjacent nodes
    int adjs[10];       // Array to store IDs of adjacent nodes
    int costs[10];      // Array to store costs associated with adjacent nodes
};

int visa[5];            // Array to store visa IDs
int mark = 0;           // Counter to mark nodes visited with visa
int nodecnt = 0;        // Counter to count total nodes visited

// Function to add a new node to the graph
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

// Function to find a path from start to end node in the graph
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount)
{
    int index = 0, i = 0;

    // Check if list contains the end node
    if (list[lcount - 1] == end)
    {
        int tcost = 0;
        mark = 0;
        nodecnt = 0;
        printf("\n");
        // Traverse the list and count nodes visited with visa
        for (i = 1; i < lcount; i++)
        {
            nodecnt++;
            for (int j = 0; j < 5; j++)
            {
                if (list[i] == visa[j])
                {
                    mark++;
                }
                tcost += clist[i];
            }
        }
        // If all nodes visited are marked with visa, print the path
        if (mark == nodecnt)
        {
            for (int i = 0; i < lcount; i++)
            {
                printf(" %d ", list[i]);
            }
        }
        printf(" cost = %d", tcost);
        return;
    }

    // Find the index of the start node
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == start)
        {
            index = i;
            break;
        }
    }

    // Explore adjacent nodes and find the path recursively
    for (i = 0; i < p[index].adjcount; i++)
    {
        int a = added(list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

int main()
{
    // Initialize variables
    struct Node nodes[50];  // Array to store nodes
    int nodecount = 0;      // Counter for number of nodes
    int n1 = 0, n2 = 0, c = 0;  // Variables to store user input for node IDs and costs
    int start, end;         // Variables to store start and end nodes
    int list[50], clist[50], lcount = 0;  // Arrays to store path and associated costs

    // Take input from the user to build the graph
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

    // Take input for start and end nodes
    printf("start, end ? ");
    scanf("%d %d", &start, &end);

    // Take input for visas
    printf("\nVisas I have with me : ");
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &visa[i]);
    }

    // Initialize the path with start node
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    // Find and print the path from start to end node
    findpath(nodes, nodecount, start, end, list, clist, lcount);

    return 0;
}
