#include "rbt.h"

// ---------------------------------------
// Node class
// Default constructor
RBTNode::RBTNode() : Node() {
    color = BLACK;
}

// Constructor
RBTNode::RBTNode(int in) : Node(in) {
    color = BLACK;
}
// Destructor
RBTNode::~RBTNode() {
}

void RBTNode::add_color(Node_color c)
{
  color = c;
}

void RBTNode::print_color(ostream& to)
{
    if(color == RED) {
        to << "Red";
    } else if (color == BLACK) {
        to << "Black";
    } else {
        cerr << "ERR: invalid color" << endl;
    }
}
void RBTNode::print_info(ostream& to)
{
    to << get_key() << " ";
    print_color(to);
}

Node_color RBTNode::get_color()
{
  return color;
}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Constructor and destructor
RBT::RBT() : BST()
{
  sentinel = new RBTNode(-1);
  root = sentinel;
}
RBT::~RBT()
{
    // re-using BST's inorder_free
    inorder_free(root, sentinel);
    // This makes sure that root is set to nullptr, so that the parent class's
    // constructor does not try to free the tree again
    root = nullptr;
    delete sentinel; 
}

// Functions that are basically wrappers for the parent class functions
// minimum key in the BST
RBTNode* RBT::tree_min()
{
    // return (RBTNode*) get_min(root);
    // return (RBTNode*) BST::tree_min();
    return (RBTNode*) BST::get_min(root, sentinel);
}
// maximum key in the BST
RBTNode* RBT::tree_max()
{
    // return (RBTNode*) get_max(root);
    // return (RBTNode*) BST::tree_max();
    return (RBTNode*) BST::get_max(root, sentinel);
}

// Get successor of the given node
RBTNode* RBT::get_succ(RBTNode* in)
{
  return (RBTNode*) BST::get_succ((Node*) in, sentinel);
}

// Get predecessor of the given node
RBTNode* RBT::get_pred(RBTNode* in)
{
  return (RBTNode*) BST::get_pred((Node*) in, sentinel);
}

// Search the tree for a given key
RBTNode* RBT::tree_search(int search_key)
{
  return (RBTNode*) BST::tree_search(search_key, sentinel);
}

void RBT::walk(ostream& to)
{
  BST::inorder_walk(root, to, sentinel);
}



// New functions to RBT
// right rotate
void RBT::right_rotate(RBTNode* y)
{
    // Assigning nodes to variables
    RBTNode* curr = y;
    RBTNode* lChild = (RBTNode*) curr->get_left();
    RBTNode* grChild = (RBTNode*) lChild->get_right();
    
    // Adding grandchild as left child to current
    curr->add_left(grChild);

    // If grandchild is a sentinel add curr
    // as grandchild's parent
    if (grChild == sentinel){
    	grChild->add_parent(curr);
    }

    // Adding curr's parent as parent of 
    // left child
    lChild->add_parent(curr->get_parent());

    // Replace curr with left child
    if (curr->get_parent() == sentinel){
    	root = lChild;
    
    }else if (curr == (curr->get_parent())->get_right()){
    	(curr->get_parent())->add_right(lChild);
    }else{
    	(curr->get_parent())->add_left(lChild);
    }

    // Add current as right child of left child 
    lChild->add_right(curr);
    
    // Add left child as parent of curr
    curr->add_parent(lChild);
}

