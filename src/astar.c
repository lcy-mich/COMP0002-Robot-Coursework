#include <astar.h>
#include <graphics.h>
#include <stdlib.h>
#include <limits.h>

// priority queue

// binary heap
void createTree(HeapValue value, HeapValue array[], int size, int* last_index) {
    for (int i = 0; i < size; i++) {
        array[i] = EMPTY_HEAPVALUE;
    }
    array[1] = value;
    *last_index = 1;
}

void _swap_BinaryHeap(int a_index, int b_index, HeapValue array[]) {
    HeapValue temp = array[a_index];
    array[a_index] = array[b_index];
    array[b_index] = temp;
}

int _leftIndex_BinaryHeap(int current_index, int last_index) {
    if (current_index * 2 > last_index) {
        return 0;
    }
    return current_index * 2;
}

int _rightIndex_BinaryHeap(int current_index, int last_index) {
    if (current_index * 2 + 1 > last_index) {
        return 0;
    }
    return current_index * 2 + 1;
}

int _parentIndex_BinaryHeap(int current_index) {
    if (current_index == 1) {
        return 0;
    }
    return current_index/2;
}

void _floatDown_BinaryHeap(int current_index, int last_index, HeapValue array[]) {
    while (1) {
        int left_priority = INT_MAX;
        int right_priority = INT_MAX;

        if (_leftIndex_BinaryHeap(current_index, last_index)) {
            left_priority = array[_leftIndex_BinaryHeap(current_index, last_index)].priority;
        }
        if (_rightIndex_BinaryHeap(current_index, last_index)) {
            right_priority = array[_rightIndex_BinaryHeap(current_index, last_index)].priority;
        }

        int smaller_priority_index = left_priority <= right_priority ? 
            _leftIndex_BinaryHeap(current_index, last_index) : 
            _rightIndex_BinaryHeap(current_index, last_index);

        if (smaller_priority_index > 0 && array[smaller_priority_index].priority < array[current_index].priority) {
            _swap_BinaryHeap(smaller_priority_index, current_index, array);
            current_index = smaller_priority_index;
            continue;
        }
        break;
    }
}

void _floatUp_BinaryHeap(int current_index, HeapValue array[]) {
     while (current_index > 1) {
        if (array[_parentIndex_BinaryHeap(current_index)].priority > array[current_index].priority) {
            _swap_BinaryHeap(_parentIndex_BinaryHeap(current_index), current_index, array);
            current_index = _parentIndex_BinaryHeap(current_index);
            continue;
        }        
        break;
    }
}

int insert_BinaryHeap(HeapValue value, HeapValue array[], int size, int* last_index) {

    if (*last_index >= size - 1) {
        return 0;
    }
    array[++(*last_index)] = value;

    _floatUp_BinaryHeap(*last_index, array);

    return 1;
    
}

int isEmpty_BinaryHeap(int last_index) {

    return (last_index < 1);

}

HeapValue extractMin_BinaryHeap(HeapValue array[], int* last_index) {

    if (!isEmpty_BinaryHeap(*last_index)) {
        HeapValue min = array[1];

        _swap_BinaryHeap(1, *last_index, array);
        (*last_index)--;
        _floatDown_BinaryHeap(1, *last_index, array);

        return min;
    }
    return EMPTY_HEAPVALUE;
}

// linked list for separate chaining
void append_LinkedList(Vector key, NodeData data, LinkedList* list) {

    Node* element = malloc(sizeof(Node));
    element->key = key;
    element->data = data;
    

    if (list->length == 0) {
        list->head = element;
        list->tail = element;
        element->previous =  NULL;
    } else {
        list->tail->next = element;
        element->previous = list->tail;
    }

    element->next = NULL;
    list->tail = element;

    list->length++;

}

//returns 0 if not found
Node* find_LinkedList(Vector key, LinkedList* list) {

    Node* current_pointer = list->head;
    if (!current_pointer) {
        return 0;
    }

    while (current_pointer && !equals(current_pointer->key,key)) {
        current_pointer = current_pointer->next;
    }
    return current_pointer;

}

//returns 1 if removed, 0 if not
int remove_LinkedList(Vector key, LinkedList* list) {

    Node* element_to_remove = find_LinkedList(key, list);

    if (!element_to_remove) {
        return 0;
    }
    
    // update first and last pointers
    if (element_to_remove == list->head) {
        list->head = element_to_remove->next;
    }
    if (element_to_remove == list->tail) {
        list->tail = element_to_remove->previous;
    }

    // relink elements around element to remove
    if (element_to_remove->previous) {
        (element_to_remove->previous)->next = element_to_remove->next;
    }
    if (element_to_remove->next) {
        (element_to_remove->next)->previous = element_to_remove->previous;
    }

    free(element_to_remove);
    list->length--;

    return 1;
}

// hashtable for vectors that uses separate chaining

// vector components has to both be positive
long long _hash_HashTable(Vector a) {

    return ((long long)abs(a.y) << sizeof(int)*8) + abs(a.x);

}

