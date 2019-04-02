#include "Node.h"
#include "Tree.h"
#include <iostream>
#include <string>
#include <stack> //idk why
#include <cstdlib>

using namespace std;

//SEG FAULTING BECUASE I AM NOT ALBE TO SEARCH THE FIRST NODE : ALIEN
//jk got it 

Tree::Tree() { // emptry root means no tree
    root = 0;
}

Tree::~Tree() { // normal destructor
    removeNodes(root);
}

void Tree::removeNodes(Node *current) { // removes the node at current, but can only remove if its a leaf so use isleaf funciton
    if (isLeaf(current) == true) {
        delete current;
        current = 0;
    }
    
    else if (isTwo(current) == true) {
        removeNodes(current -> left);
        removeNodes(current -> right);
    }
    
    else {
        removeNodes(current -> left);
        removeNodes(current -> middle);
        removeNodes(current -> right);
    }
}


void Tree::insert(const string &movie) { //does what it says it will do
    Node *current = root;
    
    if (root == 0) {
        root = new Node(movie);
        return;
    }
    
    while (current->left != 0 || current -> right != 0) {
        if (movie < current -> small) {
            current = current -> left;
        }
        else if (movie > current -> large) {
            current = current -> right;
        }
        else {
            if (current -> middle != 0) {
                current = current -> middle;
            }
        }
    }
    
    if (isTwo(current) == true) {
        if (movie < current -> small) {
            current -> large = current -> small;
            current -> small = movie;
        }
        else {
            current -> large = movie;
        }
    }
    
    else {
        split (current, movie, 0, 0, 0, 0);
    }
    
}

void Tree::split(Node *newNode, const string &movie, Node *left1, Node *left2, Node*right1, Node*right2) {
    //helper for insert: will split the nodes when necessary (should requiore alot of if statemnts)
    string smallVal = smallestNode(newNode, movie);
    string midVal = middleNode(newNode, movie);
    string largeVal = largestNode(newNode, movie);
    Node *parentNode = 0;
    Node *child1 = 0;
    Node *child2 = 0;
    Node *child3 = 0;
    Node *child4 = 0;

    if(newNode == root) {
        parentNode = new Node(midVal);
    }
    else {   
        parentNode = newNode -> parent;
    }
   
    Node *temp1 = new Node(smallVal);
    Node *temp2 = new Node(largeVal); 

    temp1 -> parent = parentNode; 
    temp2 -> parent = parentNode; 
      
    if (!isLeaf(newNode)) {
        left1 -> parent = temp1;
        left2 -> parent = temp1;
        temp1 -> left = left1;
        temp1 -> right = left2;
        right1 -> parent = temp2;
        right2 -> parent = temp2;
        temp2 -> left = right1;
        temp2 -> right = right2;
    }

    string temp3 = midVal;

    if(isThree(parentNode)==true && isThree(newNode)==true) {
        if(parentNode -> left == newNode) {
            child1 = temp1;
            child2 = temp2;
            child3 = parentNode->left;
            child4 = parentNode->right;
        }
        else if (parentNode -> right == newNode) {
            child1 = parentNode -> left;
            child2 = parentNode -> middle;
            child3 = temp1;
            child4 = temp2;
        }
        else {
            child1 = parentNode -> left;
            child2 = temp1;
            child3 = temp2;
            child4 = parentNode -> right;
        }
        split(parentNode, temp3, child1, child2, child3, child4);
    }
   
    if(isTwo(parentNode)==true) {
        if(newNode == root) {
            root = parentNode;
            parentNode -> left = temp1;
            parentNode -> right = temp2; 
        }
        else if (parentNode -> left == newNode) {
            parentNode -> left = temp1;
            parentNode -> middle = temp2;
            parentNode -> large = parentNode -> small;
            parentNode -> small = temp3;
        }
        else { 
            parentNode -> middle = temp1;
            parentNode -> right = temp2;
            parentNode -> large = temp3;
        }
    }
    return;
}

