
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

/* given */
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

/* given */
twoDtree::~twoDtree(){
	clear();
}

/* given */
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}

/* given */
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}






/**
    * Constructor that builds a twoDtree out of the given PNG.
    * Every leaf in the tree corresponds to a pixel in the PNG.
    * Every non-leaf node corresponds to a rectangle of pixels 
    * in the original PNG, represented by an (x,y) pair for the 
    * upper left corner of the rectangle and an (x,y) pair for 
    * lower right corner of the rectangle. In addition, the Node
    * stores a pixel representing the average color over the 
    * rectangle. 
    *
    * Every node's left and right children correspond to a partition
    * of the node's rectangle into two smaller rectangles. The node's
    * rectangle is split by the horizontal or vertical line that 
    * results in the two smaller rectangles whose sum of squared 
    * differences from their mean is as small as possible.
    *
    * The left child of the node will contain the upper left corner
    * of the node's rectangle, and the right child will contain the
    * lower right corner.
    *
   * This function will build the stats object used to score the 
   * splitting lines. It will also call helper function buildTree.
    */
twoDtree::twoDtree(PNG & imIn){
    stats s = stats(imIn);
    width = imIn.width();
    height = imIn.height();
    buildTree(s, pair<int,int>(0,0), pair<int,int>(width-1,height-1));
}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr) {
    RGBAPixel average=s.getAvg(ul,lr);
    root = new Node(ul,lr,average);
    buildTreeHelper(root,s,ul,lr);
    return root;
}

void twoDtree::buildTreeHelper(Node* n, stats & s, pair<int,int> ul, pair<int, int>lr){
    if(ul.first==lr.first && ul.second==lr.second) return;
    pair<pair<int,int>, pair<int,int>> sp = splitHelper(s,ul,lr);
    n->left = new Node(ul,sp.first,s.getAvg(ul,sp.first));
    n->right = new Node(ul,sp.second,s.getAvg(ul,sp.second));
    buildTreeHelper(n->left,s,ul,sp.first);
    buildTreeHelper(n->right,s,sp.second,lr);
}

pair<pair<int, int>, pair<int, int>> twoDtree::splitHelper(stats & s, pair<int,int> ul, pair<int, int>lr){
    long avgScore;
    long minScore = LONG_MAX;
    pair< pair<int, int>, pair<int, int> > cut;
    pair <int,int> lr_temp;
    pair <int,int> ul_temp;
    //cout<< "line 61"<<endl;
    for(int x = ul.first; x<lr.first; x++){
        lr_temp = make_pair (x, lr.second);
        ul_temp = make_pair (x + 1, ul.second);
        avgScore = s.getScore(ul,lr_temp) + s.getScore(ul_temp,lr);
        if(avgScore<minScore){
            //cout<< "line 70"<<endl;
            minScore = avgScore;
            cut.first = pair<int, int>(x , lr.second);
            cut.second = pair<int, int>(x + 1, ul.second);
        }
    }
    //cout<< "line 77"<<endl;
    for(int y = ul.second; y<lr.second; y++){
        //cout<< "line 79"<<endl;
        lr_temp = make_pair (lr.first, y);
        //cout<< "line 81"<<endl;
        ul_temp = make_pair (ul.first, y + 1);
        //cout<< "line 83"<<endl;
        avgScore = s.getScore(ul,lr_temp) + s.getScore(ul_temp,lr);
        //cout<< "line 85"<<endl;
        if(avgScore<minScore){
            minScore = avgScore;
            cut.first = pair<int, int>(lr.first, y);
            cut.second = pair<int, int>(ul.first, y + 1);
        }
    }
    return cut;
}




/**
    * Render returns a PNG image consisting of the pixels
    * stored in the tree. may be used on pruned trees. Draws
    * every leaf node's rectangle onto a PNG canvas using the 
    * average color stored in the node.
*/
PNG twoDtree::render(){
    if(root==NULL) return *(new PNG());
    PNG image(width,height);
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            *(image.getPixel(i,j)) = pixelHelper(root,i,j);
        }
    }
    return image;
}

