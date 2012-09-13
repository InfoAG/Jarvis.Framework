#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "global.h"
#include "AbstractLevelingOperation.h"

namespace CAS {

class Matrix : public AbstractLevelingOperation
{
public:
    /*
    Matrix(const std::vector<unsigned int> &dimensions) {
        if (dimensions.size() == 1) {
            for (unsigned int i = 0; i < dimensions.at(0); i++)
                operands.emplace_back(make_unique<DataCell>());
        } else {
            for (unsigned int i = 0; i < dimensions.at(0); i++)
                children.emplace_back(make_unique<Matrix>(std::vector<unsigned int>(begin(dimensions) + 1, end(dimensions))));
        }
    }*/
    Matrix(Operands operands) : AbstractLevelingOperation(std::move(operands)) {}
    Matrix(const Matrix &other) : AbstractLevelingOperation(other) {}

    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Matrix>(*this); }
    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return MATRIX; }
    virtual std::string toString() const;
    virtual bool equals(const AbstractArithmetic *other) const;
};

/*
struct MatrixCell : public AbstractArithmetic
{
    virtual std::unique_ptr<AbstractArithmetic> &data() { throw "no data"; }
    virtual bool hasData() const = 0;
    virtual MatrixCell &operator[](int) { throw "no children"; }
};

class DataCell : public MatrixCell
{
public:
    DataCell() {};
    DataCell(const DataCell &other) : child(other.child->copy()) {}

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return child->eval(ei); }
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<DataCell>(*this); }
    virtual ArithmeticType type() const { return DATACELL; }
    virtual std::string toString() const;
    virtual bool equals(const AbstractArithmetic *other) const;

    virtual std::unique_ptr<AbstractArithmetic> &data() { return child; }
    virtual bool hasData() const { return true; }

private:
    std::unique_ptr<AbstractArithmetic> child;

};

class Matrix : public MatrixCell
{
private:
    std::vector<std::unique_ptr<MatrixCell>> children;

public:
    Matrix(const std::vector<unsigned int> &dimensions) {
        if (dimensions.size() == 1) {
            for (unsigned int i = 0; i < dimensions.at(0); i++)
                children.emplace_back(make_unique<DataCell>());
        } else {
            for (unsigned int i = 0; i < dimensions.at(0); i++)
                children.emplace_back(make_unique<Matrix>(std::vector<unsigned int>(begin(dimensions) + 1, end(dimensions))));
        }
    }
    Matrix(std::vector<std::unique_ptr<MatrixCell>> children) : children(std::move(children)) {}
    Matrix(const Matrix &other);

    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Matrix>(*this); }
    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return MATRIX; }
    virtual std::string toString() const;
    virtual bool equals(const AbstractArithmetic *other) const;

    virtual bool hasData() const { return false; }

    virtual MatrixCell &operator[](int i) {
        if (children[i]->hasData()) return *(static_cast<DataCell*>(children[i].get()));
        else return *(static_cast<Matrix*>(children[i].get()));
    }
};*/

}

#endif //MATRIX_H