// void Tree::insert(const string & word){ // should call split fpr help
//     if(root == NULL){
//         Node * current = new Node(word); // create new node for root
//         root = current;
//         root -> parent = NULL;
//         root -> left = NULL;
//         root -> right = NULL;
//         root -> middle = NULL;
//         return;
//     }
//     else{
//         Node * current = root; // always start at the root and work your way down
//         while(current -> left != NULL && current -> right != NULL && current -> middle != NULL){
//             if(word < current -> small){
//                 current = current -> left;
//             }
//             else if(word > current -> large){
//                 current = current -> right;
//             }
//             else if(word > current -> small && word < current -> large){
//                 current = current -> middle;
//             }
//         }
        
//         while(current -> right != 0 && current -> left != 0 && current -> middle == 0){   
//             if(word < current -> small){
//                 current = current -> left;
//             }
//             else if(word > current -> large){
//                 current = current -> right;
//             }
//             else if(word > current -> small && word < current -> large){  //middle??
//                 Node * newnode = new Node(word);
//                 newnode -> parent = current ;
//                 current = current -> middle;
//                 current = newnode;
//             }
//         }

//         if(current -> large == ""){        //because small currently has the first inserted value
//             if(word > current -> small){
//                 current -> large = word; 
//             }
//             else if(word < current -> small){
//                 current -> large = current -> small;
//                 current -> small = word;
//             }
//         }
//         else{  
//             split(current,word);
//         }
//     }
 
//     return;
// }

// void Tree::split(Node* current, const string & word) { //used to help insert
//     if(current -> parent == 0){
//         if(word > current -> small && word < current -> large){  //word is middle, current->s = small and current->large = large;
//             Node * newnodel = new Node(current -> small);  //create a new Node for small
//             Node * newnode = new Node(current -> large);	 //word is middle but we dont assign it right 
            
//         	current -> left = newnodel;
//         	current -> right = newnode;
        	
//         	current -> left -> parent = current;
//         	current -> right -> parent = current;
        	
//         	current->small = word;	 
//             current ->large = "";
//         }
//         else if(word < current -> small){ 
//             Node * newnode = new Node(word);
//         	Node * newnoder = new Node(current -> large);
//             current -> left = newnode;
//             newnode -> parent = current;
//         	current -> right = newnoder;
//         	current -> right -> parent = current;
//         	current -> large = "";
//         }
//         else if(word > current -> large){ 
//             Node * newnode = new Node(word);
// 	        Node * newnodel = new Node(current -> small);
//             current -> left = newnodel;
//             newnodel -> parent = current;
//         	current -> right = newnode;
//         	current -> right -> parent = current;
//         	current-> large = "";
//         }
//     }
    
//     else{   //if it has a parent
//     //         //if new value is less than small
//         if(word < current -> small){
//             Node * newnode = new Node(word);
//             current -> parent -> middle = newnode;
//             newnode -> parent = current -> parent;
                
//         	current -> parent -> large = current -> small;
//         	root =  current -> parent;			
//         	current -> small = current -> large;	 
//           	current ->large = "";	
   
//         }  
            
//         else if(word > current -> large){
//             Node * newnodem = new Node(current -> small);
//             current -> parent -> middle = newnodem;
//             newnodem -> parent = current -> parent;
//             current -> parent -> large   =  current ->large;
//             current -> small = "";
//             current -> small = word;
// 	        current -> large = "";
                
//         }
            
//         else if(word > current -> small && word < current -> large){
//             Node *newnode = new Node(current -> small);
//             current -> parent -> middle = newnode;
//             newnode -> parent = current -> parent;
//             current -> parent -> large = word;
// 	        current -> small = current -> large;
// 	        current -> large = "";
//         }
//     }
// }


void Tree::preOrder() const {
    preOrder(root);
    cout << endl;
}

void Tree::preOrder(Node *current) const { // helper function for the pre order function given
    if (current) {
        if (current -> small != "") {
            cout << current -> small << ", ";
        }
        preOrder(current -> left);
        if (isThree(current)) {
            if (current -> large != "") {
                cout << current -> large << ", ";
            }
            preOrder(current -> middle);
        }
        preOrder(current -> right);
    }
}

