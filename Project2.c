// Aws Hammad - 1221697 - Section 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct stack {
    char name[50];
    int index;
    int wordindex;
    char op[10];
    struct stack *next;
};
struct queue {
    char word [50];
    struct queue* next;
};
struct queue* front;
struct queue* rear;
typedef struct stack *ptrStack;
typedef ptrStack Stack;
typedef struct queue *ptrqueue;
typedef ptrqueue Queue;
Queue Dequeue(Queue Q);
Stack Top (Stack S);
int wordCount = 0;// to keep up with the number of words we have in the array
int wordCountBefore = 0;// just to print the array before
int main() {
    Stack U = (Stack)malloc(sizeof(struct stack));
    U->next = NULL;
    Stack R = (Stack)malloc(sizeof(struct stack));
    R->next = NULL;
    Queue Q = (Queue)malloc(sizeof(struct queue));
    Q->next = NULL;
    rear=Q;
    front=Q;
    char *arrayBefore[1000];// the array that will not change
    char *Array[1000];// the array that will change
    int op=0;
    while (op!=10) {
        printMenu();
        scanf("%d",&op);
        switch(op) {
        case 1 :
            readWords(arrayBefore);// first I read the file and store it in the array that will not change
            copy (arrayBefore,Array);// then I copy the file text into the array that will change
            break;
        case 2 :
            print(arrayBefore);// printing the array before any changes
            break;
        case 3 :
            Insert(Q,Array,U);// insert words into the array
            break;
        case 4 :
            Remove (Q,Array,U);// remove words from the array
            break;
        case 5 :
            UndoOp(U,R,Array);// to reverse your last action
            break;
        case 6 :
            RedoOp(R,U,Array);// to reverse your last undo
            break;
        case 7 :
            printStack(U,R);// print the undo and redo stacks
            break;
        case 8 :
            printTextOnFile(Array);// print the new text on an output file
            break;
        case 9 :
            printAfter(Array);// I added this case to make it easier for you to test the changes on the text
            break;
        case 10 :
            printf("\nExiting the program...\nThanks for your time , Bye!\n");
            break;
        default :
            printf("\nERROR! Please enter a number between 1 and 10.\n");
            break;
        }
    }
}
// function to display the program menu
void printMenu() {
    printf("\nProgram Menu:\n");
    printf("-------------\n");
    printf("1. Load the input file\t\t\t");
    printf("2. Print the loaded text\n");
    printf("3. Insert strings to the text\t\t");
    printf("4. Remove strings from the text\n");
    printf("5. Perform Undo operation\t\t");
    printf("6. Perform Redo operation\n");
    printf("7. Print the Undo and the Redo stack\t");
    printf("8. Save the updated text to the output file\n");
    printf("9. Print the updated text\t\t");
    printf("10. Exit\n");
    printf("\nselect an option by entering its number: ");
}
void readWords(char *array[]) {
    FILE *in = fopen("read.txt", "r");// open a file to read from it
    if (in == NULL) {
        printf("Unable to open file \n");
        return;
    }
    char word[100];// to have the string we want to add to the array
    while (fscanf(in, "%s", word) == 1 && wordCount < 1000) {// to read words from the file until no more words or the limit is reached
        removeSpaces(word);// remove the spaces from the start and end of the word
        array[wordCount] = strdup(word);// put the word in the array
        wordCount++;// add one to the words counter
        wordCountBefore++;
    }
    printf("\nThe text for the file has been uploaded.\n");
    fclose(in);
}
void copy (char *array1[],char *array2[]) {
    for (int i = 0; i < wordCount; i++) {// from the first element to the last one in the array before
        array2[i] = strdup(array1[i]);// copy the word from the array before to the array after
    }
}
void print (char *array[]) {
    printf("\nWords from file :\n");
    for (int i = 0; i < wordCountBefore; i++) {// from the first element to the last one in the array before
        printf("%s ", array[i]);// print the word from the array before
    }
    printf("\n");
}
void printAfter (char *array[]) {
    printf("\nThe text is :\n");
    for (int i = 0; i < wordCount; i++) {// from the first element to the last one in the array after changes
        printf("%s ", array[i]);// print the word from the array before
    }
    printf("\n");
}
void removeSpaces(char *name) {
    if (name == NULL || *name == '\0') return;
    char *start = name, *end;
    while (*start == ' ' || *start == '\t') start++;// make the start pointer moves forward over the spaces
    if (*start == '\0') {// if only spaces was found set the original string to empty and return
        *name = '\0';
        return;
    }
    end = start + strlen(start) - 1;// set the end pointer to the last character of the string
    while (end > start && (*end == ' ' || *end == '\t')) end--;// make the end pointer moves backwards over the spaces
    *(end + 1) = '\0';// set the character after the last non-space character to '\0' to end the string
    if (start > name) {// if any space in the start was skipped move the non-space part of the string to the beginning
        char *temp = start;
        while (*temp) {// copy characters from 'start' to the beginning of the string
            *name++ = *temp++;
        }
        *name = '\0';// set the character after the last non-space character to '\0' to end the string
    }
}
void Insert (Queue Q,char *wordsArray[],Stack S) {
    printf("\nEnter a word/sentence to insert : ");// ask the user to enter a word or sentence to insert
    char sentence[1000];// string to have the sentence the user entered
    char temp[100];// to have the word from the queue
    while (getchar() != '\n');// to stop reading when the user write (Enter)
    scanf("%49[^\n]", sentence);
    printAfter(wordsArray);// print the text to make the user choose the word he wants to insert after it
    printf("\nAfter which word you want to insert (%s) [Press (Enter) to insert at the first] : ",sentence);
    char word[100];// the word that the user want to insert after it
    while (getchar() != '\n');
    scanf("%49[^\n]", word);
    char *t = strtok(sentence, " ");// split the sentence into words to add them to the queue
    while (t != NULL ) {
        removeSpaces(t);
        Enqueue(t,Q);// add the word to the queue
        t = strtok(NULL, " ");// move to the next word
    }
    Queue q = Q;// a queue that points on the original queue
    if (strlen(word)==1) {// if the user pressed (Enter) then add the sentence at first
        int wordindex=0;
        int charindex = 0;
        while (wordCount < 1000 && q->next != NULL) {// insert until the array is full or queue is empty
        q = Dequeue(Q);// First In First Out
        strcpy(temp,(q->word));// put the word in temp
        for (int j = wordCount; j > wordindex; j--) {// shift all the elements to make space for the new word
            wordsArray[j]=wordsArray[j-1];
        }
        wordsArray[wordindex] = strdup(temp);// put the new word in its position
        wordCount++;// add one to the words counter
        printf("%s has been inserted :)\n",temp);
        Push(S,temp,"Insert",charindex,wordindex);// push the word and its index to the undo stack
        strcpy(word,(q->word));// copy the last word we inserted in case the user inserted more than one word
        charindex+=strlen(word)+1;// add the length of the word to the character index
        wordindex++;// go to the next word index
        }
    } else {// if not at the first
        while (wordCount < 1000 && q->next != NULL) {// insert until the array is full or queue is empty
            q = Dequeue(Q);
            strcpy(temp,(q->word));
            int count=0;// number of times the word that the user wants to insert after it repeated
            int wordindices [10]= {0};// if the word that the user wants to insert after it exist more than one time
            int charindices [10]= {0};
            int wordindex=0;// the word index of the current word
            int charindex=0;// the character index of the current word
            int i=0;
            while (wordindex < wordCount && i<10) {// loop until the end of the array or the word repeated 10 times
                if (strcasecmp(word,wordsArray[wordindex])==0) {// if we found the word to insert after
                    wordindices[i] = wordindex+1;// the index of the word is after it by 1
                    charindices[i]=charindex;
                    count++;// to keep up with the number of repeated words
                    i++;
                }
                charindex+=strlen(wordsArray[wordindex])+1;// update the character index
                wordindex++;// update the word index
            }
            if (count==0) {// if the word the user want to insert after it does not exist
                printf("word %s does not exists !\n",word);
                break;
            }
            int rank=1;
            if (count>1) {// if the word is repeated more than once
                printf("\nThere is more than one (%s) enter which one do you want to insert (%s) after it?\n",word,temp);
                printAfter(wordsArray);// to make the user choose which one to insert after
                printf("\nEnter the number of its ranking between its similar words : ");
                int j=1;
                while (j<=count) {
                    printf("%d? ",j);// print the rankings of the repeated words
                    j++;
                }
                scanf("%d",&rank);
            }
            wordindex=wordindices[rank-1];// put the proper word index from the array into the current word index
            charindex=charindices[rank-1]+strlen(word)+1;// the proper character index from the array into the current character index
            //printf("%d",wordindex);// this is for debugging :)
            if (wordindex==wordCount) charindex = -1; // if the insertion is at the last
            for (int j = wordCount; j > wordindex; j--) {
                wordsArray[j]=wordsArray[j-1];// now shift all the elements to make space for our word
            }
            wordsArray[wordindex] = strdup(temp);// insert the word in its proper place
            wordCount++;
            printf("%s has been inserted :)\n",temp);
            Push(S,temp,"Insert",charindex,wordindex);// push the word into the undo stack
            strcpy(word,(q->word));// update the word
        }
    }
}
void Remove (Queue Q,char *wordsArray[],Stack S) {
    printAfter(wordsArray);
    printf("\nEnter a word/sentence to delete : ");// ask the user to enter a word or sentence to delete
    char sentence[1000];// string to have the sentence the user entered
    char temp[100];// to have the word from the queue
    while (getchar() != '\n');// to stop reading when the user write (Enter)
    scanf("%49[^\n]", sentence);
    char *t = strtok(sentence, " ");
    while (t != NULL ) {// split the sentence into words to add them to the queue
        removeSpaces(t);
        Enqueue(t,Q);// add the word to the queue
        t = strtok(NULL, " ");// move to the next word
    }
    Queue q = Q;
    while (wordCount < 1000 && q->next != NULL) {
        q = Dequeue(Q);
        strcpy(temp,(q->word));// have the word to delete in temp
        int wordindex = 0;
        int charindex =0;
        while (strcasecmp(temp,wordsArray[wordindex])!=0 && wordindex < wordCount) {//loop until the end of the array or find the word to delete
            charindex+=strlen(wordsArray[wordindex])+1;// update the character index by adding the length of the word and the space
            wordindex++;// add one to the word index
        }
        if (strcasecmp(temp,wordsArray[wordindex])==0) {// if the word is found
            //printf("%d",wordindex);// for debugging :)
            Push (S, temp,"Remove",charindex+1,wordindex);// push the word to the undo stack
            while (wordindex<wordCount-1) {
                wordsArray[wordindex]=wordsArray[wordindex+1];// shift all the elements to delete the word that have the word index
                wordindex++;
            }
            wordCount--;// removed one element
            printf("%s has been removed :(\n",temp);
        } else {
            printf("%s does not exist !\n",sentence);
        }
    }
}
void UndoOp (Stack U,Stack R,char *wordsArray[]) {
    if (U==NULL || U->next==NULL) {
        printf("Empty Stack !\n");
        return;
    } else {
        Stack temp = Top(U);// make temp points on the top of the undo stack
        char word[100];// a word to take the word from the undo stack
        strcpy(word,(temp->name));
        Pop(U);// pop the node from the undo stack
        Push(R,word,temp->op,temp->index,temp->wordindex);// push from undo to the redo stack
        int wordindex = temp->wordindex;// store the word index of the temp word
        int charindex =temp->index;// store the character index of the temp word
        if (strcasecmp(temp->op,"Insert")==0) {// if the operation was insert we will remove it in the undo
            while (wordindex<wordCount-1) {
                wordsArray[wordindex]=wordsArray[wordindex+1];// shifting to remove
                wordindex++;
            }
            wordCount--;// removed the word
        } else if (strcasecmp(temp->op, "Remove") == 0) {// if the operation was remove we will insert the removed word
            if (charindex == -1) temp->wordindex = wordCount; // if the insertion is at the last
            int index = temp->wordindex;
            for (int j = wordCount; j > index; j--) {// shifting to make space for the word
                wordsArray[j]=wordsArray[j-1];
            }
            wordsArray[index] = strdup(word);// insert the word in its place
            wordCount++;
        }
    }
}
void RedoOp (Stack R,Stack U,char *wordsArray[]) {
    if (R==NULL || R->next==NULL) {
        printf("Empty Stack !\n");
        return;
    } else {
        Stack temp = Top(R);// make temp points on the top of the redo stack
        char word[100];// a word to take the word from the redo stack
        strcpy(word,(temp->name));
        Pop(R);// pop the node from the redo stack
        Push(U,word,temp->op,temp->index,temp->wordindex);// push from redo to the undo stack
        int wordindex = temp->wordindex;// store the word index of the temp word
        int charindex =temp->index;// store the character index of the temp word
        if (strcasecmp(temp->op,"Remove")==0) {// if the operation was remove we will remove it in the undo
            while (wordindex<wordCount-1) {
                wordsArray[wordindex]=wordsArray[wordindex+1];// shifting to remove
                wordindex++;
            }
            wordCount--;
        } else if (strcasecmp(temp->op, "Insert") == 0) {// if the operation was insert we will insert the removed word
            if (charindex == -1) temp->wordindex = wordCount; // if the insertion is at the last
            int index = temp->wordindex;
            //printf("%d %d",index,wordCount);// for debugging
            for (int j = wordCount; j > index; j--) {// shifting to make space for the word
                wordsArray[j]=wordsArray[j-1];
            }
            wordsArray[index] = strdup(word);// insert the word in its place
            wordCount++;
        }
    }
}
void Push(Stack S, char *word,char *op,int index,int wordindex) {
    Stack u = (Stack)malloc(sizeof(struct stack));// new node for the stack
    strcpy(u->name, word);// copy the word in the stack
    strcpy(u->op, op);// copy the operation in the stack
    u->index=index;// store the index in the word's character index
    u->wordindex=wordindex;// store the word index in the word's index
    if (u->name == NULL) {// if there is no name
        free(u);
        return;
    }
    u->next = S->next;// insert the new node in the stack
    S->next = u;// make the new node on the top of the stack
}
void printStack(Stack undoStack, Stack redoStack) {
    if (undoStack == NULL && redoStack == NULL) {
        printf("Both stacks are empty.\n");
        return;
    }
    Stack U = (Stack)malloc(sizeof(struct stack));
    U->next = NULL;
    Stack R = (Stack)malloc(sizeof(struct stack));
    R->next = NULL;
    printf("\n\tThe Undo Stack\t\t\t\t\tThe Redo Stack\n");// to make it prints the stacks as a table
    printf("\t--------------\t\t\t\t\t--------------\n");
    while (undoStack->next != NULL || redoStack->next != NULL) {// if there is any element in the undo (OR) the redo stacks
        if (undoStack->next != NULL) {// if there is element or more in undo stack
            Stack tempUndo = Top(undoStack);// store the top of undo in temp
            printf("\t%s %s %d", tempUndo->name, tempUndo->op, tempUndo->index);
            MoveNode(U, undoStack);// move the node from undo into U stack to get it back later so we don't change the original stacks
        } else {
            printf("\t%s","\t");// if there is no elemnts in undo stack
        }
        printf("\t\t\t\t\t");// to print the node under its stack's name
        if (redoStack->next != NULL) {// if there is element or more in redo stack
            Stack tempRedo = Top(redoStack);// store the top of redo in temp
            printf("%s %s %d", tempRedo->name, tempRedo->op, tempRedo->index);
            MoveNode(R, redoStack);// move the node from redo into R stack to get it back later so we don't change the original stacks
        } else {
            printf("%s"," ");
        }
        printf("\n");
    }
    MoveStack (undoStack, U);// get the nodes back to the original stacks
    MoveStack (redoStack, R);
}
void MoveNode (Stack S1, Stack S2) {
    if (S2->next!=NULL) {// if it is not empty
        Stack temp;
        char word[100];
        temp = Top(S2);// store the top of S2 in temp
        strcpy(word,(temp->name));
        Pop(S2);// pop the top of S2
        Push(S1,word,temp->op,temp->index,temp->wordindex);// insert the node "temp" in the stack 1
    }
}
void MoveStack(Stack S1, Stack S2) {
    while (S2->next != NULL) {
        MoveNode(S1, S2);// move all the nodes from stack 2 to stack 1
    }
}
void Pop(Stack S) {
    if (S->next != NULL) {// if the stack is not empty
        Stack p = S->next;// point on the first node
        S->next = S->next->next;// make the second node is the first one
        free(p);// freeing the node
    } else {
        printf("Empty Stack !\n");
    }
}

