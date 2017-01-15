/**
 * @author Kalpathi Subramanian
 * @date  10/5/16
 *
 * This class can be used to create circular doubly linked element objects
 * with next and previous (prev) pointers
 *
 */
#include "DLelement.h"

namespace bridges{

template <typename E>
class CircDLelement : public  DLelement<E>{
	public:
		/** 
	 	 *	Constructs an empty CircDLelement with next and prev pointers set 
	 	 *	to itself
		*/
		CircDLelement() : DLelement<E> (this, this, E()) {
		}
	
		/** Constructs a CircDLelement labeled "label", holding an object "e", 
	 	 *	with next and prev pointers set to itself
	 	 * 	@param e the genereic object that this CircDLelement is holding
	 	 * 	@param label the label for this CircDLelement that shows up on the 
	 	 *		Bridges visualization
	 	 */
		CircDLelement (E e, string label) 
				: DLelement<E>(this, this, e, label) {
		}

		/** 
	 	 *	Constructs an empty DLelement with the next pointer set to the 
		 *	CircDLelement "next" and the prev pointer set to CircDLelement 
		 *	"prev". 
		 *
		 * 	@param next the DLelement that should be assigned to the next 
		 *		pointer
		 *	@param prev the DLelement that should be assigned to the prev 
		 *		pointer
		 *
		 */
		CircDLelement(CircDLelement<E> next, CircDLelement<E> prev) 
							: DLelement<E>(this, this) {
		}

		/** 
	 	 *	Constructs a DLelement holding an object "e", with the next pointer 
	 	 *	set to the DLelement "next" and the prev pointer set to DLelement 
	 	 *	"prev". 
	 	 *
	 	 *	@param e the genereic object that this CircDLelement is holding
	 	 *	@param next the CircDLelement that should be assigned to the next 
	 	 *		pointer
		 *	@param prev the CircDLelement that should be assigned to the prev 
	 	 *	pointer
	 	 *
	 	 */
		CircDLelement(E e, CircDLelement<E> next, CircDLelement<E> prev) 
									: DLelement<E>(this, this, e) {
		}
	
		/**
	 	 *	This method gets the data structure type
	 	 *
	 	 *	@return  The date structure type as a string
	 	 **/
		 string getDSType() {
			 return "CircularDoublyLinkedList";
		 }

		/**
	 	 * This method returns the pointer to the next DLelement
		 * @return the DLelement assigned to the next pointer
		 */
		const CircDLelement<E> *getNext() const {
			return static_cast<const CircDLelement*>(SLelement<E>::getNext());
		}
	
		/**
	 	 * This method sets the pointer to the next DLelement
		 *
	 	 * @param next the DLelement that should be assigned to the next pointer
	 	 *
	 	 */
		 void setNext(CircDLelement<E> *next) {
			 DLelement<E>::setNext(next);
		 }
	

		/**
		 * This method returns the pointer to the previous DLelement
	 	 * @return the DLelement assigned to the prev pointer
	 	 */
		 const CircDLelement<E> *getPrev() const {
			 return static_cast<const CircDLelement*>(SLelement<E>::getPrev());
		 }

		/**
		 * This method sets the pointer to the previous DLelement
	 	 * @param prev the DLelement that should be assigned to the prev pointer
	 	 */
		void setPrev(CircDLelement<E> *prev) {
			DLelement<E>::setPrev(prev);
		}
};

} //namespace bridges