void Tree::inOrder() const {
    inOrder(root);
    cout << endl;
}

void Tree::inOrder(Node *current) const { //helper funciotn for the in order function given
    if (current) {
        inOrder(current -> left);
        if (current -> small != "") {
            cout << current -> small << ", ";
        }
        if (isThree(current)) {
            inOrder(current-> middle);
            if (current -> large != "") {
                cout << current -> large << ", ";
            }
        }
        inOrder(current -> right);
    }
}

void Tree::postOrder() const {
    postOrder(root);
    cout << endl;
}

void Tree::postOrder(Node *current) const { //helper funciton for the post order funciton given
    if (current) {
        postOrder(current -> left);
        if (isThree(current)) {
            postOrder(current -> middle);
            if (current -> small != "") {
                cout << current -> small << ", ";
            }
        }
        postOrder(current -> right);
        if (isTwo(current)) {
            if (current -> small != "") {
                cout << current -> small << ", ";
            }
        }
        if (isThree(current)) {
            if (current -> large != "") {
                cout << current -> large <<", ";
            }
        }
    }
}

bool Tree::search (const string &movie) const { // call another search function
    Node *key = search(root, movie);
    if (key -> small == movie || key -> large == movie) {
        return true;
    }
    
    return false;
}

Node* Tree::search(Node *current, const string &movie) const { // more advanced and intricate // recursive
    if (current) {
        if (isLeaf(current)) {
            return current;
        }
        
        else if (isTwo(current)) {
            if (movie == current -> small || movie == current -> large) {
                return current;
            }
            else if (movie < current -> small) {
                return search(current -> left, movie);
            }
            else {
                return search(current -> right, movie);
            }
        }
        
        else {
            if (movie == current -> small || movie == current -> large) {
                return current;
            }
            else if (movie < current -> small) {
                return search(current -> left, movie);
            }
            else if (movie > current -> large) {
                return search(current -> right, movie);
            }
            else {
                return search(current -> middle, movie);
            }
        }
    }
    return 0;
}

bool Tree::isTwo(Node *current) const {
    if (current -> large.empty()) {
        return true;
    }
    else {
        return false;
    }
}

bool Tree::isThree(Node *current) const {
    if (!current -> small.empty() && !current -> large.empty()) {
        return true;
    }
    else {
        return false;
    }
}

bool Tree::isLeaf(Node *current) const {
    if (current -> left == 0 && current -> middle == 0 && current -> right ==0) {
        return true;
    }
    else {
        return false;
    }
}

string Tree::smallestNode(Node *current, const string &movie) {
    string Pierre;
    if (movie < current -> small) {
        Pierre = movie;
    }
    
    else {
        Pierre = current -> small;
    }
    
    return Pierre;
}

string Tree::middleNode(Node *current, const string &movie) {
    string youngMetro;
    if (movie < current -> small) {
        youngMetro = current -> small;
    }
    
    else if (movie < current -> large) {
        youngMetro = movie;
    }
    
    else {
        youngMetro = current -> large;
    }
    
    return youngMetro;
}

string Tree::largestNode(Node *current, const string &movie) {
    string metroBoomin;
    if (movie < current -> large) {
        metroBoomin = current -> large;
    }
    
    else {
        metroBoomin = movie;
    }
    
    return metroBoomin;
}

// void Tree::postOrder(Node *current) const {
//     if (current) {
//         postOrder(current -> left);
//         if (isThree(current)) {
//             postOrder(current -> middle);
//             if (current -> small != "") {
//                 cout << current -> small << ", ";
//             }
//         }
//         postOrder(current -> right);
//         if (isTwo(current)) {
//             if (current -> small != "") {
//                 cout << current -> small << ", ";
//             }
//         }
//         if (isThree(current)) {
//             if (current -> large != "") {
//                 cout << current -> large <<", ";
//             }
//         }
//     }
// }



