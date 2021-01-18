/**
 * CS 2110 - Spring 2020 - Homework #9
 *
 * @author Shaotong Sun
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return 1 if
 * the function returns a int).
 */

// Do not add ANY additional includes!!!
#include "list.h"

/* You should NOT have any global variables. */

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked List. */
static inline Node *create_node(char *data);

/** create_node
  *
  * Helper function that creates a Node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @param data a void pointer to data the user wants to store in List
  * @return a Node
  */
static Node* create_node(char *data)
{
    Node* temp = malloc(sizeof(Node));
    if (temp == NULL) {
      return NULL;
    }
    temp->data = data;
    temp->next = NULL;
    return temp;
}

/** create_list
  *
  * Creates a struct linked_list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head and tail to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @return a pointer to a new struct list or NULL on failure
  */
LinkedList *create_list(void)
{
    LinkedList* temp = malloc(sizeof(LinkedList));
    if (temp == NULL) {
      return NULL;
    }
    temp->head = NULL;
    temp->size = 0;
    return temp;
}

/** push_front
  *
  * Adds the element at the front of the struct linked_list.
  *
  * @param list a pointer to the struct linked_list structure.
  * @param data the data to add to the struct linked_list.
  * @return  1 if the struct linked_list is NULL, 0 if successful,
  */
int push_front(LinkedList *list, char *data)
{
    if (list == NULL) {
      return 1;
    }
    return add_at_index(list, data, 0);
}

/** push_back
  *
  * Adds the element to the back of the LinkedList.
  *
  * @param list a pointer to the LinkedList structure.
  * @param data the data to add to the LinkedList.
  * @return 1 if the LinkedList is NULL, 0 if successful.
  */
int push_back(LinkedList *list, char *data)
{
    if (list == NULL) {
      return 1;
    }
    return add_at_index(list, data, list->size);
}

/** add_at_index
  *
  * Add the element at the specified index in the LinkedList. This index must lie in
  * the inclusive range [0,size].
  * For example, if you have no elements in the LinkedList,
  * you should be able to add to index 0 but no further.
  * If you have two elements in the LinkedList,
  * you should be able to add to index 2 but no further.
  *
  * @param list a pointer to the LinkedList structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to add to the LinkedList
  * @return 1 if the index is out of bounds or the LinkedList is NULL
  *         (do not add the data in this case)
  *         otherwise (on success) return 0
  */
int add_at_index(LinkedList *list, char *data, int index)
{
    if (list == NULL || index < 0 || index > list->size) {
      return 1;
    }
    int i = 0;
    Node* temp = list->head;
    Node* node = create_node(data);
    if (index == 0) {
      node->next = temp;
      list->head = node;
      list->size += 1;
    } else { 
      while (i < index - 1) {
        temp = temp->next;
        i++;
      }
      node->next = temp->next;
      temp->next = node;
      list->size += 1;
    }
    return 0;
}

/** get
  *
  * Gets the data at the specified index in the LinkedList
  *
  * @param list a pointer to the LinkedList structure
  * @param index 0-based, starting from the head.
  * @param dataOut A pointer to a pointer used to return the data from the
  *        specified index in the LinkedList or NULL on failure.
  * @return 1 if dataOut is NULL or index is out of range of the LinkedList or
  *         the LinkedList is NULL, 0 (on success) otherwise
  */
int get(LinkedList *list, int index, char **dataOut)
{
    if (list == NULL) {
      if (dataOut != NULL) {
        *dataOut = NULL;
      }
      return 1;
    }
    if (index < 0 || index >= list->size) {
      if (dataOut != NULL) {
        *dataOut = NULL;
      }
      return 1;
    }
    if (list->size == 0) {
      if (dataOut != NULL) {
        *dataOut = NULL;
      }
      return 1;
    }
    if (dataOut == NULL) {
      return 1;
    }
    if (index == 0) {
      Node *node = list->head;
      *dataOut = node->data;
    } else {
      int i = 0;
      Node *temp = list->head;
      while (i < index) {
        temp = temp->next;
        i++;
      }
      *dataOut = temp->data;
    }
    return 0;
}

/** contains
  *
  * Traverses the LinkedList, trying to see if the LinkedList contains some
  * data. We say the list contains the data if the data string of the node 
  * matches the node passed in.
  *
  * You may use the string library functions to complete this comparison
  * (see what is included in list.h)
  * 
  * If there are multiple pieces of data in the LinkedList which are equal to
  * the "data" parameter, return the one at the lowest index.
  *
  *
  * @param list a pointer to the LinkedList structure
  * @param data The data, to see if it exists in the LinkedList
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the LinkedList or NULL on failure
  * @return int    0 if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else 1
  */
