bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    // Create the adjacency list for the graph
    int *inDegree = (int *)malloc(numCourses * sizeof(int));  // Array to track in-degrees
    int **graph = (int **)malloc(numCourses * sizeof(int *));  // Adjacency list for graph
    
    // Initialize the graph and in-degree array
    for (int i = 0; i < numCourses; i++) {
        graph[i] = (int *)malloc(numCourses * sizeof(int));  // Create space for the graph
        for (int j = 0; j < numCourses; j++) {
            graph[i][j] = 0;  // Initialize adjacency list to zero
        }
        inDegree[i] = 0;  // Initialize in-degree to 0
    }

    // Build the graph and in-degree array
    for (int i = 0; i < prerequisitesSize; i++) {
        int ai = prerequisites[i][0];
        int bi = prerequisites[i][1];
        
        graph[bi][ai] = 1;  // bi -> ai
        inDegree[ai]++;  // Increase the in-degree of ai
    }

    // Use Kahn's algorithm (BFS-based topological sorting)
    int *queue = (int *)malloc(numCourses * sizeof(int));
    int front = 0, rear = 0;
    
    // Enqueue all nodes with in-degree 0 (no prerequisites)
    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }
    
    int count = 0;  // To count the number of courses that can be taken
    
    // Process the queue
    while (front < rear) {
        int course = queue[front++];
        count++;
        
        // Reduce the in-degree of all neighbors (courses dependent on this course)
        for (int i = 0; i < numCourses; i++) {
            if (graph[course][i] == 1) {  // There is an edge course -> i
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    queue[rear++] = i;  // If in-degree becomes 0, add it to the queue
                }
            }
        }
    }
    
    // If we processed all courses, return true
    return count == numCourses;
}
