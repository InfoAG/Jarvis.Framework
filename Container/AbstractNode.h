#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H

namespace CAS {

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
    inline AbstractNode(AbstractNode *previous = nullptr, AbstractNode *next = nullptr) : previous(previous), next(next) {};
    //! Virtual destructor
    virtual inline ~AbstractNode() {};

    virtual T &getItem() = 0; /**< @return A reference to the item */
    virtual AbstractNode *getPrevious() const = 0;
    virtual AbstractNode *getNext() const = 0;
};

}

#endif //ABSTRACTNODE_H
