template<typename Type>
class DoubleNode {
public:
	DoubleNode(Type = Type(), DoubleNode<Type>* = nullptr, DoubleNode<Type>* = nullptr);

	Type value() const;
	DoubleNode<Type>* previous() const;
	DoubleNode<Type>* next() const;
	void setnext(DoubleNode<Type>*);

	Type         nodeValue;
	DoubleNode<Type>* previousNode;
	DoubleNode<Type>* nextNode;
};
template<typename Type>
DoubleNode<Type>::DoubleNode(
	Type nv,
	DoubleNode<Type>* pn,
	DoubleNode<Type>* nn) :
	// Updated the initialization list here
	nodeValue(nv), // This assigns 'nodeValue' the default value
	previousNode(pn),
	nextNode(nn)
{
	// Enter your implementation here

}


/*this function just return nodevalue*/
template<typename Type>
Type DoubleNode<Type>::value() const {
	// Enter your implementation here

	return nodeValue; // This returns the default value
}


/*this function just return previousnode*/
template<typename Type>
DoubleNode<Type>* DoubleNode<Type>::previous() const {
	// Enter your implementation here

	return previousNode;
}


/*this function just return nextnode*/
template<typename Type>
::DoubleNode<Type>* DoubleNode<Type>::next() const {
	// Enter your implementation here

	return nextNode;
}


/*this function just set nextnode with input*/
template<typename Type>
void DoubleNode<Type>::setnext(DoubleNode<Type>* n) {
	nextNode = n;
}