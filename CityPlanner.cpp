//Muhammad Rayyan Mohsin 22i-2052
//Fadil Falak 22i-1815

#include <iostream>
using namespace std;

struct queue
{
    int items[1000];
    int front, rear;

    queue()
    {
        front = -1;
        rear = -1;
    }

    int size()
    {
        return rear - front + 1;
    }

    void enqueue(int item)
    {
        if (rear == 1000 - 1)
        {
            cout << "Queue is full";
        }
        else
        {
            if (front == -1)
            {
                front = 0;
            }
            rear++;
            items[rear] = item;
        }
    }

    int dequeue()
    {
        int item;
        if (front == -1)
        {
            cout << "Queue is empty";
            item = -1;
        }
        else
        {
            item = items[front];
            front++;
            if (front > rear)
            {
                front = rear = -1;
            }
        }
        return item;
    }

    bool isEmpty()
    {
        if (front == -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class graph
{
public:
    int v;
    int **Road;
    int **Air;
    int *weights;

    graph(int V)
    {
        v = V;
        // Initialise aarrays with 0's
        Road = new int *[v];
        for (int i = 0; i < v; i++)
        {
            Road[i] = new int[v];
            for (int j = 0; j < v; j++)
            {
                Road[i][j] = 0;
            }
        }

        Air = new int *[v];
        for (int i = 0; i < v; i++)
        {
            Air[i] = new int[v];
            for (int j = 0; j < v; j++)
            {
                Air[i][j] = 0;
            }
        }

        weights = new int[v];
        for (int i = 0; i < v; i++)
        {
            weights[i] = 0;
        }
    }

    void addVertex()
    {
        v++;
        int **temp = new int *[v];
        for (int i = 0; i < v; i++)
        {
            temp[i] = new int[v];
            for (int j = 0; j < v; j++)
            {
                temp[i][j] = 0;
            }
        }

        for (int i = 0; i < v - 1; i++)
        {
            for (int j = 0; j < v - 1; j++)
            {
                temp[i][j] = Road[i][j];
            }
        }

        Road = temp;
    }

    void addRoad(int from, int to, int weight)
    {
        Road[from][to] = weight;
        Road[to][from] = weight;
    }

    void addAir(int from, int to, int weight)
    {
        Air[from][to] = weight;
        Air[to][from] = weight;
    }

    void connectSuccessively()
    {
        for (int i = 0; i < v - 1; ++i)
        {
            addRoad(i, i + 1, 1);
        }
    }

        int Breadth_First_Travel(int src, int dest)
    {
        bool *visited = new bool[v]; // Array to mark visited nodes
        for (int i = 0; i < v; ++i)
        {
            visited[i] = false; // Initially mark all nodes as not visited
            weights[i] = 1000;
        }

        queue q;
        weights[src] = 0;
        q.enqueue(src);
        visited[src] = true; // Mark the source node as visited

        while (!q.isEmpty())
        {
            int u = q.dequeue();

            // Check for road connections
            for (int i = 0; i < v; i++)
            {
                if (Road[u][i] == 1 && !visited[i])
                {
                    int newWeight = weights[u] + 1; // Weight for road route
                    if (newWeight < weights[i])
                    {
                        weights[i] = newWeight; // Update weight if road route is shorter
                    }
                    q.enqueue(i);
                    visited[i] = true; // Mark the node as visited
                }
            }

            // Check for air connections
            for (int i = 0; i < v; i++)
            {
                if (Air[u][i] == 1 && !visited[i])
                {
                    int newWeight = weights[u]; // Weight for air route (assumed to be same or shorter)
                    if (newWeight < weights[i])
                    {
                        weights[i] = newWeight; // Update weight if air route is shorter
                    }
                    q.enqueue(i);
                    visited[i] = true; // Mark the node as visited
                }
            }
        }

        

        delete[] visited; // Deallocate memory for the visited array

        if (weights[dest] > 6)
        {
            weights[dest] = weights[dest] / 6;
            return weights[dest];
        }
        else {
            return weights[dest];
        }
    }

    void printGraph()
    {
        cout << "\n\nFormat: ";
        cout << "City -> (Incoming road) (Outgoing road)" << endl;
        for (int i = 0; i < v; i++)
        {
            cout << i + 1 << " -> ";
            for (int j = 0; j < v; j++)
            {
                if (Road[i][j] == 1)
                {
                    cout << j + 1 << " ";
                }
            }
            cout << endl;
        }

        cout << "\nAerial Routes: " << endl;
        for (int i = 0; i < v; i++)
        {
            cout << i + 1 << " -> ";
            for (int j = 0; j < v; j++)
            {
                if (Air[i][j] == 1)
                {
                    cout << j + 1 << " ";
                }
            }
            cout << endl;
        }
    }

    ~graph()
    {
        for (int i = 0; i < v; ++i)
        {
            delete[] Road[i];
            delete[] Air[i];
        }
        delete[] Road;
        delete[] Air;
        delete[] weights;
    }
};

int main()
{
    cout << "\n\nWelcome to the City Planner!" << endl;
    cout << "----------------------------" << endl;
    cout << "\n1) Start" << endl;
    cout << "0) Exit" << endl
         << endl;
    cout << "---> ";
    int b;
    cin >> b;
    int k = 0;
    while (b != 0)
    {
        if (k > 0)
        {
            cout << "\n\n1) Create another graph." << endl;
            cout << "0) Exit" << endl;
            cout << "---> ";

            cin >> b;
        }
        k++;
        if (b == 1)
        {
            cout << "\n\nEnter the amount of test cases" << endl;
            int x, v, Aerial_V, from, to;
            cout << "---> ";

            cin >> x;
            while (x <= 0)
            {
                cout << "Invalid Input, try again1." << endl;
                cout << "---> ";
                cin >> x;
            }

            for (int i = 0; i < x; i++)
            {
                cout << "Enter the number of cities: ";
                cout << "---> ";
                cin >> v;
                while (v <= 0)
                {
                    cout << "Invalid Input, try again2." << endl;
                    cout << "---> ";
                    cin >> v;
                }

                graph g(v);

                cout << "Enter the number of aerial routes: ";
                cout << "---> ";
                cin >> Aerial_V;
                if (Aerial_V == 0)
                {
                    g.connectSuccessively();
                    g.printGraph();
                    cout << "Reaches destination on day number:  " << g.Breadth_First_Travel(0, v - 1) << endl;
                    // cout << "Shortest path will take: " << g.bfs(0, v - 1) << " days" << endl;
                    continue;
                }
                while (Aerial_V < 0)
                {
                    cout << "Invalid Input, try again3." << endl;
                    cout << "---> ";
                    cin >> Aerial_V;
                }

                for (int i = 0; i < Aerial_V; i++)
                {
                    cout << "From: ";
                    cout << "---> ";
                    cin >> from;
                    while (from > v || from < 0)
                    {
                        cout << "Invalid Input, try again. (Select values that are within range)" << endl;
                        cout << "---> ";
                        cin >> from;
                    }
                    cout << "To: ";
                    cout << "---> ";
                    cin >> to;
                    while (to > v || to < 0)
                    {
                        cout << "Invalid Input, try again. (Select values that are within range)" << endl;
                        cout << "---> ";
                        cin >> to;
                    }

                    while (from == to)
                    {
                        cout << "Invalid Input, try again. (Select values that are within range)" << endl;
                        cout << "---> ";
                        cin >> to;
                    }
                    from--;
                    to--;

                    g.addAir(from, to, 1);
                }
                g.connectSuccessively();
                g.printGraph();
                cout << "Reaches destination on day number:  " << g.Breadth_First_Travel(0, v - 1) << endl;
            }
        }
    }

    if (b == 0)
    {
        cout << "\n\n Thank you for using the City Planner!" << endl;
        cout << " --------------------------------------" << endl;
    }
}