Node* Tree::getNext(Node *current, const string &movie) const {
    if (isLeaf(current)) { // when there is no next
        return current;
    }
    
    else if (isTwo(current)) {
        if (movie < current -> small) {
            return getNext(current -> left, movie);
        }
        else {
            return getNext(current -> right, movie);
        }
    }
    
    else {
        if (movie < current -> small) {
            return getNext(current -> left, movie);
        }
        else if (movie < current -> large) {
            return getNext(current -> middle, movie);
        }
        else {
            return getNext(current -> right, movie);
        }
    }
}

Node* Tree::getSibling(Node *bretheren) {
    Node *parentNode = bretheren -> parent;
    if(isTwo(parentNode)) {
        if (parentNode -> left == bretheren) {
            return parentNode -> right;
        }
        else if(parentNode -> right == bretheren) {
            return parentNode -> left;
        }
    }
    else {
        if (parentNode -> right == bretheren || parentNode -> left == bretheren) {
            return parentNode -> middle;
        }
        else {
            if (isThree(parentNode -> left) && isThree(parentNode -> right)) {
                return parentNode -> right;
            }
            else if (isTwo(parentNode -> left) && isTwo(parentNode -> right)) {
                return parentNode -> left;
            }
            else if (isThree(parentNode -> left)) {
                return parentNode -> left;
            }
            else {
                return parentNode -> right;
            }
        }
    }
    return 0;
}

void Tree::remove(const string &movie) { // funtion given by zybooks. will call delte node (the horrid fucntion below)
    Node *current = search(root, movie);
    Node *leaf = 0;
    if (current) {
        if (!isLeaf(current) == true) {
            Node *nxt = getNext(current, movie);
            if (current -> small == movie) {
                swap(current -> small, nxt -> small);
            }
            else {
                swap(current -> large, nxt -> large);
            }
            leaf = nxt;
        }
        
        else {
            leaf = current;
        }
        
        if (movie == leaf -> large) {
            leaf -> large = "";
        }
        
        else {
            leaf -> small = leaf -> large;
            leaf -> large = "";
        }
        if (leaf -> small.empty()) {
            deleteNode(leaf);
        }
    }
}