Stack Top(Stack S) {
    if (S->next != NULL) {
        return S->next;
    } else {
        return NULL;
    }
}

void Enqueue(char *word, Queue Q) {
    Queue q = (Queue)malloc(sizeof(struct queue));// a new node to put it in the queue
    strcpy(q->word, word);// copy the word into the node
    q->next = NULL;
    if (Q->next == NULL) {// if the queue is empty
        Q->next = q;// make the node is the first node
        rear = q;// make the rear points on it because its the first and last
        front = q;// make the front points on it because its the first node
    } else {// if the queue is not empty
        rear->next = q;// insert the node at the last
        rear = q;// make the rear points at it
    }
}
Queue Dequeue(Queue Q) {
    Queue q = Q->next;// point on the first node
    if (Q->next == NULL) {
        printf("Queue is empty !\n");
    } else {
        Q->next=q->next;// make the second node is the first node
        front=q->next;// make the front points on the first node
        return q;// return the node we removed
        free(q);// free the node we removed
    }
}
void printTextOnFile (char *array[]) {
    FILE *out = fopen("output.txt", "w");// open the file to print on it
    fprintf(out, "\nThe text is :\n");
    for (int i = 0; i < wordCount; i++) {
        fprintf(out, "%s ", array[i]);// print all the strings
    }
    fclose(out);// close the output file
}