// Left rotate
void RBT::left_rotate(RBTNode* x)
{
    // Assigning nodes to variables
    RBTNode* rChild = (RBTNode*) x->get_right();
    RBTNode* glChild = (RBTNode*) rChild->get_left();
    
    // Adding grandchild as right child to current
    x->add_right(glChild);

    // If grandchild is a sentinel add curr
    // as grandchild's parent
    if (glChild == sentinel){
        glChild->add_parent(x);
    }

    // Adding curr's parent as right 
    // child's parent
    rChild->add_parent(x->get_parent());

    // Replace curr with left child
    if (x->get_parent() == sentinel){
        root = rChild;

    }else if (x == (x->get_parent())->get_left()){
        (x->get_parent())->add_left(rChild);
    }else{
        (x->get_parent())->add_right(rChild);
    }

    // Add current as left child of left child 
    rChild->add_left(x);

     // Add right child as parent of curr
    x->add_parent(rChild);
}
void RBT::rb_insert_fixup(RBTNode* in)
{
	// Assign parent and grandparent to variable
	RBTNode* par = (RBTNode*)in->get_parent();
	RBTNode* gdpar = (RBTNode*)par->get_parent();

    	while (par->get_color() == RED){
	    
	    // if the parent is the left child of
	    // the grandparent then make the parent
	    // and y node black and the grandparent red
	    if (par == (gdpar->get_left())){
		    RBTNode* y = (RBTNode*)gdpar->get_right();
		    if (y->get_color() == RED){
		   	par->add_color(BLACK);
		       	y->add_color(BLACK);
			gdpar->add_color(RED);
			in = gdpar;
			par = (RBTNode *)in->get_parent();
			gdpar = (RBTNode *)par->get_parent();	
		    }else {
			// Else if in is the right node of the 
			// parent make in the parent and left
			// rotate
			if (in == par->get_right()){
			    in = par;
			    left_rotate(in);
			    par = (RBTNode *)in->get_parent();
			    gdpar = (RBTNode *)par->get_parent();
		    }
     		    par->add_color(BLACK);
		    gdpar->add_color(RED);
		    right_rotate(gdpar);

	    }

	}else{
		// if the parent is the right child of
            	// the grandparent then make the parent
            	// and y node black and the grandparent red
		 RBTNode* y = (RBTNode*)gdpar->get_left();
	   	 if (y->get_color() == RED){
                        par->add_color(BLACK);
                        y->add_color(BLACK);
                        gdpar->add_color(RED);
                        in = gdpar;
			par = (RBTNode *)in->get_parent();
                        gdpar = (RBTNode *)par->get_parent();
                    }else {
  			 // Else if in is the right node of the
                         // parent make in the parent and left
                         // rotate

                        if (in == par->get_left()){
                            in = par;
                            right_rotate(in);
			     par = (RBTNode *)in->get_parent();
                            gdpar = (RBTNode *)par->get_parent();

                    }
                    par->add_color(BLACK);
                    gdpar->add_color(RED);
                    left_rotate(gdpar);	
		    
	    
	    }

    
    }
    }

    // Make root black
    ((RBTNode*)root)->add_color(BLACK);
}

void RBT::rb_insert_node(RBTNode* in)
{   
    // Call BST insert
    BST::insert_node(in, sentinel);

    // add left, right, and parent sentinel nodes
    // and set color to red
    in->add_left(sentinel);
    in->add_right(sentinel);
    in->add_color(RED);
    if (in->get_parent() == nullptr){
    	in->add_parent(sentinel);
    }
    rb_insert_fixup(in);
}