// returns 0 if doesnt exist
int getValue_HashTable(Vector key, LinkedList* table[], int table_size) {
    int index = _hash_HashTable(key) % table_size;

    Node* found = find_LinkedList(key, table[index]);

    if (!found) {
        return 0;
    }

    return found->data.value;
}

// returns NULL_VECTOR if doesnt exist
Vector getVector_HashTable(Vector key, LinkedList* table[], int table_size) {
    int index = _hash_HashTable(key) % table_size;

    Node* found = find_LinkedList(key, table[index]);

    if (!found) {
        return NULL_VECTOR;
    }

    return found->data.vector;
}

void cleanup_HashTable(LinkedList* table[], int table_size) {

    if (!table) {
        return;
    }

    for (int i = 0; i < table_size; i++) {

        if (!table[i]) { 
            continue;
        }

        Node* element = table[i]->head;
        while (element) {
            Node* next = element->next;
            free(element);
            element = next;
        }

        free(table[i]);

    }
}

// returns 0 if doesn't exist
int remove_HashTable(Vector key, LinkedList* table[], int table_size) {
    int index = _hash_HashTable(key) % table_size;

    return remove_LinkedList(key, table[index]);
}

void insert_HashTable(Vector key, NodeData data, LinkedList* table[], int table_size) {
    int index = _hash_HashTable(key) % table_size;

    Node* found_node = find_LinkedList(key, table[index]);
    if (found_node) {
        found_node->data = data;
        return;
    }
    append_LinkedList(key, data, table[index]);
}

void createHashTable(LinkedList* table[], int table_size) {
    for (int i = 0; i < table_size; i++) {
        table[i] = malloc(sizeof(LinkedList));
        
        table[i]->head = NULL;
        table[i]->tail = NULL;
        table[i]->length = 0;
    }
}

// a star

float calculateHeuristic(Vector pos, Vector dest) {
    return distance(pos, dest);
}

// alias of cleanup_HashTable
void freePath(LinkedList* path[], int table_size) {
    cleanup_HashTable(path, table_size);
    
    if (path) { 
        free(path);
    }
}

void followPath(Robot* robot, LinkedList* path[], int table_size, int grid[], Vector grid_size) {

    Vector next_vector = getVector_HashTable(robot->pos, path, table_size);

    if (!equals(next_vector, NULL_VECTOR)) {
        Robot dummy_robot = *robot;
        int turn_amount = -1; // -1 so that the first increment starts at 0 turns
        
        // on the basis that the next vector in path is in the neighbourhood of current position of robot
        while (!equals(dummy_robot.pos, next_vector)) {
            dummy_robot = *robot;
            turn_amount++;
            
            for (int turns = 0; turns < turn_amount; turns++) {
                left(&dummy_robot);
            }
            forward(&dummy_robot, grid, grid_size);
        }

        for (int turns = 0; turns < turn_amount; turns++) {
            left(robot);
        }
        forward(robot, grid, grid_size);
        
        return;
    }
}

// calculates path starting from goal to robot then removes
LinkedList** pathfind(Robot* robot, Vector dest, int table_size, int grid[], Vector grid_size) {

    const int total_grid_size = grid_size.x*grid_size.y;

    // initialise binary heap
    HeapValue frontier[total_grid_size];

    int last_index;

    HeapValue root;
    root.pos = dest;
    root.priority = 0;

    createTree(root, frontier, total_grid_size, &last_index);

    // initialise hashtables
    LinkedList** came_from;
    came_from = malloc(sizeof(LinkedList*)*table_size);

    LinkedList* cost[table_size];
    createHashTable(came_from, table_size);
    createHashTable(cost, table_size);

    insert_HashTable(dest, (NodeData){.vector = NULL_VECTOR}, came_from, table_size);
    insert_HashTable(dest, (NodeData){.value = 0}, cost, table_size);
    

    // while frontier is not empty
    while (!isEmpty_BinaryHeap(last_index)) {
        Vector current_pos = extractMin_BinaryHeap(frontier, &last_index).pos;

        if (equals(current_pos, robot->pos)) {
            break;
        }

        // assign values for all neighbours
        for (int dir_index = 0; dir_index < 4; dir_index++) {
            Vector neighbour_pos = add(current_pos, DIR_VECTORS[dir_index]);

            GridObjects object = getObjectAtPosition(neighbour_pos, grid, grid_size);
            if (object != AIR && object != MARKER) {
                continue;
            }

            int new_cost = getValue_HashTable(current_pos, cost, table_size) + 1;
            int neighbour_cost = getValue_HashTable(neighbour_pos, cost, table_size);

            if (!neighbour_cost || neighbour_cost > new_cost) {

                insert_HashTable(neighbour_pos, (NodeData){.value = new_cost}, cost, table_size);
                insert_HashTable(neighbour_pos, (NodeData){.vector = current_pos}, came_from, table_size);

                insert_BinaryHeap((HeapValue){
                    .priority = new_cost + calculateHeuristic(neighbour_pos, robot->pos),
                    .pos = neighbour_pos
                }, frontier, total_grid_size, &last_index);
            }
        }
    }
    cleanup_HashTable(cost, table_size);
    return came_from;
}