int contains(LinkedList *list, char *data, char **dataOut)
{
    if (dataOut == NULL || list == NULL) {
      return 0;
    }
    if (list->size == 0) {
      *dataOut = NULL;
      return 0;
    }
    Node* temp = list->head;
    for (int i = 0; i < list->size; i++) {
      if (strcmp(data, temp->data) == 0) {
        *dataOut = temp->data;
        return 1;
      }
      temp = temp->next;
    }
    *dataOut = NULL;
    return 0;
}

/** pop_front
  *
  * Removes the List_node at the front of the LinkedList, and returns its data to the user.
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                List_node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_front(LinkedList *list, char **dataOut)
{
  if (dataOut == NULL || list == NULL || list->size == 0) {
    return 1;
  }
  Node *temp = list->head;
  *dataOut = temp->data;
  list->head = temp->next;
  list->size -= 1;
  free(temp);
  return 0;
}

/** pop_back
  *
  * Removes the ListNode at the back of the LinkedList, and returns its data to the user
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                ListNode or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_back(LinkedList *list, char **dataOut)
{
  if (list == NULL || list->size == 0) {
    if (dataOut != NULL) {
      *dataOut = NULL;
    }
    return 1;
  }
  return remove_at_index(list, dataOut, list->size - 1);
}


/** remove_at_index
  *
  * Remove the element at the specified index in the LinkedList.
  *
  * @param list a pointer to the LinkedList structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to remove from the LinkedList
  * @return 1 if the index is out of bounds, the LinkedList is NULL or
  *         the dataOut is NULL
  *         otherwise return 0
  */
int remove_at_index(LinkedList * list, char **dataOut, int index) 
{
    if (list == NULL || index < 0 || index >= list->size || dataOut == NULL) {
      if (dataOut != NULL) {
        *dataOut = NULL;
      }
      return 1;
    }
    int i = 0;
    Node* temp = list->head;
    if (list->size == 1) {
      *dataOut = temp->data;
      free(temp);
      list->head = NULL;
      list->size = 0;
    } else if (index == 0) {
      list->head = temp->next;
      *dataOut = temp->data;
      free(temp);
      list->size--;
    } else {
      while (i < index - 1) {
        temp = temp->next;
        i++;
      } 
      Node *next = temp->next;
      Node *nnext = next->next;
      *dataOut = next->data;
      temp->next = nnext;
      free(next);
      list->size--;
    }
    return 0;
}

/** empty_list
  *
  * Empties the LinkedList. After this is called, the LinkedList should be
  * empty. This does not free the LinkedList struct itself, just all nodes and
  * data within. Make sure to check that listToEmpty is not NULL before
  * using it.
  *
  * You may call free on a char pointer as well as a node struct pointer.
  *
  * @param list a pointer to the LinkedList structure
  */
void empty_list(LinkedList *list)
{   
    if (list == NULL) {
      return;
    }
    if (list->size == 0) {
      return;
    }
    if (list->size == 1) {
      Node *temp = list->head;
      free(temp->data);
      free(temp);
      list->head = NULL;
      list->size = 0;
    } else {
      Node* temp1 = list->head;
      Node* temp2 = temp1->next;
      for (int i = 0; i < list->size; i++) {
        temp2 = temp1->next;
        free(temp1->data);
        free(temp1);
        temp1 = temp2;
      }
      list->head = NULL;
      list->size = 0;
    }
}


/** merge_nodes
  *
  *
  * Concatenate the string data in two adjacent nodes (at index and index + 1), 
  * then remove the extra un-merged node. 
  *
  *     LinkedList *A: "CS" -> "2110" -> "Rocks" -> "!" -> NULL
  *
  *     merge_nodes(A, 0): "CS2110" -> "Rocks" -> "!" -> NULL
  *
  * @param list  LinkedList to operate on
  * @param index  Index of the first node to merge
  * @return 1 if the index is out of bounds, or the LinkedList is NULL
  *         otherwise return 0
  */
int merge_nodes(LinkedList *list, int index)
{
    if(list == NULL || index < 0 || index >= list->size - 1 || list->size == 0) {
      return 1;
    }
    Node *node = list->head;
    int i = 0;
    while (i < index) {
      i++;
      node = node->next;
    }
    char *str_a = malloc(sizeof(char) * (strlen(node->next->data) + 1));
    char *str_b = malloc(sizeof(char) * (strlen(node->data) + strlen(node->next->data) + 1));
    strcpy(str_a, node->next->data);
    strcpy(str_b, node->data);
    strcat(str_b, str_a);
    free(node->data);
    node->data = str_b;
    Node *next = node->next;
    node->next = next->next;
    free(next->data);
    free(str_a);
    //free(str_b);
    free(next);
    list->size-=1;
    return 0;
}


