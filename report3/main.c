#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NAME 10

/*
* structure for graph
*
* variables:
*   city: current city
*   deparTime: departure time from current city
*   *current: the city that the flight was departed
*   *destCity: destination city
*/
struct path {
    char city; //current city
    int deparTime; //departure time from current city

    struct path *current; //the city where the flight was departed
    struct path *destCity; //destination city
};

/**
 * structure for RB tree
 *
 * variables: 
 *   data = id or key of RB tree
 *   color = color of the node
 *   *path = flight path
 *   *left = left child of node
 *   *right = right child of node
 *   *parent = current node's parent node
*/
struct node {
    int data; //id
    char color; //whether red or black
    char source; //source
    char dest; //destination
    char name[NAME]; //name

    struct path *path; //flight path
    struct node *left, *right, *parent; //each left child, right child, and parent node
};

/*
* Function: inorder
* Prints the rb tree inorder
*
* variables:
*   *root: current node of the tree
*/
void inorder(struct node *root){
    /* if tree doesn't exist, print nothing */
    if (root == NULL){
        return;
    }
    /* if tree exists, print nodes' ids and colors from left node to right node */
    inorder(root->left);
    printf("%d(%c) ", root->data, root->color);
    inorder(root->right);
}

/**
 * Function: leftRotate
 * function to rotate two nodes leftward
 * 
 * variables: 
 *  root: root of the tree
 *  x and y: two target nodes that will be rotated
*/
void leftRotate(struct node **root, struct node *x){
    struct node *y = x->right; //let y be x's right child node
    x->right = y->left; //make x's right child as y's left subtree

    /* if x's right child is not NULL */
    if (x->right != NULL){
        x->right->parent = x; //update x's right parent to x
    }
    y->parent = x->parent; //update y's parent to x's parent
    
    /* if x's right child is NULL */
    if (x->right == NULL){
        (*root) = y; //make y node as root of the tree
    }
    /* two cases(right or left) of y's place at x's place */
    else if (x == x->parent->left){
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->left = x; //make x as y's left child
    x->parent = y; //make y as x's parent. leftRotation done
}

/**
 * Function: rightRotate
 * the same as function leftRotate but change 'right' to 'left'
 * and 'left' to 'right'. Except that, everything is the same.
*/
void rightRotate(struct node **root, struct node *y){
    struct node *x = y->right;
    y->right = x->left;

    if (x->right != NULL){
        x->right->parent = x;
    }
    x->parent = y->parent;
    
    if (x->right == NULL){
        (*root) = x;
    }
    else if (y == y->parent->left){
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

/**
 * Function: insertFixup
 * After insert to rb tree is done, this function checks if the 
 * place and the color of inserted node is in right place and right
 * color. If yes, leave the node. If not, do the rotate and change
 * the color to fixup the tree. 
 * 
 * variables: 
 *  z: current node that is inserted 
 *  y: uncle of z
 * 
 * not variable but just in case, 'R' is red and 'B' is black
*/
void insertFixup(struct node **tree, struct node *z){
    /* if z's parent's color is red and z is not root of tree, loop following */
    struct node *root = *tree;

    while (z != root && z->parent->color == 'R' && z->color != 'B'){
        struct node *y = NULL; //initialize uncle node as NULL

        /* if z is left subtree */
        if (z->parent == z->parent->parent->left){
            y = z->parent->parent->right; //uncle will be in right subtree. Store uncle node to y
            /* if uncle does exist and color of y is red (case 1) */
            if ((y != NULL) && (y->color == 'R')){
                /* recoloring */
                z->parent->color = 'B'; 
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent; 
            }
            /* else, case 2 or 3 */
            else {
                /* if z is right node (case 2) */
                if (z == z->parent->right){
                    z = z->parent; //set z as current node's parent
                    leftRotate(tree, z); //left rotation with current node's parent
                }
                /* case 3 */
                /* recoloring */
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(tree, z->parent->parent); //right rotate with grapdparent
            }
        }
        /* else, current node is in right subtree */
        else {
            y = z->parent->parent->left; //uncle will be in left subtree. store uncle node to y
            /* Following is the same as upper case 1, 2, and 3 except 'left' changed to 'right' and 'right' changed to 'left' */
            if ((y != NULL) && (y->color == 'R')){
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left){
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    (*tree)->color = 'B'; //set root color to black always;
}

/**
 * Function: rbInsert
 * inserts nodes to rb tree with labels with id. There will be 10
 * inserts so id will be 1 to 10.
 * 
 * variables:
 *  data: id
 *  z: current node
 *  x and y: other nodes
*/
void rbInsert(struct node **root, struct path *path, char name[10], int data, char source, char dest){
    struct node *z = (struct node*)malloc(sizeof(struct node)); //dynamically allocate the size to z
    
    //z->left = z->right = z->parent = NULL; //set z's parent, left, and right child as NULL

    for (int i = 0; name[i] != '\0'; i++){
        z->name[i] = name[i];
    }
    z->path = path;
    z->data = data; //assign id to z
    z->source = source;
    z->dest = dest;

    struct node *y = NULL; //set y as NULL
    struct node *x = (*root); //set x as root of tree
    
    /* if x is not NULL, loop following */
    while (x != NULL){
        y = x; //set y as x

        /* if id of z is less than x's */
        if (z->data < x->data){
            x = x->left; //move to left
        }
        else if (z->data > x->data){
            x = x->right; //else, move to right
        }
        else {
            printf("Unsuccessful insertion\n\n");
            return;
        }
    }
    z->parent = y; //set z's parent to y

    printf("Before insertion:\n");
    inorder(*root);
    printf("\n");
    
    /* if tree is empty */
    if (y == NULL){
        *root = z; //set z as root of the tree
    }
    /* if z's id is less than y's */
    else if (z->data < y->data){
        y->left = z; //set z as left child of y
    }
    else if (z->data > y->data){
        y->right = z; //else, set z and right child of y
    }

    z->left = NULL;
    z->right = NULL;
    z->color = 'R'; //set z's color as red

    insertFixup(root, z); //call insertFixup to check

    printf("After insertion:\n");
    inorder(*root);
    printf("\n\n");
}

/**
 * Function: randGraph
 * randomize cities and their own departure time. randomized cities
 * in int value for convenience. int value will be changed to char
 * in other functions. 
 * 
 * variables: 
 *  graph: graph that vertices are cities and edges are path
 *  count: counter to count connected cities for each city
 *  i and j: for iteration
 *  connects: required paths from one city to another. (10 required)
 *  randCity: randomly picked cities
 *  departrueTime: departure time from the city
*/
void randGraph(int graph[26][26]){
    srand(time(NULL));
    int i, j;
    int count[26] = {0,0,};

    /* i compared to 26 because there are 26 cities */
    for (i = 0; i < 26; i++){
        int connects = 10; //set connects to 10
        
        /* check if two vertices already connected */
        for (j = 0; j < 26; j++){
            /* if yes, */
            if (graph[i][j] != -1){
                connects--; //reduce connects
            }
        }

        /* randomly assign connects */
        for (j = 0; j < connects; j++){
            int randCity = rand()%26; //assign random cities
            
            /* If randomly generated city is same to current city or path is already existed, */
            if (randCity == i || graph[i][randCity] != -1){
                j--; //restart random generation
            }
            /* or randomly generated city has become arrived city for 14 times, */
            else if (count[randCity] == 14){
                j--; //restart random generation
            }
            /* none of above, make it bidirectional */
            else {
                graph[i][randCity] = 0;
                graph[randCity][i] = 0;
                count[i]++;
                count[randCity]++;
            }
        }

        /* randomly generate departure time for 26 cities */
        for (j = 0; j < 26; j++){
            /* if city exists, */
            if (graph[i][j] != -1){
                int departureTime = rand()%24; //randomly generate departure time
                graph[i][j] = departureTime; //assign generated time to graph
            }
        }
    }
}

/**
 * Function: checkFlight
 * check if the path from source to destination exists
 * 
 * variables: 
 *  path: path from source to destination
 *  pathway: temporary variable
 *  count: counter to count if city is already visited
 *  sourInt: int value of source in char converted into int
 *  destInt and finalDest: int value of destination in char converted into int
 *  destination: variable to store final destination and compare to input destination
 *  minTime: arrival time
*/
int checkFlight(struct path **path, int graph[26][26], char source, char dest){
    struct path *pathway = (struct path*)malloc(sizeof(path)); //dynamically allocte to path
    pathway->current = NULL; 
    int count[26] = {0,0,};
    int sourInt = source-97;
    int destInt = dest-97;
    int finalDest = dest-97;
    char destination;

    /* if source and finl destination is equal, quit */
    if (sourInt == finalDest){
        return 0;
    }
    count[sourInt] = 1; //initialize count as 1

    /* if there is direct path, */
    if (graph[sourInt][finalDest] != -1){
        pathway->city = source; //set current city as source
        pathway->deparTime = graph[sourInt][finalDest]; //set departure time as from source to destination
        pathway->destCity = NULL; //no via so set NULL
        *path = pathway; //set path as pathway
        return 1;
    }

    /* loop to find path */
    while (destination != dest || pathway->deparTime >= 23){
        int minTime;

        /* if there is via, */
        if (pathway->current != NULL){
            minTime = pathway->current->deparTime + 1; //set minTime as via's departure time+1

            /* case: there is direct path from source to destination */
            if (graph[sourInt][finalDest] != -1 && graph[sourInt][finalDest] >= minTime){
                destination = finalDest+97; 
                destInt = finalDest;
            }
            /* case: no direct path */
            else {
                for (int i = 0; i < 26; i++){
                    /* if there is a path and time is as minimum as possible, */
                    if (graph[sourInt][i] != -1 && graph[sourInt][i] < 24){
                        /* if never visited city and departure time is not over arrival time */
                        if (count[i] != 1 && graph[sourInt][i] >= minTime){
                            minTime = graph[sourInt][i];
                            destination = i+97;
                            destInt = i;
                        }
                    }
                }
            }
        }
        else {
            minTime = 24;
            /* same as above if case but the city is never visited */
            for (int i = 0; i < 26; i++){
                if (graph[sourInt][i] != -1 && graph[sourInt][i] < minTime){
                    if (count[i] != 1){
                        minTime = graph[sourInt][i];
                        destination = i+97;
                        destInt = i;
                    }
                }
            }
        }
        pathway->city = sourInt+97; //set pathway value
        pathway->deparTime = graph[sourInt][destInt]; //set departure time from the city
        count[destInt] = 1;
        sourInt = destInt; //set new source to via

        /* if input destination has reached, */
        if (destination == dest){
            /* find the first source */
            while (pathway->current != NULL){
                pathway = pathway->current;
            }
            *path = pathway; //set path to the first source

            return 1;
        }
        struct path *temp = (struct path*)malloc(sizeof(path)); //dynamically allcate memory for new path
        temp->destCity = NULL;
        temp->current = pathway;
        pathway->destCity = temp; //connect cities
        pathway = pathway->destCity; //move to the next city
    }
    return 0;
}

/**
 * Function: printPath
 * print the path from source to destination
 * 
 * variables:
 *  temp: variable to store the path from checkFlight function
*/
void printPath(struct path *path){
    struct path *temp;
    temp = path;

    while (temp){
        /* when departure time is less than 12 */
        if (temp->deparTime < 12){
            /* if departure time is 0, it means 12AM */
            if (temp->deparTime == 0){
                printf(", %c(12AM)", temp->city); //print source city and 12AM
            }
            /* else, */
            else {
                printf(", %c(%dAM)", temp->city, temp->deparTime); //print source city and its departure time
            }
        }
        /* if departure time is 12, it means 12PM */
        else {
            if (temp->deparTime == 12){
                printf(", %c(12PM)", temp->city); //print source city and 12PM
            }
            /* else, */
            else {
                printf(", %c(%dPM)", temp->city, temp->deparTime); //print source city and its departure time
            }
        }
        temp = temp->destCity; //go to next city;
    }
    printf("\n");
}

/**
 * Function: input
 * function to get the input from the user and scan them after the
 * graph is created. Inserting nodes to rb tree, print the rb tree,
 * creating path from source to destination, checking the path, and
 * printing the path are all in this function. 
 * 
*/
void input(char name[], char source, char dest, int graph[26][26], struct path *path){
    int i = 1; //id of rb tree's node starting from 1
    struct node *root = NULL;
    /* User interface */
    printf("Airline Reservation System\n");
    printf("----------------------------------------------------------------------------------\n");
    /* 10 insertio required. Therefore, start the loop from i = 1 and ends the loop when i = 10 */
    while (i != 11){
        printf("Input your name, source, and destination in order:\n");
        printf("------------------------------------------------\n");
        scanf("%[^,], %c, %c", name, &source, &dest); //scan name, source, and destination
        
        /* call checkFlight function. If it's true(1), print following UI */
        if (checkFlight(&path, graph, source, dest) == 1){
            printf("Your reservation has been approved\n");
            printf("------------------------------------------------\n");
            printf("Flight details: \n");
            printf("%s, %c, %c", name, source, dest);
            printPath(path);
            printf("\n");
            printf("------------------------------------------------\n");            
            rbInsert(&root, path, name, i, source, dest);
            i++;
        }
        else {
            printf("Sorry. Your reservation has not been approved\n");
        }
    }
}

int main(){
    struct path *path; //path from source to destination
    struct node *tree = NULL; //rb tree initialy NULL
    char name[NAME], source, dest; //variables declaration
    int graph[26][26]; //variable declaration
    
    /* initialize graph for cities */
    for (int i = 0; i < 26; i++){
        for (int j = 0; j < 26; j++){
            graph[i][j] = -1;
        }
    }
    randGraph(graph); //call randGraph to create graph

    input(name, source, dest, graph, path); //call input
    
    return 0;
}