void RBT::rb_delete_fixup(RBTNode* in)
{
	RBTNode* parent;
	while ((in != root) && (in->get_color() == BLACK)){
		parent = (RBTNode*)in->get_parent();
		if (in == parent->get_left()){
			RBTNode* sibling = (RBTNode*)parent->get_right();
			// Case 1 : sibling is red so we 
			// add colors and left rotate
			if (sibling->get_color() == RED){
				sibling->add_color(BLACK);
				parent->add_color(RED);
				left_rotate(parent);
				sibling = (RBTNode*)parent->get_right();
			}

	

			// Case 2 : siblings children are both black
			// so we make the sibling red
			if ((((RBTNode*)(sibling->get_left()))->get_color() == BLACK) && (((RBTNode*)(sibling->get_right()))->get_color() == BLACK)){
				sibling->add_color(RED);
				in = parent;
			
			// Case 3-4: if sibling's right nde is black
			// make the left node black and make the sibling
			// red and right rotate
			}else{
				if (((RBTNode*)(sibling->get_right()))->get_color() == BLACK){
				((RBTNode*)(sibling->get_left()))->add_color(BLACK);
				sibling->add_color(RED);

				right_rotate(sibling);
				sibling = (RBTNode*)parent->get_right();
				}

				// Adding color to parent, sibling, and right sibling
				sibling->add_color(parent->get_color());
				parent->add_color(BLACK);
				((RBTNode*)(sibling->get_right()))->add_color(BLACK);
				
				left_rotate(parent);
				in = (RBTNode*)root;
			
			}
		}else{
			RBTNode* sibling = (RBTNode*)parent->get_left();
                        // Case 1 : sibling is red so we 
                        // add colors and left rotate

                        if (sibling->get_color() == RED){
                                sibling->add_color(BLACK);
                                parent->add_color(RED);
                                right_rotate(parent);
                                sibling = (RBTNode*)parent->get_left();
                        }
                        // Case 2 : siblings children are both black
                        // so we make the sibling red
                        if ((((RBTNode*)(sibling->get_left()))->get_color() == BLACK) && (((RBTNode*)(sibling->get_right()))->get_color() == BLACK)){
                                sibling->add_color(RED);
                                in = parent;

                        // Case 3-4: if sibling's right nde is black
                        // make the left node black and make the sibling
                        // red and right rotate
                        }else{
                                if (((RBTNode*)(sibling->get_left()))->get_color() == BLACK){
				((RBTNode*)(sibling->get_right()))->add_color(BLACK);
                                sibling->add_color(RED);
                                left_rotate(sibling);
                                parent = (RBTNode*)in->get_parent();
                                sibling = (RBTNode*)parent->get_left();

                                }
				// Adding color to parent, sibling, and right sibling
                                sibling->add_color(parent->get_color());
                                parent->add_color(BLACK);
                                ((RBTNode*)(sibling->get_left()))->add_color(BLACK);
				right_rotate(parent);
                                in = (RBTNode*)root;

                        }
		
		}
	
	
	
	
	
	}

    // Setting the color of in to black
    in->add_color(BLACK);
}

void RBT::rb_delete_node(RBTNode* out)
{
    	// Saving in's original color
        Node_color orig = out->get_color();
	RBTNode* curr;
	RBTNode* child;

    	// Checking if out has two children
	
    	if ((out->get_left() == sentinel) || (out->get_right() == sentinel)){
		curr = out;
	
	}else{
		curr = this->get_succ(out);
	}
	
	orig = curr->get_color();
	
	RBTNode* parent = (RBTNode*)curr->get_parent();
	
	
	// Setting the child node
	
	if (curr->get_left() != sentinel){
		child = (RBTNode*)curr->get_left();
	}else{
		child = (RBTNode*)curr->get_right();
	}


	// Adding parent only if the child is the sentinel
	 
	if(child == get_sentinel()) {
		
		child->add_parent(parent);	
  	}

	// Adding the child to the parent node 
	
	if (parent == get_sentinel()){
		root = child;
	}else{
		if (curr == parent->get_left()){
		parent->add_left(child);
		}else {
		parent->add_right(child);
	}

	// Case for if the current node is the successor
	
	if (curr != out){
		
		// Copying out's data to the successor node	
		curr->add_parent(out->get_parent());
                if (curr->get_parent() == sentinel){
                        root = curr;
                }else {

                        if(out == (out->get_parent())->get_left()){
                                (curr->get_parent())->add_left(curr);

                        }else{
                                 (curr->get_parent())->add_right(curr);

                        }

			
                }       
			RBTNode* rChild = (RBTNode*)out->get_right();
			RBTNode* lChild = (RBTNode*)out->get_left();
			curr->add_right(rChild);
			curr->add_left(lChild);

			curr->get_left()->add_parent(curr);
			curr->get_right()->add_parent(curr);
			curr->add_color(out->get_color());
				
	}	
		


	// deleting out
	delete out;

	// if the original node is black
	// call delete fixup
       	if (orig == BLACK){
            	rb_delete_fixup(child);
	}


}
}


// ---------------------------------------
//
//