void Tree::deleteNode(Node *bye) {
     if (bye == root) {
        if (isLeaf(bye) == true) {
            delete bye;
            root = 0;
            return;
        }
        
        else {
            if (root -> right == 0) {
                root = root -> left;
            }
            else {
                root = root -> right;
            }
        }
        return;
    }
    
    else {
        Node* parentNode = bye -> parent;
        Node* siblingNode = getSibling(bye);
       
        if (isThree(siblingNode) == true) {
            if (parentNode!=NULL && parentNode-> left == bye){
                if (isTwo(parentNode)){
                    bye->small = parentNode->small;
                    parentNode->small = siblingNode->small;
                    siblingNode->small = siblingNode->large;
                    siblingNode->large = "";
                }
                else {
                    if (isTwo(parentNode->right) == true) {
                        bye -> small = parentNode -> small;
                        parentNode -> small = siblingNode -> small;
                        siblingNode -> small = siblingNode -> large;
                        siblingNode -> large = "";
                    }
                    else {
                        bye -> small = parentNode -> small;
                        parentNode -> small = siblingNode -> small;
                        siblingNode -> small = siblingNode -> large;
                        siblingNode -> large = "";
                    }
                }
            }
            
            else if (parentNode -> middle == bye) { 
                if (parentNode -> left == siblingNode){
                    bye -> small = parentNode -> small;
                    parentNode -> small = siblingNode -> large;
                    siblingNode -> large = "";
                }
                else{
                    bye -> small = parentNode -> large;
                    parentNode -> large = siblingNode -> small;
                    siblingNode -> small = siblingNode -> large;
                    siblingNode -> large = "";
                }
            }
            else { 
                if (isTwo(parentNode)) {
                    bye -> small = parentNode->small;
                    parentNode -> small = siblingNode -> large;
                    siblingNode -> large = "";
                }
                else {
                    if (isTwo(parentNode->left)) {
                        bye->small = parentNode->large;
                        parentNode -> large = siblingNode -> small;
                        siblingNode -> small = siblingNode -> large;
                        siblingNode -> large = "";
                    }
                    else{ //if p's left is a 3 Node
                        bye -> small = parentNode -> large;
                        parentNode -> large = siblingNode -> large;
                        siblingNode -> large = "";
                    }
                }
            }

            if ((bye -> left != 0 && bye -> right == 0) || (bye -> right != 0 && bye -> left == 0)) { //internal node
                if (parentNode -> right == bye) {
                    if (bye -> left == 0){
                        bye -> left = siblingNode -> right;
                        siblingNode -> right = siblingNode -> middle;
                        siblingNode -> middle = 0;
                    }
                    else{
                        bye -> right = bye -> left;
                        bye -> left = siblingNode -> right;
                        siblingNode -> right = siblingNode -> middle;
                        siblingNode -> middle = 0;
                    }
                }
                else {
                    if (bye -> right == 0) {
                        bye -> right = siblingNode -> left;
                        siblingNode -> left = siblingNode -> middle;
                        siblingNode -> middle = 0;
                    }
                    else{
                        bye -> left = bye -> right;
                        bye -> right = siblingNode -> left;
                        siblingNode -> left = siblingNode -> middle;
                        siblingNode -> middle = 0;
                    }
                }
            }
        }
        else {
            if (isTwo(parentNode) == true) {
                if (parentNode -> left == bye) {
                    siblingNode -> large = siblingNode->small;
                    siblingNode -> small = parentNode->small;
                    parentNode -> small = "";
                } 
                else {
                    parentNode -> large = parentNode -> small;
                    parentNode -> small = siblingNode -> small;
                    siblingNode -> small = "";
                }
            }
            else {
                if (parentNode->left == bye) {
                    if (isTwo(parentNode -> right)) {
                        siblingNode -> large = siblingNode -> small;
                        siblingNode -> small = parentNode -> small;
                        parentNode -> small = parentNode -> large;
                        parentNode -> large = "";
                        parentNode -> left = siblingNode;
                        parentNode -> middle = 0;
                    }
                    else {
                        bye -> small = parentNode -> small;
                        parentNode -> small = siblingNode -> small;
                        siblingNode -> small = parentNode -> large;
                        parentNode -> large = parentNode -> right -> small;
                        parentNode -> right -> small = parentNode -> right -> large;
                        parentNode -> right -> large = "";
                    }
                }
                else if (parentNode -> middle == bye) {
                    siblingNode -> large = parentNode -> small;
                    parentNode -> small = parentNode -> large;
                    parentNode -> large = "";
                    parentNode -> middle = 0;
                }
                else { 
                    if (isTwo(parentNode -> left)) {
                        siblingNode -> large = parentNode -> large;
                        parentNode -> large = "";
                        parentNode -> right = siblingNode;
                        parentNode -> middle = 0;
                    }
                    else {
                        bye -> small = parentNode -> large;
                        parentNode -> large = siblingNode -> small;
                        siblingNode -> small = parentNode -> small;
                        parentNode -> small = parentNode -> left -> large;
                        parentNode -> left -> large = "";
                    }
                }
            }

            if ((bye -> left != 0 && bye -> right == 0) || (bye -> right !=0 && bye -> left == 0)) {
                if (parentNode!=NULL && parentNode -> right == bye) {
                    siblingNode -> middle = siblingNode -> right;
                    if (bye -> left == 0) {
                        siblingNode -> right = bye -> right;
                    }
                    else {
                        siblingNode -> right = bye -> left;
                    }
                }
                else {
                    siblingNode -> middle = siblingNode -> left;
                    if (bye -> right == 0) {
                        siblingNode -> left = bye -> left;
                    }
                    else {
                        siblingNode -> left = bye -> right;
                    }
                }
            }

            delete bye;
            bye = 0;
            
            if (parentNode -> small.empty() && parentNode -> large.empty()) {
                deleteNode(parentNode);
            }
        }
    }
}