RGBAPixel twoDtree::pixelHelper(Node* n,int i,int j){
    if(n->left==NULL&&n->right==NULL) return n->avg;
    
    else if(i<=n->left->lowRight.first&&n->left->upLeft.first<=i
            && j<=n->left->lowRight.second && n->left->upLeft.second<=j){
        return pixelHelper(n->left,i,j);
    }
    
    
    else{return pixelHelper(n->right,i,j);}
}






/*
    *  Prune function trims subtrees as high as possible in the tree.
    *  A subtree is pruned (cleared) if at least pct of its leaves are within 
    *  tol of the average color stored in the root of the subtree. 
    *  Pruning criteria should be evaluated on the original tree, not 
    *  on a pruned subtree. (we only expect that trees would be pruned once.)
    *  
   * You may want a recursive helper function for this one.
*/
void twoDtree::prune(double pct, int tol){
    pruneHelper(root, pct, tol);
}

void twoDtree::pruneHelper(Node* node, double pct, int tol){
     if(root != NULL){
    double counter = countLeaf(node);
    double count = countTol(node, node->avg, tol);
    double leaves_percent;


    if(counter != 0){
        leaves_percent = count/counter;
    } else{
        leaves_percent = 0;
    }
            if(( count/counter)>=pct){
                clearHelper(node->left);
                clearHelper(node->right);
                node->left=NULL;
                node->right=NULL;
                return;
        }
            else{
                pruneHelper(node->left,pct,tol);
                pruneHelper(node->right,pct,tol);

            }

    }
     return;
}

double twoDtree::countTol (Node* root, RGBAPixel &p, int tol) {
    int count = 0;
    if(root != NULL){
        if(root->left == NULL && root->right == NULL){

            if(computeD(root->avg, p, tol)){
                return 1;
            }
            return 0;

        }

        if(root->left != NULL){
            count += countTol (root->left, p, tol);
        }

        if(root->right != NULL){
            count += countTol(root->right, p, tol);
        }

    }

    return count;
}



double twoDtree::countLeaf (Node* root) {
    double counter = 0;
    if(root != NULL){
        if(root->left == NULL && root->right == NULL){
            return 1;

        }

        if(root->left != NULL){
            counter += countLeaf (root->left);
        }

        if(root->right != NULL){
            counter +=countLeaf(root->right);
        }

    }

    return counter;
}

bool twoDtree::computeD(RGBAPixel & p1, RGBAPixel & p2, int tol){
    int p1r = p1.r;
    int p1g = p1.g;
    int p1b = p1.b;

    int p2r = p2.r;
    int p2g = p2.g;
    int p2b = p2.b;

    int r_diff = (p1r-p2r)*(p1r-p2r);
    int g_diff = (p1g-p2g)*(p1g-p2g);
    int b_diff = (p1b-p2b)*(p1b-p2b);

    return (r_diff + g_diff + b_diff) <= tol;
}



void twoDtree::clear() {
    clearHelper(root);
}


void twoDtree::clearHelper(Node* root){
    if(root==NULL){
        return;
    }
    if(root->left!=NULL){
        clearHelper(root->left);
    }
    if(root->right!=NULL){
        clearHelper(root->right);
    }
    delete(root);
    root= NULL;
}


void twoDtree::copy(const twoDtree & orig){
    /* your code here */
    root = new Node(orig.root->upLeft,orig.root->lowRight,orig.root->avg);
    height = orig.height;
    width = orig.width;
    copyHelper(root, orig.root);
}

void twoDtree::copyHelper(Node *dst, Node *src){
    if(src!=NULL){
        if(src->left!=NULL && src->right!=NULL){//0 or 2 children
            
            dst->left = new Node(src->left->upLeft, src->left->lowRight, src->left->avg);
            dst->right = new Node(src->right->upLeft, src->right->lowRight, src->right->avg);
            
            copyHelper(dst->left,src->left);
            copyHelper(dst->right,src->right);
        }
    }
}














