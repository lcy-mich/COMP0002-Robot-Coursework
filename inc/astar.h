#ifndef ASTAR_H
    #define ASTAR_H

    #include <robot.h>
    #include <vectors.h>

    typedef struct {
        int priority;
        Vector pos;
    } HeapValue;

    typedef union {
        int value;
        Vector vector;
    } NodeData;

    typedef struct Node Node;
    struct Node {
        Vector key;
        NodeData data;
        Node* previous;
        Node* next;
    };

    typedef struct {
        int length;
        Node* head;
        Node* tail;
    } LinkedList;

    LinkedList** pathfind(Robot* robot, Vector dest, int table_size, int grid[], Vector grid_size);
    
    int followPath(Robot* robot, LinkedList* path[], int table_size, int grid[], Vector grid_size);
    
    void freePath(LinkedList* path[], int table_size);

    Vector getClosestMarkerPosition(Vector pos, Vector* marker_pos, int total_markers);

#endif