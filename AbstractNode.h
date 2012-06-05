#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H

//! A list node.
template <class T>
struct AbstractNode
{
    AbstractNode *previous; /**< Pointer to previous node in list. */
    AbstractNode *next; /**< Pointer to next node in list. */

    /** Constructor
      * @param previous Pointer to previous node in list
      * @param next Pointer to next node in list
      */
    inline AbstractNode(AbstractNode *previous = 0, AbstractNode *next = 0) : previous(previous), next(next) {};
    /** Virtual copy constructor
      * @return A pointer to a copy of this node
      */
    virtual AbstractNode *copy(AbstractNode *previous = 0, AbstractNode *next = 0) const = 0;
    //! Virtual destructor
    virtual inline ~AbstractNode() {};

    virtual T &getItem() = 0; /**< @return A reference to the item */
};

#endif //ABSTRACTNODE_H
